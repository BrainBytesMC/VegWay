// If your project requires pch.h/stdafx.h, include it before all other headers.
#include "ItemAddForm.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <memory>
#include <string>
#include <sstream>
#include <exception>
#include <vcclr.h>

namespace VegWay {
    namespace ItemAddData {
        // Length-aware UTF-8 conversion, including non-English names/locations.
        static std::string ToUtf8(System::String^ value) {
            array<System::Byte>^ bytes = System::Text::Encoding::UTF8->GetBytes(value);
            if (bytes->Length == 0) return std::string();
            pin_ptr<System::Byte> ptr = &bytes[0];
            return std::string(reinterpret_cast<const char*>(ptr), bytes->Length);
        }
        static std::string ToBinary(array<System::Byte>^ bytes) {
            if (bytes == nullptr || bytes->Length == 0) return std::string();
            pin_ptr<System::Byte> ptr = &bytes[0];
            return std::string(reinterpret_cast<const char*>(ptr), bytes->Length);
        }
    }

    System::Void ItemAddForm::ItemAddForm_Load(System::Object^, System::EventArgs^) {
        // Layout/defaults are in InitializeComponent. No database work in Design view.
    }

    void ItemAddForm::DisposePhoto() {
        if (picPhoto != nullptr && picPhoto->Image != nullptr) {
            System::Drawing::Image^ old = picPhoto->Image;
            picPhoto->Image = nullptr;
            delete old;
        }
        selectedImageBytes = nullptr;
        selectedImagePath = nullptr;
    }

    System::Void ItemAddForm::btnBrowse_Click(System::Object^, System::EventArgs^) {
        if (saving) return;
        System::Windows::Forms::OpenFileDialog^ picker = gcnew System::Windows::Forms::OpenFileDialog();
        picker->Filter = "Image files (*.jpg;*.jpeg;*.png;*.bmp)|*.jpg;*.jpeg;*.png;*.bmp";
        picker->Title = "Select item photo";
        picker->CheckFileExists = true;
        try {
            if (picker->ShowDialog(this) != System::Windows::Forms::DialogResult::OK) return;
            System::IO::FileInfo^ info = gcnew System::IO::FileInfo(picker->FileName);
            if (info->Length > 20LL * 1024 * 1024) {
                MessageBox::Show(this, "Choose a photo smaller than 20 MB.", "Photo size");
                return;
            }
            // Work with a byte copy so the original photo is not kept file-locked.
            array<System::Byte>^ inputBytes = System::IO::File::ReadAllBytes(picker->FileName);
            System::IO::MemoryStream^ input = gcnew System::IO::MemoryStream(inputBytes);
            System::Drawing::Image^ original = nullptr;
            System::Drawing::Bitmap^ thumbnail = nullptr;
            System::Drawing::Graphics^ graphics = nullptr;
            System::IO::MemoryStream^ output = gcnew System::IO::MemoryStream();
            try {
                original = System::Drawing::Image::FromStream(input);
                // Respect common camera EXIF orientation before resizing.
                if (System::Array::IndexOf<int>(original->PropertyIdList, 0x0112) >= 0) {
                    array<System::Byte>^ orientation = original->GetPropertyItem(0x0112)->Value;
                    if (orientation->Length > 0) {
                        switch (orientation[0]) {
                        case 2: original->RotateFlip(System::Drawing::RotateFlipType::RotateNoneFlipX); break;
                        case 3: original->RotateFlip(System::Drawing::RotateFlipType::Rotate180FlipNone); break;
                        case 4: original->RotateFlip(System::Drawing::RotateFlipType::Rotate180FlipX); break;
                        case 5: original->RotateFlip(System::Drawing::RotateFlipType::Rotate90FlipX); break;
                        case 6: original->RotateFlip(System::Drawing::RotateFlipType::Rotate90FlipNone); break;
                        case 7: original->RotateFlip(System::Drawing::RotateFlipType::Rotate270FlipX); break;
                        case 8: original->RotateFlip(System::Drawing::RotateFlipType::Rotate270FlipNone); break;
                        }
                    }
                }
                double scale = System::Math::Min(1.0, 800.0 /
                    System::Math::Max(original->Width, original->Height));
                int width = System::Math::Max(1, static_cast<int>(original->Width * scale));
                int height = System::Math::Max(1, static_cast<int>(original->Height * scale));
                thumbnail = gcnew System::Drawing::Bitmap(width, height);
                graphics = System::Drawing::Graphics::FromImage(thumbnail);
                graphics->Clear(System::Drawing::Color::White);
                graphics->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::HighQualityBicubic;
                graphics->DrawImage(original, 0, 0, width, height);
                delete graphics; graphics = nullptr;
                thumbnail->Save(output, System::Drawing::Imaging::ImageFormat::Jpeg);
                array<System::Byte>^ normalized = output->ToArray();
                if (normalized->Length == 0 || normalized->Length > 8 * 1024 * 1024)
                    throw gcnew System::ArgumentException("The processed photo is too large.");
                // Replace the previous photo only after the new one is valid.
                DisposePhoto();
                selectedImageBytes = normalized;
                selectedImagePath = picker->FileName;
                picPhoto->Image = thumbnail;
                thumbnail = nullptr; // PictureBox now owns this preview.
            }
            finally {
                if (graphics != nullptr) delete graphics;
                if (thumbnail != nullptr) delete thumbnail;
                if (original != nullptr) delete original;
                delete input; delete output;
            }
        }
        catch (System::Exception^ ex) {
            MessageBox::Show(this, "Could not open this photo.\r\n" + ex->Message, "Photo error",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        finally { delete picker; }
    }

    System::Void ItemAddForm::btnAddItem_Click(System::Object^, System::EventArgs^) {
        if (saving) return;
        System::UInt32 seller = 0;
        if (!System::UInt32::TryParse(sellerUserId, seller) || seller == 0) {
            MessageBox::Show(this, "Please open this form from the market after logging in.", "Login required");
            return;
        }
        System::String^ name = txtName->Text->Trim();
        System::String^ location = txtLocation->Text->Trim();
        System::String^ phone = txtPhone->Text->Trim();
        if (System::String::IsNullOrWhiteSpace(name) || System::String::IsNullOrWhiteSpace(location) ||
            System::String::IsNullOrWhiteSpace(phone) || cmbCategory->SelectedIndex < 0) {
            MessageBox::Show(this, "Enter the item name, location and phone number, and choose a category.", "Required fields");
            return;
        }
        if (name->Length > 100 || location->Length > 150 || phone->Length > 20) {
            MessageBox::Show(this, "Name: up to 100 characters; location: 150; phone: 20.", "Field length");
            return;
        }
        System::Decimal price = 0;
        System::Decimal quantity = 0;
        // Decimal point is '.'; do not enter commas/thousands separators.
        System::Globalization::NumberStyles style = System::Globalization::NumberStyles::AllowDecimalPoint |
            System::Globalization::NumberStyles::AllowLeadingWhite | System::Globalization::NumberStyles::AllowTrailingWhite;
        System::Globalization::CultureInfo^ culture = System::Globalization::CultureInfo::InvariantCulture;
        if (!System::Decimal::TryParse(txtPrice->Text, style, culture, price) ||
            !System::Decimal::TryParse(txtQuantity->Text, style, culture, quantity)) {
            MessageBox::Show(this, "Enter valid numbers, for example price 250.50 and quantity 2.500. Use a dot for decimals.", "Invalid number");
            return;
        }
        System::Decimal maxPrice = System::Decimal::Parse("99999999.99", culture);
        System::Decimal maxQuantity = System::Decimal::Parse("9999999.999", culture);
        if (price <= System::Decimal::Zero || price > maxPrice ||
            System::Decimal::Round(price, 2) != price ||
            quantity <= System::Decimal::Zero || quantity > maxQuantity ||
            System::Decimal::Round(quantity, 3) != quantity) {
            MessageBox::Show(this, "Price must be positive with up to 2 decimal places (maximum 99999999.99).\r\n"
                "Quantity must be positive with up to 3 decimal places (maximum 9999999.999 kg).", "Invalid price or quantity");
            return;
        }
        if (selectedImageBytes == nullptr || selectedImageBytes->Length == 0) {
            MessageBox::Show(this, "Click Browse Photo and choose a vegetable image first.", "Photo required");
            return;
        }
        saving = true;
        btnAddItem->Enabled = false; btnBrowse->Enabled = false; UseWaitCursor = true;
        bool saved = false;
        try {
            try {
                sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
                // Keep these settings consistent with your working login/market.
                std::unique_ptr<sql::Connection> con(driver->connect(
                    "tcp://127.0.0.1:3306", "root", "rasu"));
                con->setSchema("vegdb");
                con->setAutoCommit(true);
                std::unique_ptr<sql::PreparedStatement> statement(con->prepareStatement(
                    "INSERT INTO vegetables "
                    "(seller_userid, vegetable_name, category, image_data, price_per_kg, "
                    "quantity_kg, location, contact_phone) VALUES (?, ?, ?, ?, ?, ?, ?, ?)"));
                statement->setUInt(1, static_cast<unsigned int>(seller));
                statement->setString(2, ItemAddData::ToUtf8(name));
                statement->setString(3, ItemAddData::ToUtf8(cmbCategory->SelectedItem->ToString()));
                // Binary stream stays alive until executeUpdate completes.
                std::string image = ItemAddData::ToBinary(selectedImageBytes);
                std::istringstream photo(image, std::ios::in | std::ios::binary);
                statement->setBlob(4, &photo);
                statement->setString(5, ItemAddData::ToUtf8(price.ToString("F2", culture)));
                statement->setString(6, ItemAddData::ToUtf8(quantity.ToString("F3", culture)));
                statement->setString(7, ItemAddData::ToUtf8(location));
                statement->setString(8, ItemAddData::ToUtf8(phone));
                if (statement->executeUpdate() != 1)
                    throw gcnew System::InvalidOperationException("The database did not confirm an inserted item.");
                saved = true;
            }
            catch (const sql::SQLException& ex) {
                MessageBox::Show(this, "Could not save the item. Your inputs have been kept.\r\n" +
                    gcnew System::String(ex.what()), "Database error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            catch (const std::exception& ex) {
                MessageBox::Show(this, gcnew System::String(ex.what()), "Save error");
            }
            catch (System::Exception^ ex) {
                MessageBox::Show(this, ex->Message, "Save error");
            }
        }
        finally {
            saving = false; UseWaitCursor = false;
            btnAddItem->Enabled = true; btnBrowse->Enabled = true;
        }
        if (!saved) return;
        MessageBox::Show(this, "Your item was saved to VegWay Market.", "Item added",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->Close();
    }
}

#include "VegWayMarket.h"
#include "ProfileSettings.h"
#include "PayNow.h"
#include "ItemAddForm.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <memory>
#include <string>
#include <istream>
#include <exception>
#include <vcclr.h>

namespace VegWay {
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Windows::Forms;
    using namespace System::Collections::Generic;

    // Native connector and byte conversion code stays out of the designer header.
    namespace MarketData {

        static std::string ToUtf8(String^ value) {
            array<Byte>^ bytes = System::Text::Encoding::UTF8->GetBytes(value);
            if (bytes->Length == 0) return std::string();
            pin_ptr<Byte> pinned = &bytes[0];
            return std::string(reinterpret_cast<const char*>(pinned), bytes->Length);
        }

        static String^ FromUtf8(const std::string& value) {
            array<Byte>^ bytes = gcnew array<Byte>(static_cast<int>(value.size()));
            for (int i = 0; i < bytes->Length; ++i) bytes[i] = static_cast<Byte>(value[i]);
            return System::Text::Encoding::UTF8->GetString(bytes);
        }

        Image^ ReadImage(sql::ResultSet* rows) {
            if (rows->isNull("image_data")) return nullptr;
            // Connector/C++ transfers ownership of getBlob()'s stream to the caller.
            std::unique_ptr<std::istream> stream(rows->getBlob("image_data"));
            if (!stream.get()) return nullptr;
            std::string bytes; char buffer[4096];
            while (stream->read(buffer, sizeof(buffer)) || stream->gcount() > 0) {
                bytes.append(buffer, static_cast<size_t>(stream->gcount()));
                if (bytes.size() > 8 * 1024 * 1024) return nullptr;
            }
            if (bytes.empty()) return nullptr;
            array<Byte>^ managed = gcnew array<Byte>(static_cast<int>(bytes.size()));
            for (int i = 0; i < managed->Length; ++i) managed[i] = static_cast<Byte>(bytes[i]);
            IO::MemoryStream^ memory = gcnew IO::MemoryStream(managed);
            Image^ original = nullptr;
            try {
                original = Image::FromStream(memory);
                return gcnew Bitmap(original); // Own a copy before closing the stream.
            }
            catch (ArgumentException^) { return nullptr; }
            catch (Runtime::InteropServices::ExternalException^) { return nullptr; }
            finally { if (original != nullptr) delete original; delete memory; }
        }
    }


    Color VegWayMarket::Green() { return Color::FromArgb(20, 100, 66); }

    Label^ VegWayMarket::MakeLabel(String^ text, float size, bool bold) {
        Label^ label = gcnew Label();
        label->Text = text;
        label->Font = gcnew Drawing::Font("Segoe UI", size,
            bold ? FontStyle::Bold : FontStyle::Regular);
        label->ForeColor = Color::FromArgb(28, 60, 42);
        label->AutoEllipsis = true;
        return label;
    }

    Button^ VegWayMarket::MakeButton(String^ text) {
        Button^ button = gcnew Button();
        button->Text = text;
        button->BackColor = Green(); button->ForeColor = Color::White;
        button->FlatStyle = FlatStyle::Flat;
        button->FlatAppearance->BorderSize = 0;
        button->Cursor = Cursors::Hand;
        button->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
        return button;
    }

    void VegWayMarket::ClearCards() {
        if (cards == nullptr) return;
        for each (Panel ^ card in cards) {
            for each (Control ^ control in card->Controls) {
                PictureBox^ picture = dynamic_cast<PictureBox^>(control);
                if (picture != nullptr && picture->Image != nullptr) {
                    Image^ old = picture->Image; picture->Image = nullptr; delete old;
                }
            }
            products->Controls->Remove(card); delete card;
        }
        cards->Clear();
    }

    void VegWayMarket::AddCard(String^ id, String^ name, String^ price, Image^ image) {
        Panel^ card = gcnew Panel(); card->BackColor = Color::White;
        PictureBox^ picture = gcnew PictureBox();
        picture->Bounds = Rectangle(12, 12, 240, 170);
        picture->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right;
        picture->SizeMode = PictureBoxSizeMode::Zoom;
        picture->BackColor = Color::FromArgb(232, 241, 232);
        picture->Image = image; picture->AccessibleName = name;
        card->Controls->Add(picture);
        if (image == nullptr) {
            Label^ missing = MakeLabel("Image unavailable", 10, false);
            missing->Dock = DockStyle::Fill;
            missing->TextAlign = ContentAlignment::MiddleCenter;
            picture->Controls->Add(missing);
        }
        Label^ title = MakeLabel(name, 13, true);
        title->Bounds = Rectangle(12, 190, 240, 30);
        title->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right;
        Label^ amount = MakeLabel("Rs. " + price + " / kg", 12, true);
        amount->Bounds = Rectangle(12, 225, 240, 28);
        amount->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right;
        Button^ buy = MakeButton("Buy now"); buy->Tag = id;
        buy->Bounds = Rectangle(12, 265, 240, 40);
        buy->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right;
        buy->AccessibleName = "Buy " + name;
        buy->Click += gcnew EventHandler(this, &VegWayMarket::BuyClick);
        card->Controls->Add(title); card->Controls->Add(amount); card->Controls->Add(buy);
        card->Size = Drawing::Size(264, 320);
        cards->Add(card); products->Controls->Add(card);
    }

    void VegWayMarket::ArrangeCards() {
        if (products == nullptr || cards == nullptr) return;
        const int gap = 16;
        int width = Math::Max(180, (products->ClientSize.Width -
            SystemInformation::VerticalScrollBarWidth - gap * 4) / 3);
        Point scroll = products->AutoScrollPosition;
        for (int i = 0; i < cards->Count; ++i) {
            cards[i]->Bounds = Rectangle(gap + (i % 3) * (width + gap) + scroll.X,
                gap + (i / 3) * 336 + scroll.Y, width, 320);
        }
        int rows = (cards->Count + 2) / 3;
        products->AutoScrollMinSize = Drawing::Size(0, rows == 0 ? 0 : gap + rows * 336);
    }

    void VegWayMarket::LoadProducts() {
        if (IsDesignSurface() || cards == nullptr || loading) return;
        loading = true; UseWaitCursor = true;
        products->SuspendLayout(); ClearCards();
        products->AutoScrollPosition = Point(0, 0);
        empty->Visible = false; status->Text = "Loading vegetables...";
        try {
            sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
            // Same local connection as your existing forms.
            std::unique_ptr<sql::Connection> con(driver->connect(
                "tcp://127.0.0.1:3306", "root", "rasu"));
            con->setSchema("vegdb");
            std::unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement(
                "SELECT vegetable_id, vegetable_name, price_per_kg, image_data "
                "FROM vegetables WHERE is_active = 1 AND quantity_kg > 0 "
                "AND (? = 'All vegetables' OR category = ?) "
                "AND LOCATE(?, vegetable_name) > 0 "
                "ORDER BY created_at DESC, vegetable_id DESC"));
            stmt->setString(1, MarketData::ToUtf8(category)); stmt->setString(2, MarketData::ToUtf8(category));
            stmt->setString(3, MarketData::ToUtf8(search->Text->Trim()));
            std::unique_ptr<sql::ResultSet> rows(stmt->executeQuery());
            while (rows->next()) {
                AddCard(MarketData::FromUtf8(rows->getString("vegetable_id").asStdString()),
                    MarketData::FromUtf8(rows->getString("vegetable_name").asStdString()),
                    MarketData::FromUtf8(rows->getString("price_per_kg").asStdString()), MarketData::ReadImage(rows.get()));
            }
            status->Text = String::Format("{0} available item(s) | {1}", cards->Count, category);
            empty->Text = category == "All vegetables" && String::IsNullOrWhiteSpace(search->Text)
                ? "No items added yet.\r\nVegetables will appear here after sellers add them."
                : "No vegetables match your search or category.";
            empty->Visible = cards->Count == 0;
        }
        catch (const sql::SQLException& ex) {
            ClearCards(); empty->Text = "Could not load vegetables.\r\nCheck MySQL and run 01-vegetables.sql, then click Refresh.";
            empty->Visible = true; status->Text = "Database error - items could not be loaded.";
            MessageBox::Show(this, gcnew String(ex.what()), "Market database error",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        catch (const std::exception& ex) {
            ClearCards(); empty->Text = "Could not load items. Please click Refresh.";
            empty->Visible = true; status->Text = "Loading failed.";
            MessageBox::Show(this, gcnew String(ex.what()), "Market error");
        }
        catch (System::Exception^ ex) {
            ClearCards(); empty->Text = "Could not load items. Please click Refresh.";
            empty->Visible = true; status->Text = "Loading failed.";
            MessageBox::Show(this, ex->Message, "Market error");
        }
        finally {
            products->ResumeLayout(); ArrangeCards();
            UseWaitCursor = false; loading = false;
        }
    }

    void VegWayMarket::UpdateCategoryButtons() {
        if (categories == nullptr) return;
        for each (Button ^ button in categories) {
            bool selected = safe_cast<String^>(button->Tag) == category;
            button->BackColor = selected ? Green() : Color::Honeydew;
            button->ForeColor = selected ? Color::White : Green();
        }
    }

    void VegWayMarket::FirstShown(
        System::Object^ sender,
        System::EventArgs^ e)
    {
        if (IsDesignSurface())
            return;

        if (cards == nullptr)
        {
            cards = gcnew System::Collections::Generic::List<
                System::Windows::Forms::Panel^>();
        }

        if (categories == nullptr)
        {
            categories = gcnew System::Collections::Generic::List<
                System::Windows::Forms::Button^>();
        }

        if (categories->Count == 0)
        {
            categories->Add(allButton);
            categories->Add(leafyButton);
            categories->Add(rootButton);
            categories->Add(fruitButton);
            categories->Add(beansButton);
            categories->Add(otherButton);
        }

        category = "All vegetables";
        search->Clear();
        searchTimer->Stop();

        UpdateCategoryButtons();
        LoadProducts();
    }

    void VegWayMarket::ProductsResize(Object^, EventArgs^) { ArrangeCards(); }

    void VegWayMarket::RefreshClick(Object^, EventArgs^) {
        if (IsDesignSurface() || cards == nullptr) return;
        searchTimer->Stop(); LoadProducts();
    }

    void VegWayMarket::SearchChanged(Object^, EventArgs^) {
        if (IsDesignSurface() || cards == nullptr) return;
        searchTimer->Stop(); searchTimer->Start();
    }

    void VegWayMarket::SearchTick(Object^, EventArgs^) {
        if (IsDesignSurface() || cards == nullptr) return;
        searchTimer->Stop(); LoadProducts();
    }

    void VegWayMarket::CategoryClick(Object^ sender, EventArgs^) {
        if (IsDesignSurface() || cards == nullptr) return;

        category = safe_cast<String^>(safe_cast<Button^>(sender)->Tag);
        searchTimer->Stop(); UpdateCategoryButtons(); LoadProducts();
    }

    void VegWayMarket::ProfileClick(Object^, EventArgs^) {
        profileMenu->Show(profile, Point(0, profile->Height));
    }

    void VegWayMarket::ProfileAction(
        System::Object^ sender,
        System::EventArgs^ e)
    {
        if (System::String::IsNullOrWhiteSpace(userId))
        {
            System::Windows::Forms::MessageBox::Show(
                this, "Please log in again.");
            return;
        }

        int page = 0;

        if (sender == changeNameItem)
            page = 1;
        else if (sender == changePasswordItem)
            page = 2;
        else if (sender == toolStripMenuItem1)
            page = 3;

        VegWay::ProfileSettings^ settings =
            gcnew VegWay::ProfileSettings(userId, page);

        try
        {
            settings->ShowDialog(this);

            if (!System::String::IsNullOrWhiteSpace(
                settings->UpdatedName))
            {
                userName = settings->UpdatedName;
            }
        }
        finally
        {
            delete settings;
        }
    }

    void VegWayMarket::SellClick(Object^, EventArgs^) {
        // Later: open SellerForm for userId; refresh after it saves successfully.
        MessageBox::Show(this, "The seller form will be added next.", "Sell vegetables");
    }

    void VegWayMarket::BuyClick(
        System::Object^ sender,
        System::EventArgs^ e)
    {
        if (System::String::IsNullOrWhiteSpace(userId))
        {
            System::Windows::Forms::MessageBox::Show(
                this, "Please log in before buying.");
            return;
        }

        System::Windows::Forms::Button^ button =
            safe_cast<System::Windows::Forms::Button^>(sender);

        System::String^ itemId =
            System::Convert::ToString(button->Tag);

        if (System::String::IsNullOrWhiteSpace(itemId))
        {
            System::Windows::Forms::MessageBox::Show(
                this, "This button has no item ID.");
            return;
        }

        vegway::PayNow^ payment =
            gcnew vegway::PayNow(userId, itemId);

        try
        {
            payment->ShowDialog(this);
        }
        finally
        {
            delete payment;
        }

        LoadProducts();
    }

    bool VegWayMarket::IsDesignSurface() {
        return DesignMode || System::ComponentModel::LicenseManager::UsageMode ==
            System::ComponentModel::LicenseUsageMode::Designtime;
    }
    void VegWayMarket::DisposeMarket() {
        if (searchTimer != nullptr) searchTimer->Stop();
        ClearCards();
    }
}

#pragma once

#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <memory>
#include <string>
#include <exception>
#include <vcclr.h>

// Matches the attached RegForm:
// vegdb.users(userid, CustomerName, Email, Phonenumber, Password)
// Password format: PBKDF2-SHA256$600000$<Base64 salt>$<Base64 hash>
// Requires the same MySQL Connector/C++ setup and .NET Framework 4.7.2+.
// No schema changes or database writes are made by this form.

namespace VegWay {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Drawing;
    using namespace System::Windows::Forms;

    public ref class LoginForm : public System::Windows::Forms::Form
    {
    public:
        LoginForm(void)
        {
            InitializeComponent();
        }

        // Available to the caller only after ShowDialog() returns OK.
        property String^ LoggedInUserId { String^ get() { return loggedInUserId; } }
        property String^ LoggedInName { String^ get() { return loggedInName; } }
        property String^ LoggedInEmail { String^ get() { return loggedInEmail; } }

    protected:
        ~LoginForm()
        {
            if (components) delete components;
        }

    private:
        System::ComponentModel::Container^ components;
        String^ loggedInUserId;
        String^ loggedInName;
        String^ loggedInEmail;
        System::Windows::Forms::Panel^ brandPanel;
        System::Windows::Forms::Panel^ loginPanel;
        System::Windows::Forms::PictureBox^ logoPIC;
        System::Windows::Forms::Label^ brandTitle;
        System::Windows::Forms::Label^ brandDescription;
        System::Windows::Forms::Label^ teamLabel;
        System::Windows::Forms::Label^ titleLabel;
        System::Windows::Forms::Label^ subtitleLabel;
        System::Windows::Forms::Label^ emailLabel;
        System::Windows::Forms::Label^ passwordLabel;
        System::Windows::Forms::TextBox^ EmailTXT;
        System::Windows::Forms::TextBox^ PassTXT;
        System::Windows::Forms::CheckBox^ showPassCHK;
        System::Windows::Forms::Button^ loginBTN;
        System::Windows::Forms::Button^ cancelBTN;
        System::Windows::Forms::Label^ statusLBL;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(LoginForm::typeid));
            this->brandPanel = (gcnew System::Windows::Forms::Panel());
            this->logoPIC = (gcnew System::Windows::Forms::PictureBox());
            this->brandTitle = (gcnew System::Windows::Forms::Label());
            this->brandDescription = (gcnew System::Windows::Forms::Label());
            this->teamLabel = (gcnew System::Windows::Forms::Label());
            this->loginPanel = (gcnew System::Windows::Forms::Panel());
            this->titleLabel = (gcnew System::Windows::Forms::Label());
            this->subtitleLabel = (gcnew System::Windows::Forms::Label());
            this->emailLabel = (gcnew System::Windows::Forms::Label());
            this->passwordLabel = (gcnew System::Windows::Forms::Label());
            this->EmailTXT = (gcnew System::Windows::Forms::TextBox());
            this->PassTXT = (gcnew System::Windows::Forms::TextBox());
            this->showPassCHK = (gcnew System::Windows::Forms::CheckBox());
            this->loginBTN = (gcnew System::Windows::Forms::Button());
            this->cancelBTN = (gcnew System::Windows::Forms::Button());
            this->statusLBL = (gcnew System::Windows::Forms::Label());
            this->brandPanel->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->logoPIC))->BeginInit();
            this->loginPanel->SuspendLayout();
            this->SuspendLayout();
            // 
            // brandPanel
            // 
            this->brandPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
                static_cast<System::Int32>(static_cast<System::Byte>(66)));
            this->brandPanel->Controls->Add(this->logoPIC);
            this->brandPanel->Controls->Add(this->brandTitle);
            this->brandPanel->Controls->Add(this->brandDescription);
            this->brandPanel->Controls->Add(this->teamLabel);
            this->brandPanel->Dock = System::Windows::Forms::DockStyle::Left;
            this->brandPanel->Location = System::Drawing::Point(0, 0);
            this->brandPanel->Margin = System::Windows::Forms::Padding(4);
            this->brandPanel->Name = L"brandPanel";
            this->brandPanel->Size = System::Drawing::Size(388, 675);
            this->brandPanel->TabIndex = 1;
            // 
            // logoPIC
            // 
            this->logoPIC->BackColor = System::Drawing::Color::Transparent;
            this->logoPIC->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"logoPIC.Image")));
            this->logoPIC->Location = System::Drawing::Point(45, 60);
            this->logoPIC->Margin = System::Windows::Forms::Padding(4);
            this->logoPIC->Name = L"logoPIC";
            this->logoPIC->Size = System::Drawing::Size(95, 95);
            this->logoPIC->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
            this->logoPIC->TabIndex = 0;
            this->logoPIC->TabStop = false;
            // 
            // brandTitle
            // 
            this->brandTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 30, System::Drawing::FontStyle::Bold));
            this->brandTitle->ForeColor = System::Drawing::Color::White;
            this->brandTitle->Location = System::Drawing::Point(38, 199);
            this->brandTitle->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->brandTitle->Name = L"brandTitle";
            this->brandTitle->Size = System::Drawing::Size(325, 80);
            this->brandTitle->TabIndex = 1;
            this->brandTitle->Text = L"VegWay";
            // 
            // brandDescription
            // 
            this->brandDescription->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
            this->brandDescription->ForeColor = System::Drawing::Color::Honeydew;
            this->brandDescription->Location = System::Drawing::Point(45, 300);
            this->brandDescription->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->brandDescription->Name = L"brandDescription";
            this->brandDescription->Size = System::Drawing::Size(298, 172);
            this->brandDescription->TabIndex = 2;
            this->brandDescription->Text = L"Fresh connections.\r\nA greener way forward.\r\n\r\nWelcome back to your\r\nVegWay commun"
                L"ity.";
            // 
            // teamLabel
            // 
            this->teamLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
            this->teamLabel->ForeColor = System::Drawing::Color::Honeydew;
            this->teamLabel->Location = System::Drawing::Point(45, 590);
            this->teamLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->teamLabel->Name = L"teamLabel";
            this->teamLabel->Size = System::Drawing::Size(312, 58);
            this->teamLabel->TabIndex = 3;
            this->teamLabel->Text = L"BRAIN BYTES 2026\r\nVERSION 01.01";
            // 
            // loginPanel
            // 
            this->loginPanel->BackColor = System::Drawing::Color::White;
            this->loginPanel->Controls->Add(this->titleLabel);
            this->loginPanel->Controls->Add(this->subtitleLabel);
            this->loginPanel->Controls->Add(this->emailLabel);
            this->loginPanel->Controls->Add(this->passwordLabel);
            this->loginPanel->Controls->Add(this->EmailTXT);
            this->loginPanel->Controls->Add(this->PassTXT);
            this->loginPanel->Controls->Add(this->showPassCHK);
            this->loginPanel->Controls->Add(this->loginBTN);
            this->loginPanel->Controls->Add(this->cancelBTN);
            this->loginPanel->Controls->Add(this->statusLBL);
            this->loginPanel->Dock = System::Windows::Forms::DockStyle::Fill;
            this->loginPanel->Location = System::Drawing::Point(388, 0);
            this->loginPanel->Margin = System::Windows::Forms::Padding(4);
            this->loginPanel->Name = L"loginPanel";
            this->loginPanel->Size = System::Drawing::Size(737, 675);
            this->loginPanel->TabIndex = 0;
            this->loginPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &LoginForm::loginPanel_Paint);
            // 
            // titleLabel
            // 
            this->titleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26, System::Drawing::FontStyle::Bold));
            this->titleLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(24)), static_cast<System::Int32>(static_cast<System::Byte>(67)),
                static_cast<System::Int32>(static_cast<System::Byte>(44)));
            this->titleLabel->Location = System::Drawing::Point(65, 60);
            this->titleLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->titleLabel->Name = L"titleLabel";
            this->titleLabel->Size = System::Drawing::Size(600, 78);
            this->titleLabel->TabIndex = 0;
            this->titleLabel->Text = L"Welcome back";
            this->titleLabel->Click += gcnew System::EventHandler(this, &LoginForm::titleLabel_Click);
            // 
            // subtitleLabel
            // 
            this->subtitleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
            this->subtitleLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(92)), static_cast<System::Int32>(static_cast<System::Byte>(110)),
                static_cast<System::Int32>(static_cast<System::Byte>(98)));
            this->subtitleLabel->Location = System::Drawing::Point(70, 148);
            this->subtitleLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->subtitleLabel->Name = L"subtitleLabel";
            this->subtitleLabel->Size = System::Drawing::Size(598, 52);
            this->subtitleLabel->TabIndex = 1;
            this->subtitleLabel->Text = L"Sign in using your registered email and password.";
            // 
            // emailLabel
            // 
            this->emailLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
            this->emailLabel->Location = System::Drawing::Point(70, 226);
            this->emailLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->emailLabel->Name = L"emailLabel";
            this->emailLabel->Size = System::Drawing::Size(288, 35);
            this->emailLabel->TabIndex = 2;
            this->emailLabel->Text = L"EMAIL ADDRESS";
            // 
            // passwordLabel
            // 
            this->passwordLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
            this->passwordLabel->Location = System::Drawing::Point(70, 331);
            this->passwordLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->passwordLabel->Name = L"passwordLabel";
            this->passwordLabel->Size = System::Drawing::Size(288, 35);
            this->passwordLabel->TabIndex = 3;
            this->passwordLabel->Text = L"PASSWORD";
            // 
            // EmailTXT
            // 
            this->EmailTXT->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
            this->EmailTXT->Location = System::Drawing::Point(70, 269);
            this->EmailTXT->Margin = System::Windows::Forms::Padding(4);
            this->EmailTXT->MaxLength = 254;
            this->EmailTXT->Name = L"EmailTXT";
            this->EmailTXT->Size = System::Drawing::Size(596, 34);
            this->EmailTXT->TabIndex = 0;
            this->EmailTXT->TextChanged += gcnew System::EventHandler(this, &LoginForm::EmailTXT_TextChanged);
            // 
            // PassTXT
            // 
            this->PassTXT->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
            this->PassTXT->Location = System::Drawing::Point(70, 374);
            this->PassTXT->Margin = System::Windows::Forms::Padding(4);
            this->PassTXT->MaxLength = 128;
            this->PassTXT->Name = L"PassTXT";
            this->PassTXT->Size = System::Drawing::Size(596, 34);
            this->PassTXT->TabIndex = 1;
            this->PassTXT->UseSystemPasswordChar = true;
            // 
            // showPassCHK
            // 
            this->showPassCHK->AutoSize = true;
            this->showPassCHK->Location = System::Drawing::Point(70, 434);
            this->showPassCHK->Margin = System::Windows::Forms::Padding(4);
            this->showPassCHK->Name = L"showPassCHK";
            this->showPassCHK->Size = System::Drawing::Size(149, 27);
            this->showPassCHK->TabIndex = 2;
            this->showPassCHK->Text = L"Show password";
            this->showPassCHK->UseVisualStyleBackColor = true;
            this->showPassCHK->CheckedChanged += gcnew System::EventHandler(this, &LoginForm::showPassCHK_CheckedChanged);
            // 
            // loginBTN
            // 
            this->loginBTN->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
                static_cast<System::Int32>(static_cast<System::Byte>(66)));
            this->loginBTN->Cursor = System::Windows::Forms::Cursors::Hand;
            this->loginBTN->FlatAppearance->BorderSize = 0;
            this->loginBTN->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->loginBTN->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
            this->loginBTN->ForeColor = System::Drawing::Color::White;
            this->loginBTN->Location = System::Drawing::Point(70, 492);
            this->loginBTN->Margin = System::Windows::Forms::Padding(4);
            this->loginBTN->Name = L"loginBTN";
            this->loginBTN->Size = System::Drawing::Size(288, 60);
            this->loginBTN->TabIndex = 3;
            this->loginBTN->Text = L"Login";
            this->loginBTN->UseVisualStyleBackColor = false;
            this->loginBTN->Click += gcnew System::EventHandler(this, &LoginForm::loginBTN_Click);
            // 
            // cancelBTN
            // 
            this->cancelBTN->BackColor = System::Drawing::Color::Honeydew;
            this->cancelBTN->Cursor = System::Windows::Forms::Cursors::Hand;
            this->cancelBTN->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->cancelBTN->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)),
                static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(66)));
            this->cancelBTN->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->cancelBTN->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
            this->cancelBTN->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
                static_cast<System::Int32>(static_cast<System::Byte>(66)));
            this->cancelBTN->Location = System::Drawing::Point(380, 492);
            this->cancelBTN->Margin = System::Windows::Forms::Padding(4);
            this->cancelBTN->Name = L"cancelBTN";
            this->cancelBTN->Size = System::Drawing::Size(288, 60);
            this->cancelBTN->TabIndex = 4;
            this->cancelBTN->Text = L"Cancel";
            this->cancelBTN->UseVisualStyleBackColor = false;
            this->cancelBTN->Click += gcnew System::EventHandler(this, &LoginForm::cancelBTN_Click);
            // 
            // statusLBL
            // 
            this->statusLBL->ForeColor = System::Drawing::Color::Firebrick;
            this->statusLBL->Location = System::Drawing::Point(70, 572);
            this->statusLBL->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->statusLBL->Name = L"statusLBL";
            this->statusLBL->Size = System::Drawing::Size(598, 75);
            this->statusLBL->TabIndex = 5;
            // 
            // LoginForm
            // 
            this->AcceptButton = this->loginBTN;
            this->AutoScaleDimensions = System::Drawing::SizeF(120, 120);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
            this->BackColor = System::Drawing::Color::Honeydew;
            this->CancelButton = this->cancelBTN;
            this->ClientSize = System::Drawing::Size(1125, 675);
            this->Controls->Add(this->loginPanel);
            this->Controls->Add(this->brandPanel);
            this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->Margin = System::Windows::Forms::Padding(4);
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"LoginForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"VegWay Login";
            this->Load += gcnew System::EventHandler(this, &LoginForm::LoginForm_Load);
            this->brandPanel->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->logoPIC))->EndInit();
            this->loginPanel->ResumeLayout(false);
            this->loginPanel->PerformLayout();
            this->ResumeLayout(false);

        }
#pragma endregion

    private:
        static std::string ToUtf8(String^ value)
        {
            array<Byte>^ bytes = System::Text::Encoding::UTF8->GetBytes(value);
            if (bytes->Length == 0) return std::string();
            pin_ptr<Byte> pinned = &bytes[0];
            return std::string(reinterpret_cast<const char*>(pinned), bytes->Length);
        }

        static String^ FromUtf8(const std::string& value)
        {
            array<Byte>^ bytes = gcnew array<Byte>(static_cast<int>(value.size()));
            for (int i = 0; i < bytes->Length; ++i)
                bytes[i] = static_cast<Byte>(value[i]);
            return System::Text::Encoding::UTF8->GetString(bytes);
        }

        static bool VerifyPassword(String^ password, String^ stored)
        {
            if (String::IsNullOrEmpty(stored)) return false;
            array<Char>^ separators = gcnew array<Char>(1);
            separators[0] = '$';
            array<String^>^ parts = stored->Split(separators);
            // Accept exactly the format produced by the supplied RegForm.
            if (parts->Length != 4 || parts[0] != "PBKDF2-SHA256" ||
                parts[1] != "600000") return false;

            array<Byte>^ salt;
            array<Byte>^ expected;
            try
            {
                salt = Convert::FromBase64String(parts[2]);
                expected = Convert::FromBase64String(parts[3]);
            }
            catch (FormatException^) { return false; }
            if (salt->Length != 16 || expected->Length != 32) return false;

            System::Security::Cryptography::Rfc2898DeriveBytes^ pbkdf2 =
                gcnew System::Security::Cryptography::Rfc2898DeriveBytes(
                    password, salt, 600000,
                    System::Security::Cryptography::HashAlgorithmName::SHA256);
            array<Byte>^ actual;
            try { actual = pbkdf2->GetBytes(32); }
            finally { delete pbkdf2; }

            // Compare every byte without returning on the first mismatch.
            int difference = 0;
            for (int i = 0; i < expected->Length; ++i)
                difference |= actual[i] ^ expected[i];
            return difference == 0;
        }

        System::Void showPassCHK_CheckedChanged(Object^ sender, EventArgs^ e)
        {
            this->PassTXT->UseSystemPasswordChar = !this->showPassCHK->Checked;
        }

        System::Void cancelBTN_Click(Object^ sender, EventArgs^ e)
        {
            this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->Close();
        }

        // Kept separate because native RAII objects and managed finally
        // blocks should not be mixed in the same C++/CLI function.
        bool Authenticate(String^ email, String^ password)
        {
            sql::mysql::MySQL_Driver* driver =
                sql::mysql::get_mysql_driver_instance();
            std::unique_ptr<sql::Connection> con(driver->connect(
                "tcp://127.0.0.1:3306", "root", "rasu"));
            con->setSchema("vegdb");
            std::unique_ptr<sql::Statement> charset(con->createStatement());
            charset->execute("SET NAMES utf8mb4");

            std::unique_ptr<sql::PreparedStatement> query(con->prepareStatement(
                "SELECT userid, CustomerName, Email, Password "
                "FROM users WHERE Email = ? LIMIT 1"));
            query->setString(1, ToUtf8(email));
            std::unique_ptr<sql::ResultSet> rows(query->executeQuery());
            if (!rows->next()) return false;

            String^ stored = FromUtf8(rows->getString("Password").asStdString());
            if (!VerifyPassword(password, stored)) return false;

            loggedInUserId = FromUtf8(rows->getString("userid").asStdString());
            loggedInName = FromUtf8(rows->getString("CustomerName").asStdString());
            loggedInEmail = FromUtf8(rows->getString("Email").asStdString());
            return true;
        }

        System::Void loginBTN_Click(Object^ sender, EventArgs^ e)
        {
            String^ email = this->EmailTXT->Text->Trim();
            String^ password = this->PassTXT->Text; // Keep password spaces.
            this->statusLBL->Text = "";
            if (String::IsNullOrWhiteSpace(email) || String::IsNullOrEmpty(password))
            {
                this->statusLBL->Text = "Please enter your email and password.";
                return;
            }

            loggedInUserId = nullptr;
            loggedInName = nullptr;
            loggedInEmail = nullptr;
            this->loginBTN->Enabled = false;
            this->cancelBTN->Enabled = false;
            this->UseWaitCursor = true;
            bool authenticated = false;
            try
            {
                try { authenticated = Authenticate(email, password); }
                catch (const sql::SQLException& ex)
                {
                    MessageBox::Show(this, gcnew String(ex.what()),
                        "Database error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }
                catch (const std::exception& ex)
                {
                    MessageBox::Show(this, gcnew String(ex.what()), "Login error");
                    return;
                }
                catch (System::Exception^ ex)
                {
                    MessageBox::Show(this, ex->Message, "Login error");
                    return;
                }
            }
            finally
            {
                this->UseWaitCursor = false;
                this->loginBTN->Enabled = true;
                this->cancelBTN->Enabled = true;
            }

            this->PassTXT->Clear();
            if (!authenticated)
            {
                this->statusLBL->Text = "Incorrect email or password. Please try again.";
                this->PassTXT->Focus();
                return;
            }

            MessageBox::Show(this,
                String::Concat("Login successful, ", loggedInName, "!"),
                "VegWay", MessageBoxButtons::OK, MessageBoxIcon::Information);
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();

        }
    private: System::Void EmailTXT_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    }
private: System::Void loginPanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}
private: System::Void titleLabel_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void LoginForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}

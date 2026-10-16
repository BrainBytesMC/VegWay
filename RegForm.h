#pragma once
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <mysql_connection.h>
#include <mysql_driver.h>

#include <memory>
#include <string>
#include <vcclr.h>

namespace VegWay {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class RegForm : public System::Windows::Forms::Form
	{
	public:
		RegForm(void)

		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RegForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ VegWay;

	private: System::Windows::Forms::TextBox^ NameTXT;
	private: System::Windows::Forms::TextBox^ EmailTXT;
	private: System::Windows::Forms::TextBox^ MobNumTXT;
	private: System::Windows::Forms::TextBox^ PassTXT;
	private: System::Windows::Forms::Button^ RegBTN;
	private: System::Windows::Forms::Button^ cancelBTN;
	private: System::Windows::Forms::Label^ VERSION;
	private: System::Windows::Forms::Label^ Team;
	private: System::Windows::Forms::PictureBox^ pictureBox1;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(RegForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->VegWay = (gcnew System::Windows::Forms::Label());
			this->NameTXT = (gcnew System::Windows::Forms::TextBox());
			this->EmailTXT = (gcnew System::Windows::Forms::TextBox());
			this->MobNumTXT = (gcnew System::Windows::Forms::TextBox());
			this->PassTXT = (gcnew System::Windows::Forms::TextBox());
			this->RegBTN = (gcnew System::Windows::Forms::Button());
			this->cancelBTN = (gcnew System::Windows::Forms::Button());
			this->VERSION = (gcnew System::Windows::Forms::Label());
			this->Team = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Montserrat", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(204, 185);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(95, 27);
			this->label1->TabIndex = 0;
			this->label1->Text = L"NAME : ";
			this->label1->Click += gcnew System::EventHandler(this, &RegForm::label1_Click);
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Montserrat", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(204, 238);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(145, 27);
			this->label2->TabIndex = 1;
			this->label2->Text = L"EMAIL :";
			// 
			// label3
			// 
			this->label3->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Montserrat", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(204, 283);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(246, 27);
			this->label3->TabIndex = 2;
			this->label3->Text = L"MOBILE NUMBER :";
			this->label3->Click += gcnew System::EventHandler(this, &RegForm::label3_Click);
			// 
			// label4
			// 
			this->label4->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Montserrat", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(204, 328);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(206, 27);
			this->label4->TabIndex = 3;
			this->label4->Text = L"PASSWORD :";
			// 
			// VegWay
			// 
			this->VegWay->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->VegWay->AutoSize = true;
			this->VegWay->BackColor = System::Drawing::Color::Transparent;
			this->VegWay->Font = (gcnew System::Drawing::Font(L"Montserrat", 22.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->VegWay->ForeColor = System::Drawing::Color::Green;
			this->VegWay->Location = System::Drawing::Point(350, 91);
			this->VegWay->Name = L"VegWay";
			this->VegWay->Size = System::Drawing::Size(432, 51);
			this->VegWay->TabIndex = 4;
			this->VegWay->Text = L"VegWay Registration";
			this->VegWay->Click += gcnew System::EventHandler(this, &RegForm::label5_Click);
			// 
			// NameTXT
			// 
			this->NameTXT->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->NameTXT->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->NameTXT->Location = System::Drawing::Point(305, 190);
			this->NameTXT->MaxLength = 100;
			this->NameTXT->Name = L"NameTXT";
			this->NameTXT->Size = System::Drawing::Size(559, 22);
			this->NameTXT->TabIndex = 5;
			this->NameTXT->TextChanged += gcnew System::EventHandler(this, &RegForm::textBox1_TextChanged);
			// 
			// EmailTXT
			// 
			this->EmailTXT->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->EmailTXT->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->EmailTXT->Location = System::Drawing::Point(302, 243);
			this->EmailTXT->MaxLength = 254;
			this->EmailTXT->Name = L"EmailTXT";
			this->EmailTXT->Size = System::Drawing::Size(562, 22);
			this->EmailTXT->TabIndex = 6;
			// 
			// MobNumTXT
			// 
			this->MobNumTXT->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->MobNumTXT->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->MobNumTXT->Location = System::Drawing::Point(431, 289);
			this->MobNumTXT->MaxLength = 20;
			this->MobNumTXT->Name = L"MobNumTXT";
			this->MobNumTXT->Size = System::Drawing::Size(433, 22);
			this->MobNumTXT->TabIndex = 7;
			// 
			// PassTXT
			// 
			this->PassTXT->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PassTXT->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->PassTXT->Location = System::Drawing::Point(363, 333);
			this->PassTXT->MaxLength = 128;
			this->PassTXT->Name = L"PassTXT";
			this->PassTXT->PasswordChar = '*';
			this->PassTXT->Size = System::Drawing::Size(501, 22);
			this->PassTXT->TabIndex = 8;
			// 
			// RegBTN
			// 
			this->RegBTN->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->RegBTN->BackColor = System::Drawing::Color::Green;
			this->RegBTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RegBTN->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->RegBTN->Location = System::Drawing::Point(240, 428);
			this->RegBTN->Name = L"RegBTN";
			this->RegBTN->Size = System::Drawing::Size(295, 54);
			this->RegBTN->TabIndex = 9;
			this->RegBTN->Text = L"Register";
			this->RegBTN->UseVisualStyleBackColor = false;
			this->RegBTN->Click += gcnew System::EventHandler(this, &RegForm::RegBTN_Click);
			// 
			// cancelBTN
			// 
			this->cancelBTN->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->cancelBTN->BackColor = System::Drawing::Color::MintCream;
			this->cancelBTN->Cursor = System::Windows::Forms::Cursors::Hand;
			this->cancelBTN->FlatAppearance->BorderColor = System::Drawing::Color::Red;
			this->cancelBTN->FlatAppearance->BorderSize = 0;
			this->cancelBTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cancelBTN->Location = System::Drawing::Point(553, 428);
			this->cancelBTN->Name = L"cancelBTN";
			this->cancelBTN->Size = System::Drawing::Size(295, 54);
			this->cancelBTN->TabIndex = 10;
			this->cancelBTN->Text = L"Cancel";
			this->cancelBTN->UseVisualStyleBackColor = false;
			this->cancelBTN->Click += gcnew System::EventHandler(this, &RegForm::cancelBTN_Click);
			// 
			// VERSION
			// 
			this->VERSION->AutoSize = true;
			this->VERSION->BackColor = System::Drawing::Color::Transparent;
			this->VERSION->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->VERSION->Location = System::Drawing::Point(12, 9);
			this->VERSION->Name = L"VERSION";
			this->VERSION->Size = System::Drawing::Size(106, 19);
			this->VERSION->TabIndex = 11;
			this->VERSION->Text = L"VERSION 01.01";
			// 
			// Team
			// 
			this->Team->AutoSize = true;
			this->Team->BackColor = System::Drawing::Color::Transparent;
			this->Team->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Team->Location = System::Drawing::Point(12, 25);
			this->Team->Name = L"Team";
			this->Team->Size = System::Drawing::Size(127, 19);
			this->Team->TabIndex = 12;
			this->Team->Text = L"BRAIN BYTES 2026";
			this->Team->Click += gcnew System::EventHandler(this, &RegForm::label5_Click_1);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(271, 94);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(60, 45);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 13;
			this->pictureBox1->TabStop = false;
			// 
			// RegForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Honeydew;
			this->ClientSize = System::Drawing::Size(1046, 583);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->Team);
			this->Controls->Add(this->VERSION);
			this->Controls->Add(this->cancelBTN);
			this->Controls->Add(this->RegBTN);
			this->Controls->Add(this->PassTXT);
			this->Controls->Add(this->MobNumTXT);
			this->Controls->Add(this->EmailTXT);
			this->Controls->Add(this->NameTXT);
			this->Controls->Add(this->VegWay);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"RegForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"VegWay Registration";
			this->Load += gcnew System::EventHandler(this, &RegForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private:
			// Convert .NET text to UTF-8 for MySQL.
			static std::string ToUtf8(System::String^ value)
			{
				array<System::Byte>^ bytes =
					System::Text::Encoding::UTF8->GetBytes(value);

				if (bytes->Length == 0)
				{
					return std::string();
				}

				pin_ptr<System::Byte> pinned = &bytes[0];

				return std::string(
					reinterpret_cast<const char*>(pinned),
					bytes->Length
				);
			}

			// Store algorithm, iterations, salt, and hash together.
			static System::String^ HashPassword(
				System::String^ password)
			{
				array<System::Byte>^ salt =
					gcnew array<System::Byte>(16);

				System::Security::Cryptography::RandomNumberGenerator^ rng =
					System::Security::Cryptography::
					RandomNumberGenerator::Create();

				rng->GetBytes(salt);
				delete rng;

				System::Security::Cryptography::Rfc2898DeriveBytes^ pbkdf2 =
					gcnew System::Security::Cryptography::
					Rfc2898DeriveBytes(
						password,
						salt,
						600000,
						System::Security::Cryptography::
						HashAlgorithmName::SHA256
					);

				array<System::Byte>^ hash = pbkdf2->GetBytes(32);
				delete pbkdf2;

				return System::String::Concat(
					"PBKDF2-SHA256$600000$",
					System::Convert::ToBase64String(salt),
					"$",
					System::Convert::ToBase64String(hash)
				);
			}

	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void cancelBTN_Click(System::Object^ sender, System::EventArgs^ e) {
		Close();
	}


	private: System::Void RegBTN_Click(
		System::Object^ sender,
		System::EventArgs^ e)
{
	String^ customerName = NameTXT->Text->Trim();
	String^ email = EmailTXT->Text->Trim();
	String^ phone = MobNumTXT->Text->Trim();

	// Do not Trim() passwords: spaces may be intentional.
	String^ password = PassTXT->Text;

	// 1. Check required fields.
	if (String::IsNullOrWhiteSpace(customerName) ||
		String::IsNullOrWhiteSpace(email) ||
		String::IsNullOrWhiteSpace(phone) ||
		String::IsNullOrWhiteSpace(password))
	{
		MessageBox::Show(
			"Please fill in all fields.",
			"Missing information"
		);
		return;
	}

	// 2. Check lengths.
	if (customerName->Length > 100 ||
		email->Length > 254 ||
		phone->Length > 20 ||
		password->Length > 128)
	{
		MessageBox::Show(
			"One or more fields are too long.",
			"Invalid information"
		);
		return;
	}

	if (password->Length < 8)
	{
		MessageBox::Show(
			"Use a password with at least 8 characters.",
			"Password"
		);
		return;
	}

	// 3. Basic email format check.
	if (!System::Text::RegularExpressions::Regex::IsMatch(
		email,
		"^[^\\s@]+@[^\\s@]+\\.[^\\s@]+$"))
	{
		MessageBox::Show(
			"Please enter a valid email address.",
			"Email"
		);
		return;
	}

	RegBTN->Enabled = false;

	try
	{
		// 4. Hash the password.
		String^ storedPassword = HashPassword(password);

		// 5. Connect to MySQL.
		sql::mysql::MySQL_Driver* driver =
			sql::mysql::get_mysql_driver_instance();

		std::unique_ptr<sql::Connection> con(
			driver->connect(
				"tcp://127.0.0.1:3306",
				"root",
				"rasu"
			)
		);

		con->setSchema("vegdb");

		// The values passed below are UTF-8.
		std::unique_ptr<sql::Statement> charsetStmt(
			con->createStatement()
		);
		charsetStmt->execute("SET NAMES utf8mb4");

		// 6. Prepare the INSERT.
		std::unique_ptr<sql::PreparedStatement> insertStmt(
			con->prepareStatement(
				"INSERT INTO users "
				"(CustomerName, Email, Phonenumber, Password) "
				"VALUES (?, ?, ?, ?)"
			)
		);

		// 7. Supply each value separately.
		insertStmt->setString(1, ToUtf8(customerName));
		insertStmt->setString(2, ToUtf8(email));
		insertStmt->setString(3, ToUtf8(phone));
		insertStmt->setString(4, ToUtf8(storedPassword));

		// 8. Save the row.
		int rowsInserted = insertStmt->executeUpdate();

		if (rowsInserted == 1)
		{
			MessageBox::Show(
				String::Concat(
					"Registration successful, ",customerName,"!"
				),
				"VegWay"
			);

			this->Close();
			return;
		}
	}
	catch (const sql::SQLException& ex)
	{
		if (ex.getErrorCode() == 1062)
		{
			MessageBox::Show(
				"This email is already registered.",
				"Registration"
			);
		}
		else
		{
			MessageBox::Show(
				gcnew String(ex.what()),
				"Database error"
			);
		}
	}
	catch (System::Exception^ ex)
	{
		MessageBox::Show(
			ex->Message,
			"Registration error"
		);
	}

	RegBTN->Enabled = true;
}
private: System::Void label5_Click_1(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
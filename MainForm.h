#pragma once

#include "RegForm.h"
#include "LoginForm.h"




namespace VegWay {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		property System::String^ LoggedInUserId;
		property System::String^ LoggedInName;
		property System::String^ LoggedInEmail;
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	protected:
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Panel^ panel6;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Panel^ panel5;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::LinkLabel^ LinkBTN;

	private: System::Windows::Forms::Label^ Team;
	private: System::Windows::Forms::Label^ VERSION;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Button^ LogBTN;

	private: System::Windows::Forms::Button^ RegBTN;

	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Label^ label19;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->Team = (gcnew System::Windows::Forms::Label());
			this->VERSION = (gcnew System::Windows::Forms::Label());
			this->LinkBTN = (gcnew System::Windows::Forms::LinkLabel());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->LogBTN = (gcnew System::Windows::Forms::Button());
			this->RegBTN = (gcnew System::Windows::Forms::Button());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->panel6->SuspendLayout();
			this->panel5->SuspendLayout();
			this->panel4->SuspendLayout();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->panel3->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::Honeydew;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->Team);
			this->panel1->Controls->Add(this->VERSION);
			this->panel1->Controls->Add(this->LinkBTN);
			this->panel1->Controls->Add(this->panel6);
			this->panel1->Controls->Add(this->panel5);
			this->panel1->Controls->Add(this->panel4);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->panel2);
			this->panel1->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 320);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1846, 569);
			this->panel1->TabIndex = 0;
			// 
			// Team
			// 
			this->Team->AutoSize = true;
			this->Team->BackColor = System::Drawing::Color::Transparent;
			this->Team->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Team->Location = System::Drawing::Point(308, 508);
			this->Team->Name = L"Team";
			this->Team->Size = System::Drawing::Size(193, 27);
			this->Team->TabIndex = 14;
			this->Team->Text = L"BRAIN BYTES 2026";
			// 
			// VERSION
			// 
			this->VERSION->AutoSize = true;
			this->VERSION->BackColor = System::Drawing::Color::Transparent;
			this->VERSION->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->VERSION->Location = System::Drawing::Point(29, 508);
			this->VERSION->Name = L"VERSION";
			this->VERSION->Size = System::Drawing::Size(273, 27);
			this->VERSION->TabIndex = 13;
			this->VERSION->Text = L"VERSION 01.01 | VEGWAY |";
			this->VERSION->Click += gcnew System::EventHandler(this, &MainForm::VERSION_Click);
			// 
			// LinkBTN
			// 
			this->LinkBTN->AutoSize = true;
			this->LinkBTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LinkBTN->LinkColor = System::Drawing::Color::Green;
			this->LinkBTN->Location = System::Drawing::Point(189, 395);
			this->LinkBTN->Name = L"LinkBTN";
			this->LinkBTN->Size = System::Drawing::Size(453, 29);
			this->LinkBTN->TabIndex = 6;
			this->LinkBTN->TabStop = true;
			this->LinkBTN->Text = L"Click here to watch Introduction Video";
			this->LinkBTN->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainForm::LinkBTN_LinkClicked);
			// 
			// panel6
			// 
			this->panel6->BackColor = System::Drawing::Color::PaleGreen;
			this->panel6->Controls->Add(this->label13);
			this->panel6->Controls->Add(this->label10);
			this->panel6->Location = System::Drawing::Point(46, 295);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(748, 67);
			this->panel6->TabIndex = 5;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Montserrat", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->ForeColor = System::Drawing::Color::Green;
			this->label13->Location = System::Drawing::Point(85, 13);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(313, 39);
			this->label13->TabIndex = 8;
			this->label13->Text = L"Come back Anytime";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Montserrat", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::Color::Green;
			this->label10->Location = System::Drawing::Point(19, 13);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(56, 41);
			this->label10->TabIndex = 8;
			this->label10->Text = L"03";
			// 
			// panel5
			// 
			this->panel5->BackColor = System::Drawing::Color::PaleGreen;
			this->panel5->Controls->Add(this->label12);
			this->panel5->Controls->Add(this->label9);
			this->panel5->Location = System::Drawing::Point(46, 217);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(748, 67);
			this->panel5->TabIndex = 4;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Montserrat", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->ForeColor = System::Drawing::Color::Green;
			this->label12->Location = System::Drawing::Point(81, 14);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(326, 39);
			this->label12->TabIndex = 7;
			this->label12->Text = L"Get to know VegWay";
			this->label12->Click += gcnew System::EventHandler(this, &MainForm::label12_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Montserrat", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::Green;
			this->label9->Location = System::Drawing::Point(19, 12);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(56, 41);
			this->label9->TabIndex = 7;
			this->label9->Text = L"02";
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::Color::PaleGreen;
			this->panel4->Controls->Add(this->label11);
			this->panel4->Controls->Add(this->label8);
			this->panel4->Location = System::Drawing::Point(46, 139);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(748, 67);
			this->panel4->TabIndex = 3;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Montserrat", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::Color::Green;
			this->label11->Location = System::Drawing::Point(85, 16);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(302, 39);
			this->label11->TabIndex = 6;
			this->label11->Text = L"Creat Your Account";
			this->label11->Click += gcnew System::EventHandler(this, &MainForm::label11_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Montserrat", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::Green;
			this->label8->Location = System::Drawing::Point(19, 14);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(50, 41);
			this->label8->TabIndex = 6;
			this->label8->Text = L"01";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Montserrat", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::Black;
			this->label3->Location = System::Drawing::Point(81, 70);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(549, 50);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Your Journey Strats here. Create your account, \r\nlearn about the app,and ake your"
				L" next step with VegWay.";
			this->label3->Click += gcnew System::EventHandler(this, &MainForm::label3_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Montserrat", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::Green;
			this->label2->Location = System::Drawing::Point(38, 22);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(263, 25);
			this->label2->TabIndex = 1;
			this->label2->Text = L"FRESH SRILANKA! with US.";
			// 
			// panel2
			// 
			this->panel2->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->panel2->BackColor = System::Drawing::Color::MintCream;
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->label19);
			this->panel2->Controls->Add(this->label18);
			this->panel2->Controls->Add(this->label17);
			this->panel2->Controls->Add(this->LogBTN);
			this->panel2->Controls->Add(this->RegBTN);
			this->panel2->Controls->Add(this->label16);
			this->panel2->Controls->Add(this->label15);
			this->panel2->Controls->Add(this->label14);
			this->panel2->Location = System::Drawing::Point(855, 32);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(904, 490);
			this->panel2->TabIndex = 0;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->BackColor = System::Drawing::Color::Transparent;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label19->ForeColor = System::Drawing::Color::DarkGreen;
			this->label19->Location = System::Drawing::Point(19, 441);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(315, 23);
			this->label19->TabIndex = 22;
			this->label19->Text = L"Welcome to the VegWay community.";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->BackColor = System::Drawing::Color::Transparent;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label18->ForeColor = System::Drawing::Color::DarkGreen;
			this->label18->Location = System::Drawing::Point(19, 418);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(226, 23);
			this->label18->TabIndex = 21;
			this->label18->Text = L"Simple. Fresh. Welcoming.\r\n";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->BackColor = System::Drawing::Color::Transparent;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->label17->Location = System::Drawing::Point(339, 275);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(216, 23);
			this->label17->TabIndex = 20;
			this->label17->Text = L"Already have an account\?";
			// 
			// LogBTN
			// 
			this->LogBTN->BackColor = System::Drawing::Color::Honeydew;
			this->LogBTN->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->LogBTN->Cursor = System::Windows::Forms::Cursors::Hand;
			this->LogBTN->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->LogBTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LogBTN->ForeColor = System::Drawing::Color::MediumSeaGreen;
			this->LogBTN->Location = System::Drawing::Point(39, 312);
			this->LogBTN->Name = L"LogBTN";
			this->LogBTN->Size = System::Drawing::Size(811, 62);
			this->LogBTN->TabIndex = 19;
			this->LogBTN->Text = L"Login";
			this->LogBTN->UseVisualStyleBackColor = false;
			this->LogBTN->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// RegBTN
			// 
			this->RegBTN->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(66)));
			this->RegBTN->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->RegBTN->Cursor = System::Windows::Forms::Cursors::Hand;
			this->RegBTN->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->RegBTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RegBTN->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->RegBTN->Location = System::Drawing::Point(39, 200);
			this->RegBTN->Name = L"RegBTN";
			this->RegBTN->Size = System::Drawing::Size(811, 62);
			this->RegBTN->TabIndex = 18;
			this->RegBTN->Text = L"Create account";
			this->RegBTN->UseVisualStyleBackColor = false;
			this->RegBTN->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->BackColor = System::Drawing::Color::Transparent;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->ForeColor = System::Drawing::Color::DarkGreen;
			this->label16->Location = System::Drawing::Point(19, 134);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(300, 46);
			this->label16->TabIndex = 17;
			this->label16->Text = L"New to VegWay\? Create an account\r\nwith a few simple details.\r\n";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->BackColor = System::Drawing::Color::Transparent;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->ForeColor = System::Drawing::Color::DarkSlateGray;
			this->label15->Location = System::Drawing::Point(15, 69);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(270, 44);
			this->label15->TabIndex = 16;
			this->label15->Text = L"Your next step,";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->BackColor = System::Drawing::Color::Transparent;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->ForeColor = System::Drawing::Color::DarkGreen;
			this->label14->Location = System::Drawing::Point(18, 19);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(210, 27);
			this->label14->TabIndex = 15;
			this->label14->Text = L"LET\'S GET STARTED";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"PRIMETIME", 28.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(66)));
			this->label1->Location = System::Drawing::Point(104, 23);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(592, 63);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Welcome to VegWay";
			this->label1->Click += gcnew System::EventHandler(this, &MainForm::label1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(12, 23);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(85, 70);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::Green;
			this->label4->Location = System::Drawing::Point(134, 135);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(245, 150);
			this->label4->TabIndex = 3;
			this->label4->Text = L"\r\n     Kavindu Weerathunge\r\n     Nethmi Maleesha\r\n     Madusha Sewwandi\r\n     Ama"
				L"sha Malsarani\r\n     Chathura Jayamal\r\n";
			this->label4->Click += gcnew System::EventHandler(this, &MainForm::label4_Click);
			// 
			// panel3
			// 
			this->panel3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->panel3->BackColor = System::Drawing::Color::Honeydew;
			this->panel3->Controls->Add(this->label6);
			this->panel3->Location = System::Drawing::Point(514, 106);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(1219, 179);
			this->panel3->TabIndex = 4;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::DarkGreen;
			this->label6->Location = System::Drawing::Point(103, 66);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(1008, 43);
			this->label6->TabIndex = 6;
			this->label6->Text = L"Sri Lanka\'s No.01 Vegitables Trading Managment System";
			this->label6->Click += gcnew System::EventHandler(this, &MainForm::label6_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Montserrat ExtraBold", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::MediumSeaGreen;
			this->label5->Location = System::Drawing::Point(39, 121);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(212, 25);
			this->label5->TabIndex = 5;
			this->label5->Text = L"Our Team Members -";
			this->label5->Click += gcnew System::EventHandler(this, &MainForm::label5_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::Transparent;
			this->label7->Font = (gcnew System::Drawing::Font(L"PRIMETIME", 28.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::ForestGreen;
			this->label7->Location = System::Drawing::Point(743, 23);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(2003, 63);
			this->label7->TabIndex = 6;
			this->label7->Text = L"----------------------------------------------------";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(1846, 889);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Welcome to VegWay";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel6->ResumeLayout(false);
			this->panel6->PerformLayout();
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label6_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label11_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label12_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void VERSION_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	VegWay::LoginForm^ login = gcnew VegWay::LoginForm();
	bool success = false;
	try {
		if (login->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
			LoggedInUserId = login->LoggedInUserId;
			LoggedInName = login->LoggedInName;
			LoggedInEmail = login->LoggedInEmail;
			success = true;
		}
	}
	finally { delete login; }

	if (success) {
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}


}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	VegWay::RegForm^ registration = gcnew VegWay::RegForm();

	try
	{
		registration->ShowDialog(this);
	}
	finally
	{
		delete registration;
	}
}
private: System::Void LinkBTN_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {

	System::Diagnostics::ProcessStartInfo^ link =
		gcnew System::Diagnostics::ProcessStartInfo(
			"https://www.youtube.com/@Rasu_Motivation");

	link->UseShellExecute = true;
	System::Diagnostics::Process::Start(link);
}
};
}

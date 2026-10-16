#pragma once
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

namespace VegWay {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ItemAddForm
	/// </summary>
	public ref class ItemAddForm : public System::Windows::Forms::Form
	{
	public:
		ItemAddForm(void)
		{
			InitializeComponent();
		}

		// The market supplies the authenticated user's ID.
		ItemAddForm(System::String^ sellerId)
		{
			InitializeComponent();
			sellerUserId = sellerId;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ItemAddForm()
		{
			DisposePhoto();
			if (components)
			{
				delete components;
			}
		}

	private:
		// Variable to store selected image file path
		String^ selectedImagePath;
		System::String^ sellerUserId;
		array<System::Byte>^ selectedImageBytes;
		bool saving;
		System::Windows::Forms::Label^ lblCategory;
		System::Windows::Forms::ComboBox^ cmbCategory;
		void DisposePhoto();

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ txtName;
	private: System::Windows::Forms::TextBox^ txtPrice;
	private: System::Windows::Forms::TextBox^ txtQuantity;
	private: System::Windows::Forms::TextBox^ txtLocation;
	private: System::Windows::Forms::TextBox^ txtPhone;
	private: System::Windows::Forms::PictureBox^ picPhoto;
	private: System::Windows::Forms::Button^ btnBrowse;
	private: System::Windows::Forms::ComboBox^ cmbCurrency;
	private: System::Windows::Forms::Button^ btnAddItem;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ItemAddForm::typeid));
			this->lblCategory = (gcnew System::Windows::Forms::Label());
			this->cmbCategory = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->txtName = (gcnew System::Windows::Forms::TextBox());
			this->txtPrice = (gcnew System::Windows::Forms::TextBox());
			this->txtQuantity = (gcnew System::Windows::Forms::TextBox());
			this->txtLocation = (gcnew System::Windows::Forms::TextBox());
			this->txtPhone = (gcnew System::Windows::Forms::TextBox());
			this->picPhoto = (gcnew System::Windows::Forms::PictureBox());
			this->btnBrowse = (gcnew System::Windows::Forms::Button());
			this->cmbCurrency = (gcnew System::Windows::Forms::ComboBox());
			this->btnAddItem = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picPhoto))->BeginInit();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Green;
			this->label1->Location = System::Drawing::Point(147, 41);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(414, 39);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Item add to vegway market";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(36, 26);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(104, 22);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Item Name ";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(36, 77);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(139, 22);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Price (per 1 kg) ";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(36, 125);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(113, 22);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Quantity(kg)";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(38, 172);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(78, 22);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Location";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(36, 283);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(106, 22);
			this->label6->TabIndex = 5;
			this->label6->Text = L"Add picture";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(38, 226);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(100, 22);
			this->label7->TabIndex = 6;
			this->label7->Text = L"Contact No";
			// 
			// txtName
			// 
			this->txtName->Location = System::Drawing::Point(226, 26);
			this->txtName->Name = L"txtName";
			this->txtName->Size = System::Drawing::Size(207, 22);
			this->txtName->TabIndex = 7;
			// 
			// txtPrice
			// 
			this->txtPrice->Location = System::Drawing::Point(311, 77);
			this->txtPrice->Name = L"txtPrice";
			this->txtPrice->Size = System::Drawing::Size(122, 22);
			this->txtPrice->TabIndex = 8;
			// 
			// txtQuantity
			// 
			this->txtQuantity->Location = System::Drawing::Point(226, 124);
			this->txtQuantity->Name = L"txtQuantity";
			this->txtQuantity->Size = System::Drawing::Size(207, 22);
			this->txtQuantity->TabIndex = 9;
			// 
			// txtLocation
			// 
			this->txtLocation->Location = System::Drawing::Point(226, 172);
			this->txtLocation->Name = L"txtLocation";
			this->txtLocation->Size = System::Drawing::Size(207, 22);
			this->txtLocation->TabIndex = 10;
			// 
			// txtPhone
			// 
			this->txtPhone->Location = System::Drawing::Point(226, 226);
			this->txtPhone->Name = L"txtPhone";
			this->txtPhone->Size = System::Drawing::Size(207, 22);
			this->txtPhone->TabIndex = 12;
			// 
			// picPhoto
			// 
			this->picPhoto->BackColor = System::Drawing::Color::Transparent;
			this->picPhoto->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picPhoto->Location = System::Drawing::Point(226, 283);
			this->picPhoto->Name = L"picPhoto";
			this->picPhoto->Size = System::Drawing::Size(207, 152);
			this->picPhoto->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picPhoto->TabIndex = 13;
			this->picPhoto->TabStop = false;
			// 
			// btnBrowse
			// 
			this->btnBrowse->BackColor = System::Drawing::Color::LightGray;
			this->btnBrowse->Location = System::Drawing::Point(318, 445);
			this->btnBrowse->Name = L"btnBrowse";
			this->btnBrowse->Size = System::Drawing::Size(115, 30);
			this->btnBrowse->TabIndex = 14;
			this->btnBrowse->Text = L"Browse Photo";
			this->btnBrowse->UseVisualStyleBackColor = false;
			this->btnBrowse->Click += gcnew System::EventHandler(this, &ItemAddForm::btnBrowse_Click);
			// 
			// cmbCurrency
			// 
			this->cmbCurrency->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbCurrency->FormattingEnabled = true;
			this->cmbCurrency->Location = System::Drawing::Point(226, 77);
			this->cmbCurrency->Name = L"cmbCurrency";
			this->cmbCurrency->Size = System::Drawing::Size(79, 24);
			this->cmbCurrency->TabIndex = 15;
			// 
			// btnAddItem
			// 
			this->btnAddItem->BackColor = System::Drawing::Color::ForestGreen;
			this->btnAddItem->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 10, System::Drawing::FontStyle::Bold));
			this->btnAddItem->ForeColor = System::Drawing::Color::White;
			this->btnAddItem->Location = System::Drawing::Point(366, 495);
			this->btnAddItem->Name = L"btnAddItem";
			this->btnAddItem->Size = System::Drawing::Size(207, 40);
			this->btnAddItem->TabIndex = 16;
			this->btnAddItem->Text = L"Add Item";
			this->btnAddItem->UseVisualStyleBackColor = false;
			this->btnAddItem->Click += gcnew System::EventHandler(this, &ItemAddForm::btnAddItem_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::WhiteSmoke;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->btnAddItem);
			this->panel1->Controls->Add(this->cmbCurrency);
			this->panel1->Controls->Add(this->btnBrowse);
			this->panel1->Controls->Add(this->txtPhone);
			this->panel1->Controls->Add(this->label7);
			this->panel1->Controls->Add(this->picPhoto);
			this->panel1->Controls->Add(this->txtLocation);
			this->panel1->Controls->Add(this->txtQuantity);
			this->panel1->Controls->Add(this->txtPrice);
			this->panel1->Controls->Add(this->txtName);
			this->panel1->Controls->Add(this->label6);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Location = System::Drawing::Point(34, 103);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(601, 574);
			this->panel1->TabIndex = 17;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(80, 36);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(61, 44);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 18;
			this->pictureBox1->TabStop = false;
			// Category: kept beside/below the existing Add Item button.
			this->lblCategory->AutoSize = true;
			this->lblCategory->Location = System::Drawing::Point(40, 493);
			this->lblCategory->Name = L"lblCategory";
			this->lblCategory->Text = L"Vegetable category";
			this->cmbCategory->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbCategory->FormattingEnabled = true;
			this->cmbCategory->Items->AddRange(gcnew cli::array<System::Object^>(5) {
				L"Leafy vegetables", L"Root vegetables", L"Fruit vegetables", L"Beans & peas", L"Other"
			});
			this->cmbCategory->Location = System::Drawing::Point(40, 519);
			this->cmbCategory->Name = L"cmbCategory";
			this->cmbCategory->Size = System::Drawing::Size(280, 24);
			this->cmbCategory->TabIndex = 17;
			this->cmbCategory->SelectedIndex = 4;
			this->panel1->Controls->Add(this->lblCategory);
			this->panel1->Controls->Add(this->cmbCategory);
			// The existing market/table store prices in rupees only.
			this->cmbCurrency->Items->AddRange(gcnew cli::array<System::Object^>(1) { L"Rs" });
			this->cmbCurrency->SelectedIndex = 0;
			this->cmbCurrency->Enabled = false;
			this->txtName->MaxLength = 100;
			this->txtLocation->MaxLength = 150;
			this->txtPhone->MaxLength = 20;
			this->txtPrice->MaxLength = 11;
			this->txtQuantity->MaxLength = 11;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->MaximizeBox = false;
			// 
			// ItemAddForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::MintCream;
			this->ClientSize = System::Drawing::Size(671, 706);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"ItemAddForm";
			this->Text = L"Sell Your Vegitables Now!";
			this->Load += gcnew System::EventHandler(this, &ItemAddForm::ItemAddForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picPhoto))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		System::Void ItemAddForm_Load(System::Object^ sender, System::EventArgs^ e);
		System::Void btnBrowse_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnAddItem_Click(System::Object^ sender, System::EventArgs^ e);
	};
}

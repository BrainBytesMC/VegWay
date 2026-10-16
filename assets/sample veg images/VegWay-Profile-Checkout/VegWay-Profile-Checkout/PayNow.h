#pragma once
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

namespace vegway {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for PayNow
	/// </summary>
	public ref class PayNow : public System::Windows::Forms::Form
	{
	public:
		PayNow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

        PayNow(System::String^ buyer, System::String^ item) {
            InitializeComponent(); buyerId=buyer; itemId=item;
            checkoutToken=System::Guid::NewGuid().ToString();
        }
        property System::String^ CompletedOrderId {System::String^ get(){return orderId;}}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PayNow()
		{
			if (components)
			{
				delete components;
			}
		}
    private:
        System::String^ buyerId;
        System::String^ itemId;
        System::String^ checkoutToken;
        System::String^ orderId;
        System::Decimal quotedPrice;
        bool ready;
        bool saving;
        void ReloadItem();
        void UpdateTotal(System::Object^ sender, System::EventArgs^ e);
        System::Windows::Forms::Label^ lblNotice;
        System::Windows::Forms::Button^ btnReload;
	private: System::Windows::Forms::Label^ IblTitle;
	private: System::Windows::Forms::Label^ Lblstock;
	private: System::Windows::Forms::TextBox^ txtstock;
	private: System::Windows::Forms::Label^ lblquantity;
	private: System::Windows::Forms::TextBox^ txtpricekg;
	private: System::Windows::Forms::NumericUpDown^ numquntity;
	private: System::Windows::Forms::Label^ lblpricekg;
	private: System::Windows::Forms::Label^ lbltotal;
	private: System::Windows::Forms::TextBox^ txttotal;
	private: System::Windows::Forms::Button^ btnpay;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Panel^ pnlorder;
	private: System::Windows::Forms::PictureBox^ pictureBox1;





	protected:

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(PayNow::typeid));
            this->lblNotice = (gcnew System::Windows::Forms::Label());
            this->btnReload = (gcnew System::Windows::Forms::Button());
			this->IblTitle = (gcnew System::Windows::Forms::Label());
			this->Lblstock = (gcnew System::Windows::Forms::Label());
			this->txtstock = (gcnew System::Windows::Forms::TextBox());
			this->lblquantity = (gcnew System::Windows::Forms::Label());
			this->txtpricekg = (gcnew System::Windows::Forms::TextBox());
			this->numquntity = (gcnew System::Windows::Forms::NumericUpDown());
			this->lblpricekg = (gcnew System::Windows::Forms::Label());
			this->lbltotal = (gcnew System::Windows::Forms::Label());
			this->txttotal = (gcnew System::Windows::Forms::TextBox());
			this->btnpay = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pnlorder = (gcnew System::Windows::Forms::Panel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numquntity))->BeginInit();
			this->pnlorder->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// IblTitle
			// 
			this->IblTitle->AutoSize = true;
			this->IblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 22.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->IblTitle->ForeColor = System::Drawing::Color::DarkGreen;
			this->IblTitle->Location = System::Drawing::Point(259, 62);
			this->IblTitle->Name = L"IblTitle";
			this->IblTitle->Size = System::Drawing::Size(194, 50);
			this->IblTitle->TabIndex = 0;
			this->IblTitle->Text = L"VEGWAY  ";
			// 
			// Lblstock
			// 
			this->Lblstock->AutoSize = true;
			this->Lblstock->Font = (gcnew System::Drawing::Font(L"Segoe UI Semilight", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Lblstock->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->Lblstock->Location = System::Drawing::Point(58, 39);
			this->Lblstock->Name = L"Lblstock";
			this->Lblstock->Size = System::Drawing::Size(160, 25);
			this->Lblstock->TabIndex = 1;
			this->Lblstock->Text = L"Available Stock       ";
			// 
			// txtstock
			// 
			this->txtstock->BackColor = System::Drawing::Color::White;
			this->txtstock->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtstock->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtstock->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->txtstock->Location = System::Drawing::Point(275, 33);
			this->txtstock->Name = L"txtstock";
			this->txtstock->ReadOnly = true;
			this->txtstock->Size = System::Drawing::Size(150, 31);
			this->txtstock->TabIndex = 2;
			// 
			// lblquantity
			// 
			this->lblquantity->AutoSize = true;
			this->lblquantity->Font = (gcnew System::Drawing::Font(L"Segoe UI Semilight", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblquantity->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lblquantity->Location = System::Drawing::Point(58, 80);
			this->lblquantity->Name = L"lblquantity";
			this->lblquantity->Size = System::Drawing::Size(159, 25);
			this->lblquantity->TabIndex = 3;
			this->lblquantity->Text = L"Order Quantity      ";
			// 
			// txtpricekg
			// 
			this->txtpricekg->BackColor = System::Drawing::Color::White;
			this->txtpricekg->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtpricekg->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtpricekg->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->txtpricekg->Location = System::Drawing::Point(275, 116);
			this->txtpricekg->Name = L"txtpricekg";
			this->txtpricekg->ReadOnly = true;
			this->txtpricekg->Size = System::Drawing::Size(150, 34);
			this->txtpricekg->TabIndex = 4;
			// 
			// numquntity
			// 
			this->numquntity->BackColor = System::Drawing::Color::White;
			this->numquntity->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->numquntity->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numquntity->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->numquntity->Location = System::Drawing::Point(275, 74);
			this->numquntity->Minimum = System::Decimal(0);
            this->numquntity->DecimalPlaces = 3;
            this->numquntity->Increment = System::Decimal(1, 0, 0, false, 3);
			this->numquntity->ValueChanged += gcnew System::EventHandler(this, &PayNow::UpdateTotal);
            this->numquntity->Name = L"numquntity";
			this->numquntity->Size = System::Drawing::Size(150, 31);
			this->numquntity->TabIndex = 5;
			this->numquntity->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// lblpricekg
			// 
			this->lblpricekg->AutoSize = true;
			this->lblpricekg->Font = (gcnew System::Drawing::Font(L"Segoe UI Semilight", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblpricekg->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lblpricekg->Location = System::Drawing::Point(58, 122);
			this->lblpricekg->Name = L"lblpricekg";
			this->lblpricekg->Size = System::Drawing::Size(158, 25);
			this->lblpricekg->TabIndex = 6;
			this->lblpricekg->Text = L"Price Per Kg           ";
			// 
			// lbltotal
			// 
			this->lbltotal->AutoSize = true;
			this->lbltotal->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbltotal->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lbltotal->Location = System::Drawing::Point(58, 164);
			this->lbltotal->Name = L"lbltotal";
			this->lbltotal->Size = System::Drawing::Size(158, 25);
			this->lbltotal->TabIndex = 7;
			this->lbltotal->Text = L"Total Price            ";
			// 
			// txttotal
			// 
			this->txttotal->BackColor = System::Drawing::Color::White;
			this->txttotal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txttotal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txttotal->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->txttotal->Location = System::Drawing::Point(275, 158);
			this->txttotal->Name = L"txttotal";
			this->txttotal->ReadOnly = true;
			this->txttotal->Size = System::Drawing::Size(150, 31);
			this->txttotal->TabIndex = 9;
			// 
			// btnpay
			// 
			this->btnpay->AutoSize = true;
			this->btnpay->BackColor = System::Drawing::Color::DarkGreen;
			this->btnpay->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnpay->ForeColor = System::Drawing::Color::White;
			this->btnpay->Location = System::Drawing::Point(139, 221);
			this->btnpay->Name = L"btnpay";
			this->btnpay->Size = System::Drawing::Size(150, 45);
			this->btnpay->TabIndex = 10;
			this->btnpay->Text = L"PAY NOW";
			this->btnpay->UseVisualStyleBackColor = false;
			this->btnpay->Click += gcnew System::EventHandler(this, &PayNow::btnpay_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = false;
            this->label1->AutoEllipsis = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::DarkGreen;
			this->label1->Location = System::Drawing::Point(253, 112);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(370, 45);
			this->label1->TabIndex = 11;
			this->label1->Text = L"Order And  Payment";
			// 
			// pnlorder
			// 
			this->pnlorder->BackColor = System::Drawing::Color::White;
			this->pnlorder->Controls->Add(this->Lblstock);
			this->pnlorder->Controls->Add(this->txtstock);
			this->pnlorder->Controls->Add(this->btnpay);
			this->pnlorder->Controls->Add(this->lblquantity);
			this->pnlorder->Controls->Add(this->txttotal);
			this->pnlorder->Controls->Add(this->numquntity);
			this->pnlorder->Controls->Add(this->lbltotal);
			this->pnlorder->Controls->Add(this->lblpricekg);
			this->pnlorder->Controls->Add(this->txtpricekg);
			this->pnlorder->Location = System::Drawing::Point(107, 167);
			this->pnlorder->Name = L"pnlorder";
			this->pnlorder->Size = System::Drawing::Size(451, 304);
			this->pnlorder->TabIndex = 12;
			this->pnlorder->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &PayNow::pnlorder_Paint);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::WhiteSmoke;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(177, 67);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(70, 70);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 13;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &PayNow::pictureBox1_Click);
			// 
			// PayNow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->ClientSize = System::Drawing::Size(649, 600);
            this->lblNotice->Location = System::Drawing::Point(40, 480);
            this->lblNotice->Size = System::Drawing::Size(570, 55);
            this->lblNotice->ForeColor = System::Drawing::Color::DarkGreen;
            this->lblNotice->Name = L"lblNotice";
            this->lblNotice->Text = L"Records an order and reduces stock. No money is transferred.";
            this->btnReload->Location = System::Drawing::Point(240, 540);
            this->btnReload->Size = System::Drawing::Size(160, 35);
            this->btnReload->Text = L"Reload stock / price";
            this->btnReload->Name = L"btnReload";
            this->btnReload->Click += gcnew System::EventHandler(this, &PayNow::ReloadClick);
            this->Controls->Add(this->lblNotice);
            this->Controls->Add(this->btnReload);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->pnlorder);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->IblTitle);
			this->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"PayNow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"VegWay -  Payment";
			this->Load += gcnew System::EventHandler(this, &PayNow::PayNow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numquntity))->EndInit();
			this->pnlorder->ResumeLayout(false);
			this->pnlorder->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
    private:
        System::Void PayNow_Load(System::Object^ sender, System::EventArgs^ e);
        System::Void pnlorder_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {}
        System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {}
        System::Void btnpay_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void ReloadClick(System::Object^ sender, System::EventArgs^ e);
};
}

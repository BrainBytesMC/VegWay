#pragma once
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>
#include "ItemAddForm.h"


namespace VegWay {
    public ref class VegWayMarket : public System::Windows::Forms::Form
    {
    public:
        VegWayMarket(void) { InitializeComponent(); 
        this->viewProfileItem->Click +=
            gcnew System::EventHandler(
                this, &VegWayMarket::ProfileAction);
        
        }
        VegWayMarket(System::String^ id, System::String^ name, System::String^ email) {
            InitializeComponent();
            userId = id; userName = name; userEmail = email;
        }
        property System::String^ CurrentUserId {
            System::String^ get() { return userId; }
        }
    protected:
        ~VegWayMarket() {
            DisposeMarket();
            if (components != nullptr) delete components;
        }
    private:
        System::String^ userId;
        System::String^ userName;
        System::String^ userEmail;
        System::String^ category;
        bool loading;
        System::Collections::Generic::List<System::Windows::Forms::Panel^>^ cards;
        System::Collections::Generic::List<System::Windows::Forms::Button^>^ categories;
        System::ComponentModel::IContainer^ components;
        System::Windows::Forms::TableLayoutPanel^ layout;
        System::Windows::Forms::TableLayoutPanel^ header;

        System::Windows::Forms::Panel^ heading;
        System::Windows::Forms::Label^ marketTitle;
        System::Windows::Forms::Label^ tagline;
        System::Windows::Forms::Button^ profile;
        System::Windows::Forms::ContextMenuStrip^ profileMenu;
        System::Windows::Forms::ToolStripMenuItem^ viewProfileItem;
        System::Windows::Forms::ToolStripMenuItem^ changeNameItem;
        System::Windows::Forms::ToolStripMenuItem^ changePasswordItem;
        System::Windows::Forms::TableLayoutPanel^ toolbar;
        System::Windows::Forms::Label^ searchLabel;
        System::Windows::Forms::TextBox^ search;
        System::Windows::Forms::Button^ refresh;
        System::Windows::Forms::TableLayoutPanel^ body;
        System::Windows::Forms::FlowLayoutPanel^ sidebar;
        System::Windows::Forms::Label^ categoryTitle;
        System::Windows::Forms::Button^ allButton;
        System::Windows::Forms::Button^ leafyButton;
        System::Windows::Forms::Button^ rootButton;
        System::Windows::Forms::Button^ fruitButton;
        System::Windows::Forms::Button^ beansButton;
        System::Windows::Forms::Button^ otherButton;
        System::Windows::Forms::Panel^ content;
        System::Windows::Forms::Label^ status;
        System::Windows::Forms::Panel^ products;
        System::Windows::Forms::Label^ empty;
    private: System::Windows::Forms::PictureBox^ pictureBox1;
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem1;
           System::Windows::Forms::Timer^ searchTimer;
           System::Drawing::Color Green();
           System::Windows::Forms::Label^ MakeLabel(System::String^ text, float size, bool bold);
           System::Windows::Forms::Button^ MakeButton(System::String^ text);
           void ClearCards();
           void AddCard(System::String^ id, System::String^ name, System::String^ price, System::Drawing::Image^ image);
           void ArrangeCards();
           void LoadProducts();
           void UpdateCategoryButtons();
           void FirstShown(System::Object^ sender, System::EventArgs^ e);
           void ProductsResize(System::Object^ sender, System::EventArgs^ e);
           void RefreshClick(System::Object^ sender, System::EventArgs^ e);
           void SearchChanged(System::Object^ sender, System::EventArgs^ e);
           void SearchTick(System::Object^ sender, System::EventArgs^ e);
           void CategoryClick(System::Object^ sender, System::EventArgs^ e);
           void ProfileClick(System::Object^ sender, System::EventArgs^ e);
           void ProfileAction(System::Object^ sender, System::EventArgs^ e);
           void SellClick(System::Object^ sender, System::EventArgs^ e);
           void BuyClick(System::Object^ sender, System::EventArgs^ e);
           bool IsDesignSurface();
           void DisposeMarket();
#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->components = (gcnew System::ComponentModel::Container());
               System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(VegWayMarket::typeid));
               this->layout = (gcnew System::Windows::Forms::TableLayoutPanel());
               this->header = (gcnew System::Windows::Forms::TableLayoutPanel());
               this->heading = (gcnew System::Windows::Forms::Panel());
               this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
               this->tagline = (gcnew System::Windows::Forms::Label());
               this->marketTitle = (gcnew System::Windows::Forms::Label());
               this->profile = (gcnew System::Windows::Forms::Button());
               this->button1 = (gcnew System::Windows::Forms::Button());
               this->toolbar = (gcnew System::Windows::Forms::TableLayoutPanel());
               this->searchLabel = (gcnew System::Windows::Forms::Label());
               this->search = (gcnew System::Windows::Forms::TextBox());
               this->refresh = (gcnew System::Windows::Forms::Button());
               this->body = (gcnew System::Windows::Forms::TableLayoutPanel());
               this->sidebar = (gcnew System::Windows::Forms::FlowLayoutPanel());
               this->categoryTitle = (gcnew System::Windows::Forms::Label());
               this->allButton = (gcnew System::Windows::Forms::Button());
               this->leafyButton = (gcnew System::Windows::Forms::Button());
               this->rootButton = (gcnew System::Windows::Forms::Button());
               this->fruitButton = (gcnew System::Windows::Forms::Button());
               this->beansButton = (gcnew System::Windows::Forms::Button());
               this->otherButton = (gcnew System::Windows::Forms::Button());
               this->content = (gcnew System::Windows::Forms::Panel());
               this->products = (gcnew System::Windows::Forms::Panel());
               this->empty = (gcnew System::Windows::Forms::Label());
               this->status = (gcnew System::Windows::Forms::Label());
               this->profileMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
               this->viewProfileItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->changeNameItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->changePasswordItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->searchTimer = (gcnew System::Windows::Forms::Timer(this->components));
               this->layout->SuspendLayout();
               this->header->SuspendLayout();
               this->heading->SuspendLayout();
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
               this->toolbar->SuspendLayout();
               this->body->SuspendLayout();
               this->sidebar->SuspendLayout();
               this->content->SuspendLayout();
               this->products->SuspendLayout();
               this->profileMenu->SuspendLayout();
               this->SuspendLayout();
               // 
               // layout
               // 
               this->layout->ColumnCount = 1;
               this->layout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
               this->layout->Controls->Add(this->header, 0, 0);
               this->layout->Controls->Add(this->toolbar, 0, 1);
               this->layout->Controls->Add(this->body, 0, 2);
               this->layout->Dock = System::Windows::Forms::DockStyle::Fill;
               this->layout->Location = System::Drawing::Point(0, 0);
               this->layout->Margin = System::Windows::Forms::Padding(0);
               this->layout->Name = L"layout";
               this->layout->RowCount = 3;
               this->layout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 135)));
               this->layout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 90)));
               this->layout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
               this->layout->Size = System::Drawing::Size(1868, 1055);
               this->layout->TabIndex = 0;
               // 
               // header
               // 
               this->header->BackColor = System::Drawing::Color::White;
               this->header->ColumnCount = 3;
               this->header->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 262)));
               this->header->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
               this->header->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 262)));
               this->header->Controls->Add(this->heading, 1, 0);
               this->header->Controls->Add(this->profile, 2, 0);
               this->header->Controls->Add(this->button1, 0, 0);
               this->header->Dock = System::Windows::Forms::DockStyle::Fill;
               this->header->Location = System::Drawing::Point(0, 0);
               this->header->Margin = System::Windows::Forms::Padding(0);
               this->header->Name = L"header";
               this->header->Padding = System::Windows::Forms::Padding(25, 15, 25, 15);
               this->header->RowCount = 1;
               this->header->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
               this->header->Size = System::Drawing::Size(1868, 135);
               this->header->TabIndex = 0;
               // 
               // heading
               // 
               this->heading->Controls->Add(this->pictureBox1);
               this->heading->Controls->Add(this->tagline);
               this->heading->Controls->Add(this->marketTitle);
               this->heading->Dock = System::Windows::Forms::DockStyle::Fill;
               this->heading->Location = System::Drawing::Point(291, 19);
               this->heading->Margin = System::Windows::Forms::Padding(4);
               this->heading->Name = L"heading";
               this->heading->Size = System::Drawing::Size(1286, 97);
               this->heading->TabIndex = 1;
               // 
               // pictureBox1
               // 
               this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
               this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
               this->pictureBox1->Location = System::Drawing::Point(329, 4);
               this->pictureBox1->Name = L"pictureBox1";
               this->pictureBox1->Size = System::Drawing::Size(108, 56);
               this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
               this->pictureBox1->TabIndex = 2;
               this->pictureBox1->TabStop = false;
               // 
               // tagline
               // 
               this->tagline->AutoEllipsis = true;
               this->tagline->Dock = System::Windows::Forms::DockStyle::Bottom;
               this->tagline->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
               this->tagline->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(28)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
                   static_cast<System::Int32>(static_cast<System::Byte>(42)));
               this->tagline->Location = System::Drawing::Point(0, 63);
               this->tagline->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
               this->tagline->Name = L"tagline";
               this->tagline->Size = System::Drawing::Size(1286, 34);
               this->tagline->TabIndex = 1;
               this->tagline->Text = L"Buy fresh Veg now!";
               this->tagline->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
               // 
               // marketTitle
               // 
               this->marketTitle->AutoEllipsis = true;
               this->marketTitle->BackColor = System::Drawing::Color::Transparent;
               this->marketTitle->Dock = System::Windows::Forms::DockStyle::Top;
               this->marketTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26, System::Drawing::FontStyle::Bold));
               this->marketTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(28)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
                   static_cast<System::Int32>(static_cast<System::Byte>(42)));
               this->marketTitle->Location = System::Drawing::Point(0, 0);
               this->marketTitle->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
               this->marketTitle->Name = L"marketTitle";
               this->marketTitle->Size = System::Drawing::Size(1286, 60);
               this->marketTitle->TabIndex = 0;
               this->marketTitle->Text = L"VegWay Market";
               this->marketTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
               // 
               // profile
               // 
               this->profile->AccessibleName = L"Open profile menu";
               this->profile->Anchor = System::Windows::Forms::AnchorStyles::Right;
               this->profile->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
                   static_cast<System::Int32>(static_cast<System::Byte>(66)));
               this->profile->Cursor = System::Windows::Forms::Cursors::Hand;
               this->profile->FlatAppearance->BorderSize = 0;
               this->profile->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->profile->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->profile->ForeColor = System::Drawing::Color::White;
               this->profile->Location = System::Drawing::Point(1601, 38);
               this->profile->Margin = System::Windows::Forms::Padding(4);
               this->profile->Name = L"profile";
               this->profile->Size = System::Drawing::Size(238, 58);
               this->profile->TabIndex = 2;
               this->profile->Text = L"- My profile -";
               this->profile->UseVisualStyleBackColor = false;
               this->profile->Click += gcnew System::EventHandler(this, &VegWayMarket::ProfileClick);
               // 
               // button1
               // 
               this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
                   static_cast<System::Int32>(static_cast<System::Byte>(66)));
               this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->button1->ForeColor = System::Drawing::Color::White;
               this->button1->Location = System::Drawing::Point(28, 18);
               this->button1->Name = L"button1";
               this->button1->Size = System::Drawing::Size(238, 98);
               this->button1->TabIndex = 1;
               this->button1->Text = L"Sell Your Veg Now";
               this->button1->UseVisualStyleBackColor = false;
               this->button1->Click += gcnew System::EventHandler(this, &VegWayMarket::button1_Click);
               // 
               // toolbar
               // 
               this->toolbar->ColumnCount = 3;
               this->toolbar->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 225)));
               this->toolbar->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
               this->toolbar->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 156)));
               this->toolbar->Controls->Add(this->searchLabel, 0, 0);
               this->toolbar->Controls->Add(this->search, 1, 0);
               this->toolbar->Controls->Add(this->refresh, 2, 0);
               this->toolbar->Dock = System::Windows::Forms::DockStyle::Fill;
               this->toolbar->Location = System::Drawing::Point(0, 135);
               this->toolbar->Margin = System::Windows::Forms::Padding(0);
               this->toolbar->Name = L"toolbar";
               this->toolbar->Padding = System::Windows::Forms::Padding(25, 20, 25, 15);
               this->toolbar->RowCount = 1;
               this->toolbar->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
               this->toolbar->Size = System::Drawing::Size(1868, 90);
               this->toolbar->TabIndex = 1;
               // 
               // searchLabel
               // 
               this->searchLabel->AutoEllipsis = true;
               this->searchLabel->Dock = System::Windows::Forms::DockStyle::Fill;
               this->searchLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
               this->searchLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(28)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
                   static_cast<System::Int32>(static_cast<System::Byte>(42)));
               this->searchLabel->Location = System::Drawing::Point(29, 20);
               this->searchLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
               this->searchLabel->Name = L"searchLabel";
               this->searchLabel->Size = System::Drawing::Size(217, 55);
               this->searchLabel->TabIndex = 0;
               this->searchLabel->Text = L"Search vegetables";
               this->searchLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
               // 
               // search
               // 
               this->search->AccessibleName = L"Search vegetables by name";
               this->search->Dock = System::Windows::Forms::DockStyle::Fill;
               this->search->Font = (gcnew System::Drawing::Font(L"Segoe UI Light", 10.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->search->Location = System::Drawing::Point(254, 24);
               this->search->Margin = System::Windows::Forms::Padding(4);
               this->search->MaxLength = 100;
               this->search->Name = L"search";
               this->search->Size = System::Drawing::Size(1429, 30);
               this->search->TabIndex = 1;
               this->search->Text = L"search to find what you need easily!";
               this->search->TextChanged += gcnew System::EventHandler(this, &VegWayMarket::SearchChanged);
               // 
               // refresh
               // 
               this->refresh->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
                   static_cast<System::Int32>(static_cast<System::Byte>(66)));
               this->refresh->Cursor = System::Windows::Forms::Cursors::Hand;
               this->refresh->Dock = System::Windows::Forms::DockStyle::Fill;
               this->refresh->FlatAppearance->BorderSize = 0;
               this->refresh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->refresh->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->refresh->ForeColor = System::Drawing::Color::White;
               this->refresh->Location = System::Drawing::Point(1691, 24);
               this->refresh->Margin = System::Windows::Forms::Padding(4);
               this->refresh->Name = L"refresh";
               this->refresh->Size = System::Drawing::Size(148, 47);
               this->refresh->TabIndex = 2;
               this->refresh->Text = L"Refresh";
               this->refresh->UseVisualStyleBackColor = false;
               this->refresh->Click += gcnew System::EventHandler(this, &VegWayMarket::RefreshClick);
               // 
               // body
               // 
               this->body->ColumnCount = 2;
               this->body->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 256)));
               this->body->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
               this->body->Controls->Add(this->sidebar, 0, 0);
               this->body->Controls->Add(this->content, 1, 0);
               this->body->Dock = System::Windows::Forms::DockStyle::Fill;
               this->body->Location = System::Drawing::Point(4, 229);
               this->body->Margin = System::Windows::Forms::Padding(4);
               this->body->Name = L"body";
               this->body->RowCount = 1;
               this->body->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
               this->body->Size = System::Drawing::Size(1860, 822);
               this->body->TabIndex = 2;
               // 
               // sidebar
               // 
               this->sidebar->AutoScroll = true;
               this->sidebar->BackColor = System::Drawing::Color::White;
               this->sidebar->Controls->Add(this->categoryTitle);
               this->sidebar->Controls->Add(this->allButton);
               this->sidebar->Controls->Add(this->leafyButton);
               this->sidebar->Controls->Add(this->rootButton);
               this->sidebar->Controls->Add(this->fruitButton);
               this->sidebar->Controls->Add(this->beansButton);
               this->sidebar->Controls->Add(this->otherButton);
               this->sidebar->Dock = System::Windows::Forms::DockStyle::Fill;
               this->sidebar->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
               this->sidebar->Location = System::Drawing::Point(4, 4);
               this->sidebar->Margin = System::Windows::Forms::Padding(4);
               this->sidebar->Name = L"sidebar";
               this->sidebar->Padding = System::Windows::Forms::Padding(12);
               this->sidebar->Size = System::Drawing::Size(248, 814);
               this->sidebar->TabIndex = 0;
               this->sidebar->WrapContents = false;
               // 
               // categoryTitle
               // 
               this->categoryTitle->AutoEllipsis = true;
               this->categoryTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->categoryTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(28)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
                   static_cast<System::Int32>(static_cast<System::Byte>(42)));
               this->categoryTitle->Location = System::Drawing::Point(16, 12);
               this->categoryTitle->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
               this->categoryTitle->Name = L"categoryTitle";
               this->categoryTitle->Size = System::Drawing::Size(212, 52);
               this->categoryTitle->TabIndex = 0;
               this->categoryTitle->Text = L"VEGETABLE TYPES";
               // 
               // allButton
               // 
               this->allButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
                   static_cast<System::Int32>(static_cast<System::Byte>(66)));
               this->allButton->Cursor = System::Windows::Forms::Cursors::Hand;
               this->allButton->FlatAppearance->BorderSize = 0;
               this->allButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->allButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->allButton->ForeColor = System::Drawing::Color::White;
               this->allButton->Location = System::Drawing::Point(12, 64);
               this->allButton->Margin = System::Windows::Forms::Padding(0, 0, 0, 11);
               this->allButton->Name = L"allButton";
               this->allButton->Size = System::Drawing::Size(212, 56);
               this->allButton->TabIndex = 1;
               this->allButton->Tag = L"All vegetables";
               this->allButton->Text = L"All vegetables";
               this->allButton->UseVisualStyleBackColor = false;
               this->allButton->Click += gcnew System::EventHandler(this, &VegWayMarket::CategoryClick);
               // 
               // leafyButton
               // 
               this->leafyButton->BackColor = System::Drawing::Color::Honeydew;
               this->leafyButton->Cursor = System::Windows::Forms::Cursors::Hand;
               this->leafyButton->FlatAppearance->BorderSize = 0;
               this->leafyButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->leafyButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->leafyButton->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
                   static_cast<System::Int32>(static_cast<System::Byte>(66)));
               this->leafyButton->Location = System::Drawing::Point(12, 131);
               this->leafyButton->Margin = System::Windows::Forms::Padding(0, 0, 0, 11);
               this->leafyButton->Name = L"leafyButton";
               this->leafyButton->Size = System::Drawing::Size(212, 56);
               this->leafyButton->TabIndex = 2;
               this->leafyButton->Tag = L"Leafy vegetables";
               this->leafyButton->Text = L"Leafy vegetables";
               this->leafyButton->UseVisualStyleBackColor = false;
               this->leafyButton->Click += gcnew System::EventHandler(this, &VegWayMarket::CategoryClick);
               // 
               // rootButton
               // 
               this->rootButton->BackColor = System::Drawing::Color::Honeydew;
               this->rootButton->Cursor = System::Windows::Forms::Cursors::Hand;
               this->rootButton->FlatAppearance->BorderSize = 0;
               this->rootButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->rootButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->rootButton->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
                   static_cast<System::Int32>(static_cast<System::Byte>(66)));
               this->rootButton->Location = System::Drawing::Point(12, 198);
               this->rootButton->Margin = System::Windows::Forms::Padding(0, 0, 0, 11);
               this->rootButton->Name = L"rootButton";
               this->rootButton->Size = System::Drawing::Size(212, 56);
               this->rootButton->TabIndex = 3;
               this->rootButton->Tag = L"Root vegetables";
               this->rootButton->Text = L"Root vegetables";
               this->rootButton->UseVisualStyleBackColor = false;
               this->rootButton->Click += gcnew System::EventHandler(this, &VegWayMarket::CategoryClick);
               // 
               // fruitButton
               // 
               this->fruitButton->BackColor = System::Drawing::Color::Honeydew;
               this->fruitButton->Cursor = System::Windows::Forms::Cursors::Hand;
               this->fruitButton->FlatAppearance->BorderSize = 0;
               this->fruitButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->fruitButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->fruitButton->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
                   static_cast<System::Int32>(static_cast<System::Byte>(66)));
               this->fruitButton->Location = System::Drawing::Point(12, 265);
               this->fruitButton->Margin = System::Windows::Forms::Padding(0, 0, 0, 11);
               this->fruitButton->Name = L"fruitButton";
               this->fruitButton->Size = System::Drawing::Size(212, 56);
               this->fruitButton->TabIndex = 4;
               this->fruitButton->Tag = L"Fruit vegetables";
               this->fruitButton->Text = L"Fruit vegetables";
               this->fruitButton->UseVisualStyleBackColor = false;
               this->fruitButton->Click += gcnew System::EventHandler(this, &VegWayMarket::CategoryClick);
               // 
               // beansButton
               // 
               this->beansButton->BackColor = System::Drawing::Color::Honeydew;
               this->beansButton->Cursor = System::Windows::Forms::Cursors::Hand;
               this->beansButton->FlatAppearance->BorderSize = 0;
               this->beansButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->beansButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->beansButton->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
                   static_cast<System::Int32>(static_cast<System::Byte>(66)));
               this->beansButton->Location = System::Drawing::Point(12, 332);
               this->beansButton->Margin = System::Windows::Forms::Padding(0, 0, 0, 11);
               this->beansButton->Name = L"beansButton";
               this->beansButton->Size = System::Drawing::Size(212, 56);
               this->beansButton->TabIndex = 5;
               this->beansButton->Tag = L"Beans & peas";
               this->beansButton->Text = L"Beans & peas";
               this->beansButton->UseVisualStyleBackColor = false;
               this->beansButton->Click += gcnew System::EventHandler(this, &VegWayMarket::CategoryClick);
               // 
               // otherButton
               // 
               this->otherButton->BackColor = System::Drawing::Color::Honeydew;
               this->otherButton->Cursor = System::Windows::Forms::Cursors::Hand;
               this->otherButton->FlatAppearance->BorderSize = 0;
               this->otherButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->otherButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->otherButton->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
                   static_cast<System::Int32>(static_cast<System::Byte>(66)));
               this->otherButton->Location = System::Drawing::Point(12, 399);
               this->otherButton->Margin = System::Windows::Forms::Padding(0, 0, 0, 11);
               this->otherButton->Name = L"otherButton";
               this->otherButton->Size = System::Drawing::Size(212, 56);
               this->otherButton->TabIndex = 6;
               this->otherButton->Tag = L"Other";
               this->otherButton->Text = L"Other";
               this->otherButton->UseVisualStyleBackColor = false;
               this->otherButton->Click += gcnew System::EventHandler(this, &VegWayMarket::CategoryClick);
               // 
               // content
               // 
               this->content->Controls->Add(this->products);
               this->content->Controls->Add(this->status);
               this->content->Dock = System::Windows::Forms::DockStyle::Fill;
               this->content->Location = System::Drawing::Point(260, 4);
               this->content->Margin = System::Windows::Forms::Padding(4);
               this->content->Name = L"content";
               this->content->Size = System::Drawing::Size(1596, 814);
               this->content->TabIndex = 1;
               // 
               // products
               // 
               this->products->AutoScroll = true;
               this->products->Controls->Add(this->empty);
               this->products->Dock = System::Windows::Forms::DockStyle::Fill;
               this->products->Location = System::Drawing::Point(0, 44);
               this->products->Margin = System::Windows::Forms::Padding(4);
               this->products->Name = L"products";
               this->products->Size = System::Drawing::Size(1596, 770);
               this->products->TabIndex = 0;
               this->products->Resize += gcnew System::EventHandler(this, &VegWayMarket::ProductsResize);
               // 
               // empty
               // 
               this->empty->AutoEllipsis = true;
               this->empty->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold));
               this->empty->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(28)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
                   static_cast<System::Int32>(static_cast<System::Byte>(42)));
               this->empty->Location = System::Drawing::Point(31, 44);
               this->empty->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
               this->empty->Name = L"empty";
               this->empty->Size = System::Drawing::Size(875, 125);
               this->empty->TabIndex = 0;
               this->empty->Text = L"No items added yet.";
               // 
               // status
               // 
               this->status->AutoEllipsis = true;
               this->status->Dock = System::Windows::Forms::DockStyle::Top;
               this->status->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
               this->status->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(28)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
                   static_cast<System::Int32>(static_cast<System::Byte>(42)));
               this->status->Location = System::Drawing::Point(0, 0);
               this->status->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
               this->status->Name = L"status";
               this->status->Size = System::Drawing::Size(1596, 44);
               this->status->TabIndex = 1;
               this->status->Text = L"Available vegetables";
               // 
               // profileMenu
               // 
               this->profileMenu->ImageScalingSize = System::Drawing::Size(20, 20);
               this->profileMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
                   this->viewProfileItem,
                       this->changeNameItem, this->changePasswordItem, this->toolStripMenuItem1
               });
               this->profileMenu->Name = L"profileMenu";
               this->profileMenu->Size = System::Drawing::Size(207, 100);
               this->profileMenu->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &VegWayMarket::profileMenu_Opening);
               // 
               // viewProfileItem
               // 
               this->viewProfileItem->Name = L"viewProfileItem";
               this->viewProfileItem->Size = System::Drawing::Size(206, 24);
               this->viewProfileItem->Text = L"View profile details";
               this->viewProfileItem->Click += gcnew System::EventHandler(this, &VegWayMarket::ProfileAction);
               // 
               // changeNameItem
               // 
               this->changeNameItem->Name = L"changeNameItem";
               this->changeNameItem->Size = System::Drawing::Size(206, 24);
               this->changeNameItem->Text = L"Change name";
               this->changeNameItem->Click += gcnew System::EventHandler(this, &VegWayMarket::ProfileAction);
               // 
               // changePasswordItem
               // 
               this->changePasswordItem->Name = L"changePasswordItem";
               this->changePasswordItem->Size = System::Drawing::Size(206, 24);
               this->changePasswordItem->Text = L"Change password";
               this->changePasswordItem->Click += gcnew System::EventHandler(this, &VegWayMarket::ProfileAction);
               // 
               // toolStripMenuItem1
               // 
               this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
               this->toolStripMenuItem1->Size = System::Drawing::Size(206, 24);
               this->toolStripMenuItem1->Text = L"View Your Sells!";
               this->toolStripMenuItem1->Click += gcnew System::EventHandler(this, &VegWayMarket::ProfileAction);
               // 
               // searchTimer
               // 
               this->searchTimer->Interval = 350;
               this->searchTimer->Tick += gcnew System::EventHandler(this, &VegWayMarket::SearchTick);
               // 
               // VegWayMarket
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(120, 120);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
               this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(244)), static_cast<System::Int32>(static_cast<System::Byte>(249)),
                   static_cast<System::Int32>(static_cast<System::Byte>(245)));
               this->ClientSize = System::Drawing::Size(1868, 1055);
               this->Controls->Add(this->layout);
               this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
               this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
               this->Margin = System::Windows::Forms::Padding(4);
               this->MinimumSize = System::Drawing::Size(1370, 838);
               this->Name = L"VegWayMarket";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"VegWay Market";
               this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
               this->Load += gcnew System::EventHandler(this, &VegWayMarket::VegWayMarket_Load);
               this->Shown += gcnew System::EventHandler(this, &VegWayMarket::FirstShown);
               this->layout->ResumeLayout(false);
               this->header->ResumeLayout(false);
               this->heading->ResumeLayout(false);
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
               this->toolbar->ResumeLayout(false);
               this->toolbar->PerformLayout();
               this->body->ResumeLayout(false);
               this->sidebar->ResumeLayout(false);
               this->content->ResumeLayout(false);
               this->products->ResumeLayout(false);
               this->profileMenu->ResumeLayout(false);
               this->ResumeLayout(false);

           }
#pragma endregion
    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        if (System::String::IsNullOrWhiteSpace(userId))
        {
            System::Windows::Forms::MessageBox::Show(
                this, "Please log in before selling.");
            return;
        }

        VegWay::ItemAddForm^ itemForm =
            gcnew VegWay::ItemAddForm(userId);

        bool saved = false;

        try
        {
            saved = itemForm->ShowDialog(this) ==
                System::Windows::Forms::DialogResult::OK;
        }
        finally
        {
            delete itemForm;
        }

        if (saved)
        {
            category = "All vegetables";
            search->Clear();
            searchTimer->Stop();

            UpdateCategoryButtons();
            LoadProducts();
        }
    }
    private: System::Void VegWayMarket_Load(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void profileMenu_Opening(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
    }
};
}

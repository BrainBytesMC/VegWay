// Include pch.h first if required, or disable PCH for this .cpp.
#include "ProfileSettings.h"
#include "VegWayStore.h"
using namespace System;
using namespace System::Data;
using namespace System::Globalization;
using namespace System::Windows::Forms;
using namespace System::Windows::Forms::DataVisualization::Charting;
namespace VegWay {
void ProfileSettings::FirstShown(Object^,EventArgs^) {
    if(DesignMode||ComponentModel::LicenseManager::UsageMode==ComponentModel::LicenseUsageMode::Designtime)return;
    Reload();
    if(initialPage>=0&&initialPage<4&&pages->TabPages[initialPage]->Enabled)pages->SelectedIndex=initialPage;
}
void ProfileSettings::ViewClick(Object^,EventArgs^){pages->SelectedIndex=0;}
void ProfileSettings::NameClick(Object^,EventArgs^){pages->SelectedIndex=1;}
void ProfileSettings::PasswordClick(Object^,EventArgs^){pages->SelectedIndex=2;}
void ProfileSettings::SalesClick(Object^,EventArgs^){if(btnSales->Enabled)pages->SelectedIndex=3;}
void ProfileSettings::RefreshClick(Object^,EventArgs^){Reload();}
void ProfileSettings::Reload() {
    if(busy)return;busy=true;UseWaitCursor=true;
    try {
        DataTable^ p=VegWayStore::Profile(userId);
        if(!p->Rows->Count)throw gcnew InvalidOperationException("Account no longer exists. Please log in again.");
        currentName=Convert::ToString(p->Rows[0]["CustomerName"]);
        lblName->Text="Name: "+currentName;
        lblEmail->Text="Email: "+Convert::ToString(p->Rows[0]["Email"]);
        lblPhone->Text="Phone: "+Convert::ToString(p->Rows[0]["Phonenumber"]);
        DataTable^ history=VegWayStore::BuyerOrders(userId);ordersGrid->DataSource=history;
        lblOrders->Text=history->Rows->Count?"Your order history":"Your order history - no orders yet";
        DataTable^ listings=VegWayStore::Listings(userId);listingGrid->DataSource=listings;
        bool seller=listings->Rows->Count>0;btnSales->Enabled=seller;salesPage->Enabled=seller;
        if(!seller&&pages->SelectedIndex==3)pages->SelectedIndex=0;
        note->Text=seller?"Recorded earnings only.\r\nNo money is transferred.":"Add a market listing to unlock Your sells.";
        DataTable^ totals=VegWayStore::Totals(userId);
        Decimal earned=Decimal::Parse(Convert::ToString(totals->Rows[0]["Earnings"]),CultureInfo::InvariantCulture);
        salesSummary->Text="Orders: "+Convert::ToString(totals->Rows[0]["Orders"])+
            "    Sold: "+Convert::ToString(totals->Rows[0]["Kg"])+" kg    Total earnings: Rs. "+earned.ToString("N2");
        if(seller)DrawSales(VegWayStore::DailySales(userId),VegWayStore::SalesStart(userId));
        if(initialPage==3&&!seller)note->Text="Your sells unlocks after you add your first listing.";
    }
    catch(Exception^ ex){MessageBox::Show(this,ex->Message,"Could not load account",MessageBoxButtons::OK,MessageBoxIcon::Error);}
    finally {busy=false;UseWaitCursor=false;}
}
void ProfileSettings::SaveNameClick(Object^,EventArgs^) {
    if(busy)return;
    String^ proposed=newName->Text->Trim();
    if(proposed!=confirmName->Text->Trim()){MessageBox::Show(this,"The two names do not match.","Check name");return;}
    busy=true;saveName->Enabled=false;UseWaitCursor=true;
    bool saved=false;
    try {VegWayStore::ChangeName(userId,proposed);currentName=proposed;newName->Clear();confirmName->Clear();saved=true;}
    catch(Exception^ ex){MessageBox::Show(this,ex->Message,"Could not change name");}
    finally {busy=false;saveName->Enabled=true;UseWaitCursor=false;}
    if(saved){Reload();MessageBox::Show(this,"Your name has been updated.","Name saved");}
}
void ProfileSettings::SavePasswordClick(Object^,EventArgs^) {
    if(busy)return;
    if(newPassword->Text!=confirmPassword->Text){MessageBox::Show(this,"New passwords do not match.","Check password");return;}
    busy=true;savePassword->Enabled=false;UseWaitCursor=true;
    try {
        VegWayStore::ChangePassword(userId,currentPassword->Text,newPassword->Text);
        currentPassword->Clear();newPassword->Clear();confirmPassword->Clear();
        MessageBox::Show(this,"Password updated. Use the new password the next time you log in.","Password saved");
    }
    catch(Exception^ ex){MessageBox::Show(this,ex->Message,"Could not change password");}
    finally{busy=false;savePassword->Enabled=true;UseWaitCursor=false;}
}
void ProfileSettings::DrawSales(DataTable^ table,DateTime start) {
    Series^ orders=salesChart->Series["Orders"];Series^ earnings=salesChart->Series["Earnings"];
    orders->Points->Clear();earnings->Points->Clear();
    Decimal total=0;int count=0,index=0;
    DateTime today=DateTime::UtcNow.AddMinutes(330).Date;
    DateTime last=today;
    if(table->Rows->Count) {
        DateTime first=DateTime::ParseExact(Convert::ToString(table->Rows[0]["Day"]),"yyyy-MM-dd",CultureInfo::InvariantCulture);
        if(first<start)start=first;
        DateTime finalDay=DateTime::ParseExact(Convert::ToString(table->Rows[table->Rows->Count-1]["Day"]),"yyyy-MM-dd",CultureInfo::InvariantCulture);
        if(finalDay>last)last=finalDay;
    }
    for(DateTime day=start.Date;day<=last;day=day.AddDays(1)) {
        String^ key=day.ToString("yyyy-MM-dd",CultureInfo::InvariantCulture);
        if(index<table->Rows->Count&&Convert::ToString(table->Rows[index]["Day"])==key) {
            count+=Int32::Parse(Convert::ToString(table->Rows[index]["Orders"]),CultureInfo::InvariantCulture);
            total+=Decimal::Parse(Convert::ToString(table->Rows[index]["Earnings"]),CultureInfo::InvariantCulture);index++;
        }
        orders->Points->AddXY(day.ToOADate(),gcnew array<double>{static_cast<double>(count)});
        earnings->Points->AddXY(day.ToOADate(),gcnew array<double>{Decimal::ToDouble(total)});
    }
    salesNote->Text="Cumulative orders and earnings since "+start.ToString("dd MMM yyyy")+". Dates: Sri Lanka time.";
    salesChart->ChartAreas["Sales"]->RecalculateAxesScale();
}
}

// Include pch.h first if required, or disable PCH for this .cpp.
#include "PayNow.h"
#include "VegWayStore.h"
using namespace System;
using namespace System::Windows::Forms;
namespace vegway {
    void PayNow::PayNow_Load(Object^, EventArgs^) {
        if (DesignMode || System::ComponentModel::LicenseManager::UsageMode == System::ComponentModel::LicenseUsageMode::Designtime)return;
        ReloadItem();
    }
    void PayNow::ReloadItem() {
        ready = false;btnpay->Enabled = false;numquntity->Enabled = false;
        try {
            if (String::IsNullOrWhiteSpace(buyerId))throw gcnew InvalidOperationException("Open this form from Buy now after logging in.");
            VegWay::MarketProduct^ p = VegWay::VegWayStore::Product(itemId);
            label1->Text = p->Name;
            quotedPrice = p->Price;
            txtstock->Text = p->Stock.ToString("0.###") + " kg";
            txtpricekg->Text = "Rs. " + p->Price.ToString("0.00");
            numquntity->Maximum = p->Stock;
            if (numquntity->Value <= Decimal::Zero || numquntity->Value > p->Stock)
                numquntity->Value = (p->Stock < System::Decimal(1))
                ? p->Stock : System::Decimal(1);
            ready = p->Active && p->Stock > Decimal::Zero && p->SellerId != buyerId;
            btnpay->Enabled = ready;numquntity->Enabled = ready;
            lblNotice->Text = p->SellerId == buyerId ? "This is your own listing." :
                (ready ? "Records an order and reduces stock. No money is transferred." : "This listing is unavailable or out of stock.");
            UpdateTotal(nullptr, nullptr);
        }
        catch (Exception^ ex) { txttotal->Text = "";lblNotice->Text = "Could not load this item. Click Reload to try again.";MessageBox::Show(this, ex->Message, "Order error"); }
    }
    void PayNow::UpdateTotal(Object^, EventArgs^) {
        Decimal total = Decimal::Round(quotedPrice * numquntity->Value, 2, MidpointRounding::AwayFromZero);
        txttotal->Text = "Rs. " + total.ToString("0.00");
    }
    void PayNow::ReloadClick(Object^, EventArgs^) { if (!saving)ReloadItem(); }
    void PayNow::btnpay_Click(Object^, EventArgs^) {
        if (!ready || saving)return;
        // Force pending typed quantity to commit before reading Value.
        this->Validate();
        Decimal quantity = numquntity->Value;
        if (quantity <= Decimal::Zero) { MessageBox::Show(this, "Enter a positive order quantity.");return; }
        Decimal total = Decimal::Round(quotedPrice * quantity, 2, MidpointRounding::AwayFromZero);
        if (MessageBox::Show(this, "Confirm " + quantity.ToString("0.###") + " kg for Rs. " + total.ToString("0.00") +
            "?\r\nThis records an order; no money is transferred.", "Confirm order", MessageBoxButtons::YesNo, MessageBoxIcon::Question) != System::Windows::Forms::DialogResult::Yes)return;
        saving = true;btnpay->Enabled = false;numquntity->Enabled = false;btnReload->Enabled = false;UseWaitCursor = true;
        bool saved = false;
        try { orderId = VegWay::VegWayStore::Checkout(buyerId, itemId, quantity, quotedPrice, checkoutToken);saved = true; }
        catch (Exception^ ex) { MessageBox::Show(this, ex->Message + "\r\nIf the connection failed during confirmation, retry in this same window to avoid recording twice.", "Order not confirmed"); }
        finally { saving = false;UseWaitCursor = false;btnpay->Enabled = ready;numquntity->Enabled = ready;btnReload->Enabled = true; }
        if (saved) { MessageBox::Show(this, "Order " + orderId + " recorded. No money was transferred.", "Order recorded");this->DialogResult = System::Windows::Forms::DialogResult::OK;Close(); }
    }
}

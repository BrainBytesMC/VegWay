#include "MainForm.h"
#include "VegWayMarket.h"

using namespace System;
using namespace System::Windows::Forms;
bool SetupDatabase();

[STAThreadAttribute]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    if (!SetupDatabase()) return 1;

    String^ id = nullptr;
    String^ name = nullptr;
    String^ email = nullptr;
    VegWay::MainForm^ mainWindow = gcnew VegWay::MainForm();
    try {
        if (mainWindow->ShowDialog() == DialogResult::OK) {
            id = mainWindow->LoggedInUserId;
            name = mainWindow->LoggedInName;
            email = mainWindow->LoggedInEmail;
        }
    }
    finally { delete mainWindow; }

    // Closing/cancelling MainForm before successful login exits normally.
    if (String::IsNullOrWhiteSpace(id)) return 0;
    VegWay::VegWayMarket^ market = gcnew VegWay::VegWayMarket(id, name, email);
    try { Application::Run(market); }
    finally { delete market; }
    return 0;
}

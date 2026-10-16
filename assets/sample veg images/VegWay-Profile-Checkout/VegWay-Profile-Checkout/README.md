# VegWay profile settings and local checkout

This package extends the two files you attached: your customized `VegWayMarket` in namespace `VegWay`, and your PayNow form in lowercase namespace `vegway`. It preserves your market layout and PayNow resource references. It adds an editable ProfileSettings form and records purchases in the existing database.

**Pay Now records a local order and reduces stock. It does not charge a card, move money or confirm an external payment.** Seller account earnings are the sum of recorded orders belonging to that seller, not a withdrawable bank/wallet balance. Both forms say this explicitly. The button text stays PAY NOW as requested.

## 1. Add the orders table in MySQL Workbench

Open your working MySQL connection and run `01-orders.sql` once. This creates only `vegway_orders` in `vegdb`; it does not change existing users or vegetable rows. No data is deleted.

The expected existing keys are:

- `users.userid`: INT UNSIGNED, primary key.
- `vegetables.vegetable_id`: BIGINT UNSIGNED, primary key.
- `vegetables.seller_userid`: INT UNSIGNED.
- Tables use InnoDB.
- Existing vegetable fields: vegetable_name, category, image_data, price_per_kg, quantity_kg, location, contact_phone, is_active, created_at.

If you get an incompatible foreign-key error, inspect `SHOW CREATE TABLE vegdb.users;` and `SHOW CREATE TABLE vegdb.vegetables;` and send the results. Do not delete or recreate existing tables. If vegway_orders already exists, IF NOT EXISTS does not upgrade its structure; inspect it before continuing.

Orders contain buyer/seller/item IDs, item-name snapshot, purchased kg, the price at checkout, rounded total, timestamp and a unique retry token. Changing a listing price later does not change historical orders. Old listings added before this feature do not have invented sales history; their earnings start at zero until orders are recorded.

## 2. Create the ProfileSettings form in Visual Studio

1. Stop debugging/running the application.
2. Right-click your existing C++/CLI .NET Framework PROJECT > Add > New Item > UI > Windows Form.
3. Name it **ProfileSettings.h**. This registers it as a form so View Designer is available.
4. Open its header in Code view and replace ALL its contents with the supplied **ProfileSettings.h**. Do not append a second class.
5. If Visual Studio created ProfileSettings.cpp with only a header include, replace its contents with the supplied **ProfileSettings.cpp**. Otherwise add that .cpp through Add > Existing Item.
6. Add **VegWayStore.h** and **VegWayStore.cpp** to the same project.
7. Add references to **System.Data** and **System.Windows.Forms.DataVisualization** (project References > Add Reference > Assemblies / Framework). System, System.Drawing and System.Windows.Forms should already be referenced.
8. Use **.NET Framework 4.7.2 or later**, matching the PBKDF2 password hashing in your working login.

The new profile form uses named control members and an explicit InitializeComponent, rather than a runtime layout builder. No database connection runs from the default constructor or InitializeComponent.

All four sections are TabPages, with green navigation buttons at the left. In Design view, click the page tabs to edit each page; Document Outline also lets you select nested controls. The chart is an actual WinForms Chart control, editable in the Designer. Do not rename fields unless their .cpp references are updated too.

## 3. Update PayNow

1. Back up PayNow.h outside the project.
2. Replace your existing **PayNow.h** with the supplied version.
3. Keep your original **PayNow.resx**, including its logo resource. The resource bytes were not attached here.
4. Replace the existing PayNow.cpp contents with the supplied **PayNow.cpp**, or add it if you do not yet have one.

This preserves your namespace `vegway`, spelling of controls such as `numquntity`, logo and basic design. It corrects the original swapped price/total textbox positions, widens numeric displays, enables up to three decimal places of kg, and adds Reload plus an explanation that no money is transferred.

Only order quantity is editable. Stock, price and total are read-only and load for the specific listing selected in the market. The price displayed as rupees is fetched again and checked when the order is confirmed. Zero-stock/inactive and own listings cannot be purchased. Quantities whose rounded total is less than Rs. 0.01 are rejected.

## 4. Connect the market

The supplied **VegWayMarket.h** is your current attached header with ONE menu wiring fix: `toolStripMenuItem1` (View Your Sells!) is now connected to ProfileAction. Your custom logo, layout, dimensions and existing Sell button handler remain intact. Keep **VegWayMarket.resx**.

Either replace your header with this supplied version, OR keep your header and add the single event line documented at the end of **02-market-handlers.txt**. Do not do both and register the event twice.

Now open your current **VegWayMarket.cpp**:

1. Add the two includes shown in **02-market-handlers.txt**.
2. Replace the existing **ProfileAction** function with that file's ProfileAction function.
3. Replace the existing **BuyClick** function with that file's BuyClick function.
4. Keep FirstShown, RefreshClick, LoadProducts, selling, image loading and other functions unchanged.

**Do not replace the whole VegWayMarket.cpp with the snippets file.** We have your current header but not your current working market .cpp. The patch targets the existing method declarations and product-card ID Tag behavior supplied earlier.

There must be exactly one definition of each market function. Your recent "already defined in ItemAddForm.obj" issue was duplicate compilation; do not copy market function implementations into ItemAddForm.cpp. Include .h files only. Never `#include "VegWayMarket.cpp"`, `#include "PayNow.cpp"`, etc.

Keep MainForm, LoginForm, ItemAddForm, source.cpp/SetupDatabase and your main() unchanged. They already pass the authenticated user ID into the market.

## 5. Build and open Design view

Compile each of these new .cpp files exactly once:

- ProfileSettings.cpp
- PayNow.cpp
- VegWayStore.cpp

Keep your existing VegWayMarket.cpp compiled once as well. Do not also compile backup copies.

The store uses the same native MySQL Connector/C++ classic JDBC API as your login/market. Preserve the working include/library paths, architecture and runtime DLL setup. The new store connection uses the same local host/user/password values from your supplied code. If those settings changed, update Connect() in VegWayStore.cpp.

Use `/clr` for the new files. If C1010 appears, put your project's actual pch.h/stdafx.h include FIRST in each new .cpp, or disable precompiled headers on those files through Properties > C/C++ > Precompiled Headers > Not Using Precompiled Headers. Don't replace source.cpp.

Build > Clean Solution > Rebuild Solution. Then right-click ProfileSettings.h > View Designer (Shift+F7). Runtime behavior requires running the application and logging in; Designer shows the layout without real user data.

## Profile behavior

| Left navigation | Contents |
| --- | --- |
| View profile | Generic profile icon, current name/email/phone, and buyer order history |
| Change name | New name, re-type confirmation, Save name |
| Change password | Current password, new password, re-type confirmation, Save password |
| View your sells! | Cumulative sales/earnings graph, total orders, kg sold, total rupees, listing stock and per-item sales |

Your sells is enabled after the account has at least one vegetable listing, even if it has not sold yet. A non-seller sees a prompt to add their first listing. Every account can view its buyer history.

The graph starts on the first listing date, includes zero-sale days, and ends today. Green is cumulative order count (left axis); gold is cumulative rupee earnings (right axis). An order counts as one sale regardless of kg. Transactions/dates use Sri Lanka time (+05:30). The listing table includes active and inactive listings, remaining stock, sold kg and earnings per listing.

Click Refresh account or reopen settings after purchases in another application instance. There is no live push connection between separate desktops. Names reload from the database; the market's cached userName is updated when settings closes. Passwords use the same `PBKDF2-SHA256$600000$...` format already verified by your attached LoginForm; no password is displayed in profile data.

The password change checks the current password, hashes the new one with a fresh salt, and refuses a conflicting concurrent change. Use the new password next time you log in. Changing name does not change email or user ID.

## Checkout behavior

1. Buy now passes the product-card listing ID and logged-in buyer ID to PayNow.
2. PayNow loads that listing and calculates quantity × price with decimal arithmetic.
3. Clicking Pay Now asks the buyer to confirm the displayed quantity and total.
4. The store begins an InnoDB transaction, locks that vegetable row, and checks the unique checkout token for a previous successful attempt.
5. It checks current stock, listing status, seller identity and the latest price. A changed price/insufficient stock is rejected; Reload lets the buyer review current values.
6. It conditionally decreases stock and inserts the order, then commits both changes together. Any failure before commit rolls back both.
7. Buyer order history and seller earnings both read the same order record. No separately maintained balance can drift out of sync.
8. The market reloads when PayNow closes. An item with zero stock disappears from the market, but remains in its seller's listings.

If the connection is lost during commit and the outcome is uncertain, retry in the SAME PayNow window. Its token stays unchanged, so an already-recorded order is returned without reducing stock again. A newly opened checkout window is a distinct order. Check order history before starting another checkout after an uncertain connection error.

This starter does not provide external payment collection, refunds/cancellation, delivery tracking, withdrawals or server-side account sessions. It retains your existing local desktop-to-MySQL architecture and logged-in user-ID flow. All buyers/sellers must connect to the same MySQL database for shared stock and orders; different PCs using localhost do not share data automatically.

## What was validated here

The two current attachments were read. Namespace/class/control names, market event declarations, SQL parameter bindings, order schema mappings, designer event handlers and default constructors were checked. Password format was compared with your attached login implementation. See TESTING.md for the acceptance checks to run on Windows, including stock contention and retries.

This environment has no Windows Visual Studio C++/CLI compiler, WinForms Designer or running MySQL server. The Windows build, UI rendering and live database transactions have **not** been executed here. If you hit a compiler error, send the first error with the filename/line rather than repeatedly removing functions.

References: MySQL locking reads https://dev.mysql.com/doc/refman/8.0/en/innodb-locking-reads.html ; WinForms secondary chart axis https://learn.microsoft.com/en-us/dotnet/api/system.windows.forms.datavisualization.charting.series.yaxistype?view=netframework-4.8.1 .

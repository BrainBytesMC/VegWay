// Add your project's pch.h first if required, or disable PCH for this file.
#include "VegWayStore.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <memory>
#include <exception>
#include <string>
#include <vcclr.h>
using namespace System;
using namespace System::Data;
using namespace System::Globalization;
using namespace System::Security::Cryptography;
namespace VegWay {
    namespace StoreInternal {
        static std::string Utf8(String^ s) {
            array<Byte>^ b = Text::Encoding::UTF8->GetBytes(s);
            if (!b->Length)return std::string();
            pin_ptr<Byte> p = &b[0]; return std::string(reinterpret_cast<char*>(p), b->Length);
        }
        static String^ Managed(const sql::SQLString& s) {
            std::string n = s.asStdString();array<Byte>^ b = gcnew array<Byte>(static_cast<int>(n.size()));
            for (int i = 0;i < b->Length;i++)b[i] = static_cast<Byte>(n[i]);return Text::Encoding::UTF8->GetString(b);
        }
        static Decimal Money(const sql::SQLString& s) { return Decimal::Parse(Managed(s), CultureInfo::InvariantCulture); }
        static std::string Number(Decimal n) { return Utf8(n.ToString(CultureInfo::InvariantCulture)); }
        static void UserId(String^ id) { UInt32 n; if (!UInt32::TryParse(id, n) || n == 0)throw gcnew ArgumentException("Please log in again."); }
        static sql::Connection* Connect() {
            sql::Connection* raw = sql::mysql::get_mysql_driver_instance()->connect("tcp://127.0.0.1:3306", "root", "rasu");
            std::unique_ptr<sql::Connection> c(raw);c->setSchema("vegdb");
            std::unique_ptr<sql::Statement> timezone(c->createStatement());timezone->execute("SET time_zone = '+05:30'");
            return c.release();
        }
        static DataTable^ Query(const char* text, String^ id) {
            UserId(id);std::unique_ptr<sql::Connection> c(Connect());
            std::unique_ptr<sql::PreparedStatement> s(c->prepareStatement(text));s->setString(1, Utf8(id));
            std::unique_ptr<sql::ResultSet> r(s->executeQuery());auto meta = r->getMetaData();
            DataTable^ t = gcnew DataTable();unsigned int count = meta->getColumnCount();
            for (unsigned int i = 1;i <= count;i++)t->Columns->Add(Managed(meta->getColumnLabel(i)));
            while (r->next()) {
                DataRow^ row = t->NewRow();for (unsigned int i = 1;i <= count;i++)
                    row[static_cast<int>(i - 1)] = r->isNull(i) ? String::Empty : Managed(r->getString(i));t->Rows->Add(row);
            }return t;
        }
        static bool Verify(String^ password, String^ stored) {
            if (String::IsNullOrEmpty(stored))return false;
            array<String^>^ p = stored->Split(gcnew array<Char>{'$'});
            if (p->Length != 4 || p[0] != "PBKDF2-SHA256" || p[1] != "600000")return false;
            array<Byte>^ salt;array<Byte>^ expected;
            try { salt = Convert::FromBase64String(p[2]);expected = Convert::FromBase64String(p[3]); }
            catch (FormatException^) { return false; }
            if (salt->Length != 16 || expected->Length != 32)return false;
            Rfc2898DeriveBytes^ k = gcnew Rfc2898DeriveBytes(password, salt, 600000, HashAlgorithmName::SHA256);
            array<Byte>^ actual;try { actual = k->GetBytes(32); }
            finally { delete k; }
            int diff = 0;for (int i = 0;i < 32;i++)diff |= actual[i] ^ expected[i];return diff == 0;
        }
        static String^ Hash(String^ password) {
            array<Byte>^ salt = gcnew array<Byte>(16);RandomNumberGenerator^ rng = RandomNumberGenerator::Create();
            try { rng->GetBytes(salt); }
            finally { delete rng; }
            Rfc2898DeriveBytes^ k = gcnew Rfc2898DeriveBytes(password, salt, 600000, HashAlgorithmName::SHA256);
            array<Byte>^ hash;try { hash = k->GetBytes(32); }
            finally { delete k; }
            return "PBKDF2-SHA256$600000$" + Convert::ToBase64String(salt) + "$" + Convert::ToBase64String(hash);
        }
    }
    // Convert native connector errors into managed exceptions for the forms.
#define STORE_ERROR catch(const sql::SQLException& e){throw gcnew InvalidOperationException(gcnew String(e.what()));} catch(const std::exception& e){throw gcnew InvalidOperationException(gcnew String(e.what()));}
    DataTable^ VegWayStore::Profile(String^ id) { try { return StoreInternal::Query("SELECT userid,CustomerName,Email,Phonenumber FROM users WHERE userid=?", id); }STORE_ERROR }
    DataTable^ VegWayStore::BuyerOrders(String^ id) {
        try {
            return StoreInternal::Query(
                "SELECT order_id AS Order_ID,item_name AS Item,quantity_kg AS Kg,price_per_kg AS Rs_per_kg,total_amount AS Total_Rs,created_at AS Ordered_at FROM vegway_orders WHERE buyer_userid=? ORDER BY created_at DESC,order_id DESC", id);
        }STORE_ERROR
    }
    DataTable^ VegWayStore::Listings(String^ id) {
        try {
            return StoreInternal::Query(
                "SELECT v.vegetable_id AS Item_ID,v.vegetable_name AS Item,v.category AS Category,v.price_per_kg AS Rs_per_kg,v.quantity_kg AS Stock_kg,v.is_active AS Active,v.created_at AS Listed_at,COALESCE(o.sold,0) AS Sold_kg,COALESCE(o.earned,0) AS Earnings_Rs "
                "FROM vegetables v LEFT JOIN (SELECT vegetable_id,SUM(quantity_kg) sold,SUM(total_amount) earned FROM vegway_orders GROUP BY vegetable_id) o ON o.vegetable_id=v.vegetable_id WHERE v.seller_userid=? ORDER BY v.created_at DESC", id);
        }STORE_ERROR
    }
    DataTable^ VegWayStore::DailySales(String^ id) {
        try {
            return StoreInternal::Query(
                "SELECT DATE_FORMAT(created_at,'%Y-%m-%d') AS Day,COUNT(*) AS Orders,SUM(total_amount) AS Earnings FROM vegway_orders WHERE seller_userid=? GROUP BY DATE(created_at),DATE_FORMAT(created_at,'%Y-%m-%d') ORDER BY Day", id);
        }STORE_ERROR
    }
    DataTable^ VegWayStore::Totals(String^ id) {
        try {
            return StoreInternal::Query(
                "SELECT COUNT(*) AS Orders,COALESCE(SUM(quantity_kg),0) AS Kg,COALESCE(SUM(total_amount),0) AS Earnings FROM vegway_orders WHERE seller_userid=?", id);
        }STORE_ERROR
    }
    DateTime VegWayStore::SalesStart(String^ id) {
        try {
            DataTable^ t = StoreInternal::Query("SELECT DATE_FORMAT(MIN(created_at),'%Y-%m-%d') AS Day FROM vegetables WHERE seller_userid=?", id);
            DataRow^ firstRow = t->Rows[0];
            String^ s = Convert::ToString(firstRow[0]);return s->Length ? DateTime::ParseExact(s, "yyyy-MM-dd", CultureInfo::InvariantCulture) : DateTime::UtcNow.AddMinutes(330).Date;
        }STORE_ERROR
    }
    void VegWayStore::ChangeName(String^ id, String^ name) {
        try {
            StoreInternal::UserId(id);name = name->Trim();if (name->Length < 1 || name->Length>100)throw gcnew ArgumentException("Name must contain 1 to 100 characters.");
            std::unique_ptr<sql::Connection> c(StoreInternal::Connect());
            std::unique_ptr<sql::PreparedStatement> s(c->prepareStatement("UPDATE users SET CustomerName=? WHERE userid=?"));
            s->setString(1, StoreInternal::Utf8(name));s->setString(2, StoreInternal::Utf8(id));
            if (s->executeUpdate() == 0) {
                std::unique_ptr<sql::PreparedStatement> check(c->prepareStatement("SELECT userid FROM users WHERE userid=?"));
                check->setString(1, StoreInternal::Utf8(id));std::unique_ptr<sql::ResultSet> exists(check->executeQuery());
                if (!exists->next())throw gcnew InvalidOperationException("Account no longer exists.");
            }
        }STORE_ERROR
    }
    void VegWayStore::ChangePassword(String^ id, String^ current, String^ next) {
        try {
            StoreInternal::UserId(id);if (next->Length < 8 || next->Length>128)throw gcnew ArgumentException("New password must contain 8 to 128 characters.");
            std::unique_ptr<sql::Connection> c(StoreInternal::Connect());
            std::unique_ptr<sql::PreparedStatement> q(c->prepareStatement("SELECT Password FROM users WHERE userid=?"));
            q->setString(1, StoreInternal::Utf8(id));std::unique_ptr<sql::ResultSet> r(q->executeQuery());
            if (!r->next())throw gcnew InvalidOperationException("Account no longer exists.");
            String^ old = StoreInternal::Managed(r->getString(1));
            if (!StoreInternal::Verify(current, old))throw gcnew ArgumentException("Current password is incorrect.");
            String^ updated = StoreInternal::Hash(next);
            std::unique_ptr<sql::PreparedStatement> s(c->prepareStatement("UPDATE users SET Password=? WHERE userid=? AND Password=?"));
            s->setString(1, StoreInternal::Utf8(updated));s->setString(2, StoreInternal::Utf8(id));s->setString(3, StoreInternal::Utf8(old));
            if (s->executeUpdate() != 1)throw gcnew InvalidOperationException("Account changed. Reopen settings and try again.");
        }STORE_ERROR
    }
    MarketProduct^ VegWayStore::Product(String^ itemId) {
        try {
            UInt64 n;if (!UInt64::TryParse(itemId, n) || !n)throw gcnew ArgumentException("Invalid item ID.");
            std::unique_ptr<sql::Connection> c(StoreInternal::Connect());
            std::unique_ptr<sql::PreparedStatement> s(c->prepareStatement("SELECT vegetable_name,seller_userid,quantity_kg,price_per_kg,is_active FROM vegetables WHERE vegetable_id=?"));
            s->setString(1, StoreInternal::Utf8(itemId));std::unique_ptr<sql::ResultSet> r(s->executeQuery());
            if (!r->next())throw gcnew InvalidOperationException("This item no longer exists.");
            MarketProduct^ p = gcnew MarketProduct();p->Name = StoreInternal::Managed(r->getString(1));p->SellerId = StoreInternal::Managed(r->getString(2));
            p->Stock = StoreInternal::Money(r->getString(3));p->Price = StoreInternal::Money(r->getString(4));p->Active = r->getBoolean(5);return p;
        }STORE_ERROR
    }
    String^ VegWayStore::Checkout(String^ buyerId, String^ itemId, Decimal quantity, Decimal quote, String^ token) {
        try {
            StoreInternal::UserId(buyerId);UInt64 n;Guid guid;
            if (!UInt64::TryParse(itemId, n) || !n || !Guid::TryParse(token, guid))throw gcnew ArgumentException("Invalid checkout details.");
            if (quantity <= Decimal::Zero || Decimal::Round(quantity, 3) != quantity)throw gcnew ArgumentException("Enter a positive quantity with up to 3 decimal places.");
            std::unique_ptr<sql::Connection> c(StoreInternal::Connect());c->setAutoCommit(false);
            try {
                // Every checkout locks the listing before checking the retry token.
                std::unique_ptr<sql::PreparedStatement> q(c->prepareStatement("SELECT seller_userid,vegetable_name,quantity_kg,price_per_kg,is_active FROM vegetables WHERE vegetable_id=? FOR UPDATE"));
                q->setString(1, StoreInternal::Utf8(itemId));std::unique_ptr<sql::ResultSet> r(q->executeQuery());
                if (!r->next())throw gcnew InvalidOperationException("Item is no longer available.");
                String^ seller = StoreInternal::Managed(r->getString(1));String^ item = StoreInternal::Managed(r->getString(2));
                Decimal stock = StoreInternal::Money(r->getString(3)), price = StoreInternal::Money(r->getString(4));bool active = r->getBoolean(5);
                std::unique_ptr<sql::PreparedStatement> old(c->prepareStatement("SELECT order_id,buyer_userid,vegetable_id FROM vegway_orders WHERE checkout_token=? FOR UPDATE"));
                old->setString(1, StoreInternal::Utf8(token));std::unique_ptr<sql::ResultSet> prior(old->executeQuery());
                if (prior->next()) {
                    if (StoreInternal::Managed(prior->getString(2)) != buyerId || StoreInternal::Managed(prior->getString(3)) != itemId)
                        throw gcnew InvalidOperationException("Checkout token belongs to another order.");
                    String^ previous = StoreInternal::Managed(prior->getString(1));c->commit();return previous;
                }
                if (seller == buyerId)throw gcnew InvalidOperationException("You cannot buy your own listing.");
                if (!active || stock < quantity)throw gcnew InvalidOperationException("Stock changed or the listing is inactive. Reload the order before confirming.");
                if (price != quote)throw gcnew InvalidOperationException("Price changed. Reload the order to review the new price.");
                Decimal total = Decimal::Round(price * quantity, 2, MidpointRounding::AwayFromZero);
                if (total <= Decimal::Zero)throw gcnew ArgumentException("The total must be at least Rs. 0.01.");
                std::unique_ptr<sql::PreparedStatement> update(c->prepareStatement("UPDATE vegetables SET quantity_kg=quantity_kg-? WHERE vegetable_id=? AND is_active=1 AND quantity_kg>=?"));
                update->setString(1, StoreInternal::Number(quantity));update->setString(2, StoreInternal::Utf8(itemId));update->setString(3, StoreInternal::Number(quantity));
                if (update->executeUpdate() != 1)throw gcnew InvalidOperationException("Insufficient stock.");
                std::unique_ptr<sql::PreparedStatement> insert(c->prepareStatement(
                    "INSERT INTO vegway_orders(checkout_token,buyer_userid,seller_userid,vegetable_id,item_name,quantity_kg,price_per_kg,total_amount) VALUES(?,?,?,?,?,?,?,?)"));
                insert->setString(1, StoreInternal::Utf8(token));insert->setString(2, StoreInternal::Utf8(buyerId));insert->setString(3, StoreInternal::Utf8(seller));
                insert->setString(4, StoreInternal::Utf8(itemId));insert->setString(5, StoreInternal::Utf8(item));insert->setString(6, StoreInternal::Number(quantity));
                insert->setString(7, StoreInternal::Number(price));insert->setString(8, StoreInternal::Number(total));insert->executeUpdate();
                std::unique_ptr<sql::PreparedStatement> last(c->prepareStatement("SELECT LAST_INSERT_ID()"));std::unique_ptr<sql::ResultSet> result(last->executeQuery());result->next();
                String^ orderId = StoreInternal::Managed(result->getString(1));c->commit();return orderId;
            }
            catch (...) { try { c->rollback(); } catch (...) {}throw; }
        }STORE_ERROR
    }
#undef STORE_ERROR
}

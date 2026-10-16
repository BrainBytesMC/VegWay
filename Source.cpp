#using <System.Windows.Forms.dll>


#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <mysql_connection.h>
#include <mysql_driver.h>

#include <memory>
#include <string>


bool SetupDatabase()
{



    try
    {
        sql::mysql::MySQL_Driver* driver =
            sql::mysql::get_mysql_driver_instance();

        std::unique_ptr<sql::Connection> con(
            driver->connect(
                "tcp://127.0.0.1:3306",
                "root",
                "rasu"
            )
        );

        std::unique_ptr<sql::Statement> stmt(
            con->createStatement()
        );

        stmt->execute(
            "CREATE DATABASE IF NOT EXISTS vegdb "
            "DEFAULT CHARACTER SET utf8mb4"
        );

        con->setSchema("vegdb");

        std::string createTableSQL =
            "CREATE TABLE IF NOT EXISTS users ("
            "userid INT UNSIGNED NOT NULL AUTO_INCREMENT,"
            "CustomerName VARCHAR(100) NOT NULL,"
            "Email VARCHAR(254) NOT NULL,"
            "Phonenumber VARCHAR(20) NOT NULL,"
            "Password VARCHAR(255) NOT NULL,"
            "PRIMARY KEY (userid),"
            "UNIQUE KEY uq_users_email (Email)"
            ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;";

        stmt->execute(createTableSQL);

        return true;
    }


    catch (const sql::SQLException& e)
    {
        System::Windows::Forms::MessageBox::Show(
            gcnew System::String(e.what()),
            "Database error"
        );

        return false;
    }

    


}
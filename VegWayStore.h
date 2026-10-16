#pragma once
#using <System.dll>
#using <System.Data.dll>
namespace VegWay {
    public ref class MarketProduct {
    public:
        System::String^ Name;
        System::String^ SellerId;
        System::Decimal Stock;
        System::Decimal Price;
        bool Active;
    };
    public ref class VegWayStore abstract sealed {
    public:
        static System::Data::DataTable^ Profile(System::String^ userId);
        static System::Data::DataTable^ BuyerOrders(System::String^ userId);
        static System::Data::DataTable^ Listings(System::String^ userId);
        static System::Data::DataTable^ DailySales(System::String^ userId);
        static System::Data::DataTable^ Totals(System::String^ userId);
        static System::DateTime SalesStart(System::String^ userId);
        static void ChangeName(System::String^ userId, System::String^ name);
        static void ChangePassword(System::String^ userId, System::String^ current, System::String^ next);
        static MarketProduct^ Product(System::String^ itemId);
        static System::String^ Checkout(System::String^ buyerId, System::String^ itemId,
            System::Decimal quantity, System::Decimal quotedPrice, System::String^ token);
    };
}

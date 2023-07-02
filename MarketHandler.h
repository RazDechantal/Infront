#pragma once
#include <iostream>
#include <string> // for std::string
#include <vector> // for std::vector

using namespace std;

class MarketHandler
{
public:
    MarketHandler();
    MarketHandler(string fileName);

    string filename = "";

    string readFile();
    void bFile();

    class Message
    {
    public:
    private:
        //  identifies the message type
        int8_t _header;
        enum MessageType
        {
            Best,
            Trade,
            TradeCancellation

        };
        // Identifies the listing to which this message is related.
        string symbol = "";
        // The current best bid price for the listing.
        double best_bid;
        // The current best ask price for the listing.
        double best_ask;
        int32_t trade_id;
        int64_t timestamp;
        int32_t quantity;
        double price;
    };

    ~MarketHandler();

private:
    double _length;
    string symbol = "";
};

// =======================================================================
//   Implementation section
// =======================================================================

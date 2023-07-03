#include "iostream"
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include <ctype.h>
#include <stdlib.h>
#include <climits>
#include <fstream>
#include <iterator>
#include "MarketHandler.h"

using namespace std;

struct message
{
    int8_t _header;
    std::string listing;
    double best_bid;
    double best_ask;
    int32_t trade_id;
    int64_t timestamp;
    int32_t quantity;
    double price;
};

std::vector<message> Messages;

MarketHandler::MarketHandler(string file)
{
    filename = file;
    cout << "Object with feeder: " << file << " was created!" << endl;
}

string MarketHandler::readFile()
{
    std::ifstream file(filename);
    string input = "";
    while (file >> input)
    {
        std::cout << input;
    }
    std::cout << "File: " << MarketHandler::filename << " has " << input.length() << " bytes!";
    return input;
}

void MarketHandler::bFile()
{
    struct message m = {};
    ifstream myFile(filename, ios::in | ios::binary);
    myFile.seekg(0, ios::end);
    size_t size = myFile.tellg();
    std::string buffer(size, ' ');
    myFile.seekg(0);
    myFile.read(&buffer[0], size);

    if (!myFile)
    {
        cout << "Reading file failed!" << endl;
        return;
    }
    else
    {
        cout << "Got " << myFile.gcount() << " characters:" << endl;
        for (int i = 0; i != myFile.gcount(); ++i)
        {
            switch (buffer[i])
            {
            case Best:
                // cout << "The position of the buffer in best is: " << i << endl;
                parseMessage(buffer, MessageType::Best, i);
                break;

            case Trade:
                parseMessage(buffer, MessageType::Trade, i);
                break;

            case TradeCancellation:
                parseMessage(buffer, MessageType::Trade, i);
                break;

            default:
                break;
            }
        }
    }

    // cout << endl;
}
std::ostream &operator<<(std::ostream &out, vector<message> v)
{
    out << v; // for example
    return out;
}

MarketHandler::~MarketHandler()
{
    cout << "destructed!" << endl;
}

void parseMessage(string buffer, int header, int position)
{
    message m = {};

    std::string bestAsk(8, ' ');
    std::string bestBid(8, ' ');
    std::string symbol(6, ' ');

    std::string tradeId(4, ' ');
    std::string timeStamp(8, ' ');
    std::string quantity(4, ' ');
    std::string price(8, ' ');

    // Type 1: Best Bid Ask
    int listing_start = 1 + position;
    int listing_end = 7 + position;
    int besAsk_start = 8 + position;
    int bestAsk_end = 16 + position;
    int bestBid_start = 17 + position;
    int bestBid_end = 25 + position;
    // Type 2:trade
    int tradId_start = 1 + position;
    int tradeId_end = 5 + position;
    int timeStamp_start = 6 + position;
    int timeStamp_end = 14 + position;
    int quantity_start = 15 + position;
    int quantity_end = 19 + position;
    int price_start = 20 + position;
    int price_end = 28 + position;

    // Type 3:

    int i = 0;
    // For Best
    if (header == Best)
    {
        // header
        m._header = 01;
        // Listing
        for (int j = listing_start; j <= listing_end; j++)
        {
            if (isalpha(buffer[j]) || isdigit(buffer[j]))
            {
                symbol[i] = buffer[j];
                ++i;
            }
        }
        i = 0;
        m.listing = symbol;
        // std::memcpy(&(m.listing), &symbol, sizeof(symbol));
        cout << "In BEST symbol is: " << m.listing << endl;

        // best bid
        for (int j = bestBid_start; j <= bestBid_end; j++)
        {
            if (isalpha(buffer[j]) || isdigit(buffer[j]))
            {
                bestBid[i] = buffer[j];
                ++i;
            }
        }
        i = 0;
        std::memcpy(&(m.best_bid), &bestBid, sizeof(double));
        m.best_bid = (bestBid[0] << 0) | (bestBid[1] << 8) | (bestBid[2] << 16) | ((unsigned)bestBid[3] << 24);
        cout << "In Best bid is: " << m.best_bid << endl;

        // best ask
        for (int j = besAsk_start; j <= bestAsk_end; j++)
        {
            if (isalpha(buffer[j]) || isdigit(buffer[j]))
            {
                bestAsk[i] = buffer[j];
                ++i;
            }
        }
        i = 0;
        std::memcpy(&(m.best_ask), &bestAsk, sizeof(double));
        m.best_ask = (bestAsk[0] << 0) | (bestAsk[1] << 8) | (bestAsk[2] << 16) | ((unsigned)bestAsk[3] << 24);
        cout << "In Best ask is: " << m.best_ask << endl;
        Messages.push_back(m);
    }

    //  string symb = symbolFind();

    if (header == Trade)
    {
        // header
        m._header = 02;
        for (int j = listing_start; j <= listing_end; j++)
        {
            if (isalpha(buffer[j]) || isdigit(buffer[j]))
            {
                symbol[i] = buffer[j];
                ++i;
            }
        }
        i = 0;
        m.listing = symbol;
        cout << "In trade, symbol is: " << m.listing << endl;

        // trade id
        for (int j = tradId_start; j <= tradeId_end; j++)
        {
            if (isalpha(buffer[j]) || isdigit(buffer[j]))
            {
                tradeId[i] = buffer[j - i - 1];
                ++i;
            }
        }

        i = 0;
        std::memcpy(&(m.trade_id), &tradeId, sizeof(int32_t));
        m.trade_id = (tradeId[0] << 0) | (tradeId[1] << 8) | (tradeId[2] << 16) | ((unsigned)tradeId[3] << 24);
        cout << "In Trade, trade id  is: " << m.trade_id << endl;

        // timestamp
        for (int j = timeStamp_start; j <= timeStamp_end; j++)
        {
            if (isalpha(buffer[j]) || isdigit(buffer[j]))
            {
                timeStamp[i] = buffer[j];
                ++i;
            }
        }
        i = 0;
        std::memcpy(&(m.timestamp), &timeStamp, sizeof(int64_t));
        m.timestamp = (timeStamp[0] << 0) | (timeStamp[1] << 8) | (timeStamp[2] << 16) | ((unsigned)timeStamp[3] << 24);
        cout << "At time: " << m.timestamp << endl;

        // quantity
        for (int j = quantity_start; j <= quantity_end; j++)
        {
            if (isalpha(buffer[j]) || isdigit(buffer[j]))
            {
                quantity[i] = buffer[j];
                ++i;
            }
        }
        i = 0;
        std::memcpy(&(m.quantity), &quantity, sizeof(int32_t));
        m.quantity = (quantity[0] << 0) | (quantity[1] << 8) | (quantity[2] << 16) | ((unsigned)quantity[3] << 24);
        cout << "In Trade, quantity: " << m.quantity << endl;

        // price
        for (int j = price_start; j <= price_end; j++)
        {
            if (isalpha(buffer[j]) || isdigit(buffer[j]))
            {
                price[i] = buffer[j];
                ++i;
            }
        }
        i = 0;
        double p = (price[0] << 0) | (price[1] << 8) | (price[2] << 16) | ((unsigned)price[3] << 24);
        std::memcpy(&(m.price), &p, sizeof(double));

        cout << "In Trade Price is: " << m.price << endl;
        Messages.push_back(m);
    }

    if (header == TradeCancellation)
    {
        // header
        m._header = 03;
        for (int j = listing_start; j <= listing_end; j++)
        {
            if (isalpha(buffer[j]) || isdigit(buffer[j]))
            {
                symbol[i] = buffer[j];
                ++i;
            }
        }
        i = 0;
        m.listing = symbol;
        cout << "In cancellation, symbol is: " << m.listing << endl;

        // trade id
        for (int j = tradId_start; j <= tradeId_end; j++)
        {
            if (isalpha(buffer[j]) || isdigit(buffer[j]))
            {
                tradeId[i] = buffer[j - i - 1];
                ++i;
            }
        }

        i = 0;
        std::memcpy(&(m.trade_id), &tradeId, sizeof(int32_t));
        int32_t ddd = (tradeId[0] << 0) | (tradeId[1] << 8) | (tradeId[2] << 16) | ((unsigned)tradeId[3] << 24);
        cout << "In Cancellation, trade id  is: " << ddd << endl;
        Messages.push_back(m);
    }

    return;
}
void printMessages()
{
    cout << "Number of messages in queue: " << Messages.size() << endl;
    cout << endl;

    std::cout << "Trade messages based on their listings" << endl;
    std::cout << "Type of traade     trade id     Bid \t\t Ask \t\t quantity \t Price \t\t Time " << endl;
    for (unsigned i = 0; i < Messages.size(); i++)
    {
        std::cout << "______________________________________________________________________________________________________________________________" << endl;
        std::cout << Messages.at(i)._header
                  << "\t " << Messages.at(i).trade_id
                  << "\t " << Messages.at(i).best_bid
                  << "\t\t" << Messages.at(i).best_ask
                  << "\t\t" << Messages.at(i).quantity
                  << "\t" << Messages.at(i).price
                  << "\t\t" << Messages.at(i).timestamp << endl;
    }
}

ostream &operator<<(ostream &output, const message &m)
{
    output << m << endl;
    return output;
}

void writeFile()
{
    std::ofstream myfile;
    myfile.open("output.txt");

    double highestBid = 0;
    double highestAsk = 0;
    int numberOfTrade = 0;
    int32_t sumOfQuantity = 0;
    int64_t totalTurnOver = 0;
    for (auto &m : Messages)
    {
        if (m.best_bid > highestBid)
            highestBid = m.best_bid;
        if (m.best_ask > highestAsk)
            highestAsk = m.best_ask;
        if (m._header == 02)
            numberOfTrade++;
        sumOfQuantity += m.quantity;
        totalTurnOver += (m.price * m.quantity);
    }
    myfile << "highest bid: " << highestBid
           << " highest ask: " << highestAsk
           << " Total number of trades " << numberOfTrade
           << " Total turn over " << totalTurnOver << endl;
    myfile.close();
    return;
}

#pragma once
#include <iostream>
#include <string> // for std::string
#include <vector> // for std::vector
#include <fstream>

using namespace std;

class MarketHandler
{
public:
    std::string filename = "";
    MarketHandler(string file);

    std::string readFile();
    void bFile();

    ~MarketHandler();

private:
    double _length;
    std::string symbol = "";
};
enum MessageType
{
    Best = 1,
    Trade = 2,
    TradeCancellation = 3

};

void parseMessage(string buffer, int header, int position);
void writeFile();
template <typename T>
std::ofstream &operator<<(std::ofstream &s, std::vector<T> v);
void printMessages();

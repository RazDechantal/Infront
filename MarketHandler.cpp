#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "MarketHandler.h"

MarketHandler::MarketHandler()
{
}

MarketHandler::MarketHandler(string fileName)
{
    filename = fileName;
    cout << "Object with feeder: " << filename << " was created!" << endl;
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
    MarketHandler::Message m;

    // uint8_t id;

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
            case 01:

                /* code */
                break;

            case 02:
                /* code */
                break;

            case 03:
                /* code */
                break;

            default:
                break;
            }
            if (buffer[i] == 03)
            {
                cout << buffer[i];
            }
        }
        cout << endl;
    }

    std::string tohexed = ToHex(std::string(buffer, size), true);

    std::cout << "Buffer: " << buffer << std::endl;
    std::cout << "Conversion to Hex: " << tohexed << std::endl;
}

string MarketHandler::ToHex(const string &s, bool upper_case)
{
    std::ostringstream ret;

    for (string::size_type i = 0; i < s.length(); ++i)
        ret << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << (int)s[i];

    return ret.str();
}

MarketHandler::~MarketHandler()
{
}

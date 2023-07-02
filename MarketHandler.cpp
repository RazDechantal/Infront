#include <iostream>
#include <fstream>
#include <string>
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
        // An error occurred!
        // myFile.gcount() returns the number of bytes read.
        // calling myFile.clear() will reset the stream state
        // so it is usable again.
    }

    cout << "So far so good! The first identifier is: " << buffer << endl;

    /*     ofstream f(filename, ios::out | ios::binary);
        if (!f)
        {
            cout << "Cannot open file!" << endl;
            return;
        }
     */
}

MarketHandler::~MarketHandler()
{
}

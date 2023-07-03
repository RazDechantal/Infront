#include <iostream>
#include "MarketHandler.h"

using namespace std;

int main()
{
    string file = "input_feed";
    cout << "The project started!" << endl;

    MarketHandler mh(file);

    // Reading and parsing the files
    mh.bFile();

    // Printing the message
    printMessages();
    // writes the messages to the file
    writeFile();

    return 0;
}
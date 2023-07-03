#include <iostream>
#include "MarketHandler.h"

using namespace std;

int main()
{
    string file = "input_feed";
    cout << "The project started!" << endl;

    MarketHandler mh(file);

    mh.bFile();

    writeFile();

    return 0;
}
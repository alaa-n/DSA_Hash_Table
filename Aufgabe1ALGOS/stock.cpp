#include "stock.h"

stock::stock(){
    cout << "Enter stock name: " << endl;                                           // get data of the stock and save them in the struct
    cin.ignore();
    getline(cin, name);
    cout << "Enter WKN: " << endl;
    cin >> wkn;
    cout << "Enter stock symbol: " << endl;
    cin >> symbol;

    for (int i = 0; i < MAX_DAYS; i++) {
        data[i].setDate(""); // initialize each stockData object to null
        data[i].setOpen(0.0);
        data[i].setHigh(0.0);
        data[i].setLow(0.0);
        data[i].setClose(0.0);
        data[i].setAdjClose(0.0);
        data[i].setVolume(0.0);
    }
}
stock::stock(string name, string wkn, string symbol) {
    this->name = name;
    this->wkn = wkn;
    this->symbol = symbol;

    for (int i = 0; i < MAX_DAYS; i++) {
        data[i].setDate(""); // initialize each stockData object to null
        data[i].setOpen(0.0);
        data[i].setHigh(0.0);
        data[i].setLow(0.0);
        data[i].setClose(0.0);
        data[i].setAdjClose(0.0);
        data[i].setVolume(0.0);
    }
}

string stock::getName(){
    return name;
}

string stock::getWKN(){
    return wkn;
}

string stock::getSymbol(){
    return symbol;
}
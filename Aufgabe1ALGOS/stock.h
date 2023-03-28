#ifndef AUFGABE1ALGOS_STOCK_H
#define AUFGABE1ALGOS_STOCK_H

#include "stockData.h"
#define MAX_DAYS 30

using namespace std;

class stock {
    string name;
    string wkn;
    string symbol;

public:
    stock();
    stock(string name, string wkn, string symbol);
    string getName();
    string getWKN();
    string getSymbol();
    stockData data[MAX_DAYS];
};


#endif //AUFGABE1ALGOS_STOCK_H

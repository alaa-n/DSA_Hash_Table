#ifndef AUFGABE1ALGOS_HASHTABLE_H
#define AUFGABE1ALGOS_HASHTABLE_H

#include "define.h"
#define TABLE_SIZE 1301                                 // gute tabellengroesse ca. (1,3 * max key nrs) -> 1300 -> prime number closest to 1300: 1301


using namespace std;

class stock;

class hashTable {
    stock *table[TABLE_SIZE];
public:
    hashTable();

    unsigned int hash(string name);
    bool insertToTable(string nameORsymbol, stock& stock1);
    stock* checkStockExists(string nameORsymbol, char type);
    stock* searchThroughName();
    stock* searchThroughSymbol();
    bool deleteStockByName(string name);
    bool deleteStockBySymbol(string symbol);
    bool import();
    bool save();
    bool load();
    bool plot();
};


#endif //AUFGABE1ALGOS_HASHTABLE_H

#include <iostream>

#include "define.h"

hashTable hashName;
hashTable hashSymbol;

int main() {
    char menu[10];
    do {
        printf("Choose an action: ADD | DEL | IMPORT | SEARCH | PLOT | SAVE | LOAD | QUIT\n");
        scanf("%s", menu);

        if (strcasecmp(menu, "ADD") == 0){
            auto* stock1 = new stock;
            hashName.insertToTable(stock1->getName(), *stock1);
            hashSymbol.insertToTable(stock1->getSymbol(), *stock1);
        }
        else if (strcasecmp(menu, "DEL") == 0){
            string name, symbol;
            cout << "Enter stock name to delete: " << endl;
            cin >> name;
            cout << "Enter stock symbol: " << endl;
            cin >> symbol;

            hashName.deleteStockByName(name);
            hashSymbol.deleteStockBySymbol(symbol);
        }
        else if (strcasecmp(menu, "IMPORT") == 0){
            hashName.import();
        }
        else if (strcasecmp(menu, "SEARCH") == 0){
            string searchThrough;
            cout << "Enter 'NAME' to search through stock name, 'SYMBOL' to search through stock symbol, or 'X' to quit search." << endl;
            cin >> searchThrough;

            if (searchThrough.compare("NAME") == 0 || searchThrough.compare("name") == 0 ) {
                hashName.searchThroughName();
            }
            else if (searchThrough.compare("SYMBOL") == 0 || searchThrough.compare("symbol") == 0 ) {
                hashSymbol.searchThroughSymbol();
            }

            else if (searchThrough.compare("X") != 0){
                cout << "Invalid entry!" << endl;
            }
        }
        else if (strcasecmp(menu, "PLOT") == 0){
            hashName.plot();
        }
        else if (strcasecmp(menu, "SAVE") == 0){
            string choice;
            cout << "Enter 'NAME' to save name table or 'SYMBOL' to save symbol table" << endl;
            cin >> choice;
            if (choice.compare("NAME") == 0 || choice.compare("name") == 0 ) {
                hashName.save();
            }
            else if (choice.compare("SYMBOL") == 0 || choice.compare("symbol") == 0 ) {
                hashSymbol.save();
            }
            else if (choice.compare("X") != 0){
                cout << "Invalid entry!" << endl;
            }
        }
        else if (strcasecmp(menu, "LOAD") == 0){
            string choice;
            cout << "Enter 'NAME' to load name table or 'SYMBOL' to load symbol table" << endl;
            cin >> choice;
            if (choice.compare("NAME") == 0 || choice.compare("name") == 0 ) {
                hashName.load();
            }
            else if (choice.compare("SYMBOL") == 0 || choice.compare("symbol") == 0 ) {
                hashSymbol.load();
            }
            else if (choice.compare("X") != 0){
                cout << "Invalid entry!" << endl;
            }
        }
        else if (strcasecmp(menu, "QUIT") == 0){
            cout << "Choice: QUIT" << endl;
        }
        else {
            cout << "Entry not valid! Choose an action from the menu." << endl;;
        }

    } while (strcasecmp(menu, "QUIT") != 0);

    return 0;
}
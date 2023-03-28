#include "define.h"

hashTable::hashTable(){                                        // HASH TABLE SHOULD BE EMPTY IN THE BEGINNING
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = NULL;                            // -> SET THE WHOLE TABLE TO NULL BEFORE INSERTING ANY VALUES INTO IT
    }
}

unsigned int hashTable::hash(string name){                          // hash function that generates hash value for the given stock
    unsigned int hashValue = 0;

    // turn to lower case before hashing to make it case insensitive:
    string result = name;
    transform(result.begin(), result.end(), result.begin(), ::tolower);


    int length = size(result);
    for (int i = 0; i < length; ++i) {
        hashValue += result[i];
        hashValue = (hashValue * result[i]) % TABLE_SIZE;
    }
    return hashValue;
}
bool hashTable::insertToTable(string nameORsymbol, stock& stock1){
    // turn to lower case before hashing to make it case insensitive:
    string result = nameORsymbol;
    transform(result.begin(), result.end(), result.begin(), ::tolower);

    int index = hash(result);                                         // hash the stock by its name and get its index

    for (int i = 0; i < TABLE_SIZE; i++) {                               // i *= i because we are using quadratic probing
        int test = (index + i*i) % TABLE_SIZE;                                 // hi(x) = h(x) + i^2 mod m ; wobei i in der for() quadriert wird und m die groesse der hashtabelle entspricht
        if (table[test] == NULL || table[test] == DELETED_NODE){      // we can use null indexes bc they're empty or deleted indexes bc they are also now empty and available to use
            table[test] = &stock1;
            return true;
        }
    }
    return false;
}
stock* hashTable::checkStockExists(string nameORsymbol, char type){

    int index = hash(nameORsymbol);                                                 // we hash the name to get the index it would be saved in and then check what is in the table at that index or quadratically entfernt davon

    for (int i = 0; i < TABLE_SIZE; i++) {
        int test = (index + i*i) % TABLE_SIZE;

        if (table[test] == NULL) {                                       // as mention oben bei define deleted_node: wenn wir bei der suche NULL erreichen,
            return nullptr;                                                   // ist es nicht mehr moeglich, dass diese aktie noch weiter vorhanden ist.
        }

        if (table[test] == DELETED_NODE) continue;                       // wenn wir eine deleted finden, soll das unsere suche nicht stoeren, current i wird uebersprungen und suche fortgesetzt mit naechstem i.

        if (type == 'n') {

            string lowerName = table[test]->getName();
            transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

            if (lowerName.compare(nameORsymbol) == 0) {         // if not null or deleted: check if the name that we are looking for matches the name the hash table delivered
                return table[test];
            }
        } else if (type == 's'){

            string lowerSymbol = table[test]->getSymbol();
            transform(lowerSymbol.begin(), lowerSymbol.end(), lowerSymbol.begin(), ::tolower);

            if (lowerSymbol.compare(nameORsymbol) == 0) {         // if not null or deleted: check if the name that we are looking for matches the name the hash table delivered
                return table[test];
            }
        }
    }
    return nullptr;
}
stock* hashTable::searchThroughName() {
    string name;
    cout << "Enter stock name: " << endl;
    cin.ignore();
    getline(cin, name);
    // make lowercase
    string result = name;
    transform(result.begin(), result.end(), result.begin(), ::tolower);

    stock* stock1 = checkStockExists(result, 'n');
    int latestEntryIndex = MAX_DAYS-1;
    if(!stock1){
        cout << "Stock not found!" << endl;
        return nullptr;
    } else if (stock1->data[latestEntryIndex].getDate() == ""){
        cout << "Stock " << stock1->getName() << " (" << stock1->getSymbol() << ") found successfully. No data imported. Select option IMPORT to add data." << endl;
        return stock1;
    }
    else {
        cout << "Stock " << stock1->getName() << " (" << stock1->getSymbol() << ") found. "
        << endl << "Latest Stock Entry - Date: " << stock1->data[latestEntryIndex].getDate() << " open: " << stock1->data[latestEntryIndex].getOpen() <<
             " high: " << stock1->data[latestEntryIndex].getHigh() << " low: " << stock1->data[latestEntryIndex].getLow() << " close: " << stock1->data[latestEntryIndex].getClose() <<
             " adjClose: " << stock1->data[latestEntryIndex].getClose() << " volume: " << stock1->data[latestEntryIndex].getVolume() << endl;
        return stock1;
    }
}
stock* hashTable::searchThroughSymbol() {
    string symbol;
    cout << "Enter stock symbol: " << endl;
    cin >> symbol;

    // turn to lower case before hashing to make it case insensitive:
    string result = symbol;
    transform(result.begin(), result.end(), result.begin(), ::tolower);

    stock* stock1 = checkStockExists(result, 's');
    int latestEntryIndex = MAX_DAYS-1;
    if(!stock1){
        cout << "Stock not found!" << endl;
        return nullptr;
    } else if (stock1->data[latestEntryIndex].getDate() == ""){
        cout << "Stock " << stock1->getName() << " (" << stock1->getSymbol() << ") found successfully. No data imported. Select option IMPORT to add data." << endl;
        return stock1;
    }
    else {
        cout << "Stock " << stock1->getName() << " (" << stock1->getSymbol() << ") found. "
        << endl << "Latest Stock Entry - Date: " << stock1->data[latestEntryIndex].getDate() << " open: " << stock1->data[latestEntryIndex].getOpen() <<
             " high: " << stock1->data[latestEntryIndex].getHigh() << " low: " << stock1->data[latestEntryIndex].getLow() << " close: " << stock1->data[latestEntryIndex].getClose() <<
             " adjClose: " << stock1->data[latestEntryIndex].getClose() << " volume: " << stock1->data[latestEntryIndex].getVolume() << endl;
        return stock1;
    }
}
bool hashTable::deleteStockByName(string name){
    // turn to lower case before hashing to make it case insensitive:
    string result = name;
    transform(result.begin(), result.end(), result.begin(), ::tolower);

    int index = hash(result); // hash the stock by its name and get its index

    stock* deleteMe = checkStockExists(result, 'n');

    if(deleteMe != nullptr){
        delete deleteMe;
        table[index] = DELETED_NODE; // mark the index as deleted
        cout << "Stock deleted successfully." << endl;
        return true;
    } else {
        cout << "Stock not found. Check if Name and Symbol entered correctly." << endl;
    }
    return false; // the stock was not found in the hash table
}
bool hashTable::deleteStockBySymbol(string symbol) {
    // turn to lower case before hashing to make it case insensitive:
    string result = symbol;
    transform(result.begin(), result.end(), result.begin(), ::tolower);

    int index = hash(result); // hash the stock by its name and get its index

    stock* deleteMe = checkStockExists(result, 's');

    if(deleteMe != nullptr){
        table[index] = DELETED_NODE; // mark the index as deleted
        return true;
    }
    return false; // the stock was not found in the hash table
}
bool hashTable::import(){                                          // importiert die data aus der csv datei von den letzten 30 tagen in die stock struct

    string name;
    cout << "Enter stock name: " << endl;
    cin.ignore();
    getline(cin, name);

    // turn to lower case before hashing to make it case insensitive:
    string result = name;
    transform(result.begin(), result.end(), result.begin(), ::tolower);

    stock* stock1 = checkStockExists(result, 'n');
    if(!stock1){
        cout << "Stock does not exist! Add stock before importing data." << endl;
        return false;
    }

    // FILE HANDELING:

    string path = FILE_PATH;
    string filename = path + stock1->getSymbol() + ".csv";   // haengt .csv zum symbol und speichert das ganze als filename

    ifstream file(filename);

    if (file.is_open()) {
        cout << "File opened successfully." << endl;

        // Count the number of lines in the file
        int num_lines = 0;
        string line;
        while (getline(file, line)) {
            num_lines++;
        }

        // Read the last 30 lines of the file into an array of structs
        file.clear();
        file.seekg(0, ios::beg);
        int start_line = num_lines - MAX_DAYS;
        if (start_line < 0) {
            start_line = 0;
        }
        int i = 0;
        int index = 0;
        while (getline(file, line)) {
            if (i >= start_line) {
                stockData stock_data;
                stringstream ss(line);
                string date_str, open_str, high_str, low_str, close_str, adj_close_str, volume_str;
                getline(ss, date_str, ',');
                getline(ss, open_str, ',');
                getline(ss, high_str, ',');
                getline(ss, low_str, ',');
                getline(ss, close_str, ',');
                getline(ss, adj_close_str, ',');
                getline(ss, volume_str, '\n');

                stock_data.setDate(date_str);
                stock_data.setOpen(stof(open_str));
                stock_data.setHigh(stof(high_str));
                stock_data.setLow(stof(low_str));
                stock_data.setClose(stof(close_str));
                stock_data.setAdjClose(stof(adj_close_str));
                stock_data.setVolume(stoi(volume_str));

                stock1->data[index] = stock_data;
                index++;
            }
            i++;
        }

        file.close();

        cout << "Data imported successfully." << endl;
    }
    else {
        cout << "Failed to open file." << endl;
        return false;
    }
    return true;
}
bool hashTable::save(){
    FILE *fp;
    string filename;
    cout << "Enter file name: " << endl;
    cin >> filename;

    filename = FILE_PATH + filename + ".txt";

    ofstream outFile(filename);

    if (outFile.is_open()) {
            for (int i = 0; i < TABLE_SIZE; i++) {
                if (table[i] != NULL && table[i] != DELETED_NODE) {
                    outFile << i << "," << table[i]->getName() << "," << table[i]->getWKN() << "," << table[i]->getSymbol() << ",";
                    for (int j = 0; j < MAX_DAYS; j++) {
                        if (table[i]->data->getDate() != "") {
                            outFile << table[i]->data[j].getDate() << ","
                                    << table[i]->data[j].getOpen() << ","
                                    << table[i]->data[j].getHigh() << ","
                                    << table[i]->data[j].getLow() << ","
                                    << table[i]->data[j].getClose() << ","
                                    << table[i]->data[j].getAdjClose() << ","
                                    << table[i]->data[j].getVolume();
                                    if(j != MAX_DAYS-1){
                                       outFile << ",";
                                    } else {
                                        outFile << "\n";
                                    }
                        }
                    }
                }
            }


        outFile.close();

        cout << "Table exported successfully." << endl;

        return true;
    } else {
        cout << "Unable to open file." << endl;
        return false;
    }
}
bool hashTable::load() {
    string filename;
    cout << "Enter file name: " << endl;
    cin >> filename;

    string path = FILE_PATH;
    filename = path + filename + ".txt";

    ifstream inFile(filename);

    if (inFile.is_open()) {
        // Clear existing data in table
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = NULL;                            // -> SET THE WHOLE TABLE TO NULL BEFORE INSERTING ANY VALUES INTO IT
        }

        // Read data from file and populate table
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string index_str, name, wkn, symbol;
            getline(ss, index_str, ',');
            getline(ss, name, ',');
            getline(ss, wkn, ',');
            getline(ss, symbol, ',');

            int index = stoi(index_str);

            stock* stock1 = new stock(name, wkn, symbol);
            table[index] = stock1;

            stockData stock_data;
            for (int j = 0; j < MAX_DAYS; j++) {
                string date_str;
                string open_str, high_str, low_str, close_str, adj_close_str, volume_str;
                getline(ss, date_str, ',');
                if (date_str == "") {
                    break;
                }
                getline(ss, open_str, ',');
                getline(ss, high_str, ',');
                getline(ss, low_str, ',');
                getline(ss, close_str, ',');
                getline(ss, adj_close_str, ',');
                getline(ss, volume_str, ',');

                stock_data.setDate(date_str);
                stock_data.setOpen(stof(open_str));
                stock_data.setHigh(stof(high_str));
                stock_data.setLow(stof(low_str));
                stock_data.setClose(stof(close_str));
                stock_data.setAdjClose(stof(adj_close_str));
                stock_data.setVolume(stoi(volume_str));

                stock1->data[j] = stock_data;
            }
        }

        inFile.close();

        cout << "Table imported successfully." << endl;

        return true;
    } else {
        cout << "Unable to open file." << endl;
        return false;
    }
}
bool hashTable::plot() {
    // Search for the stock in the hash table
    string name;
    cout << "Enter stock name: " << endl;
    cin >> name;

    // turn to lower case before hashing to make it case insensitive:
    string result = name;
    transform(result.begin(), result.end(), result.begin(), ::tolower);

    stock* stock1 = checkStockExists(result, 'n');
    int latestEntryIndex = MAX_DAYS-1;

    if(!stock1){
        cout << "Stock does not exist! Add stock and import data before plotting." << endl;
        return false;
    } else if(stock1->data[latestEntryIndex].getDate() == "") {
        cout << "Stock " << stock1->getName() << " (" << stock1->getSymbol() << ") found successfully. No data imported. Select option IMPORT to add data." << endl;
        return false;
    } else {
        // Plot the close values using a simple ASCII chart
        cout << "Close values for " << stock1->getName() << " (" << stock1->getSymbol() << "):" << endl;
        for (int i = 0; i < MAX_DAYS; i++) {
            double value = stock1->data[i].getClose();
            int stars = static_cast<int>(value / 10.0);
            cout << stock1->data[i].getDate() << "  ";
            for (int j = 0; j < stars; j++) {
                cout << "*";
            }
            cout << "  " << value << endl;
        }
        return true;
    }
}

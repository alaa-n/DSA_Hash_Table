#ifndef AUFGABE1ALGOS_DEFINE_H
#define AUFGABE1ALGOS_DEFINE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "stock.h"
#include "stockData.h"
#include "hashTable.h"


#define FILE_PATH "/Users/alaa/Desktop/Aufgabe1ALGOS/files/"
#define MAX_STOCKS 1000                                 // lt. Angabe
#define TABLE_SIZE 1301                                 // gute tabellengroesse ca. (1,3 * max key nrs) -> 1300 -> prime number closest to 1300: 1301
#define MAX_NAME 20
#define WKN_LENGTH 7                                    // 6-stellig + \0
#define MAX_SYMBOL 6                                    // 5-stellig + \0
#define DELETED_NODE  (stock *)(0xFFFFFFFFFFFFFFFFUL)   // hilfreich bei der suche: wenn wir suchen, sollen wir soweit weiter gehen, bis wir null erreichen, weil ab null bedeutet es dass
/* es noch keine aktien hier inserted wurden. Wenn wir beim loeschen die geloeschten auf null zeigen lassen statt deleted, dann
   stoert das unsere search efficiency, weil man nicht mehr 100% sagen kann, dass es nicht moeglich ist, dass die aktien noch weiter
   vorne sind. Wenn wir also beim deleten unterscheiden und nicht null verwenden, koennen wir beim searchen immer noch dann aufhoeren,
   wenn wir null erreichen. */

#endif //AUFGABE1ALGOS_DEFINE_H

#ifndef AUFGABE1ALGOS_STOCKDATA_H
#define AUFGABE1ALGOS_STOCKDATA_H

#include "define.h"

class stockData {
    std::string date;
    double open;
    double high;
    double low;
    double close;
    double adjClose;
    int volume;

public:
    stockData(){}
    stockData(std::string date, double open, double high, double low, double close, double adjClose, int volume){
        this->date = date;
        this->open = open;
        this->high = high;
        this->low = low;
        this->close = close;
        this->adjClose = adjClose;
        this->volume = volume;
    }
    std::string getDate(){
        return date;
    }
    std::string setDate(std::string date){
        this->date = date;
        return this->date;
    }
    double getOpen(){
        return open;
    }
    double setOpen(double open){
        this->open = open;
        return this->open;
    }
    double getHigh(){
        return high;
    }
    double setHigh(double high){
        this->high = high;
        return this->high;
    }
    double getLow(){
        return low;
    }
    double setLow(double low){
        this->low = low;
        return this->low;
    }
    double getClose(){
        return close;
    }
    double setClose(double close){
        this->close = close;
        return this->close;
    }
    double getAdjClose(){
        return adjClose;
    }
    double setAdjClose(double adjClose){
        this->adjClose = adjClose;
        return this->adjClose;
    }
    int getVolume(){
        return volume;
    }
    int setVolume(int volume){
        this->volume = volume;
        return this->volume;
    }

};
#endif //AUFGABE1ALGOS_STOCKDATA_H

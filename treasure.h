#ifndef _TREASURE_H_
#define _TREASURE_H_
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "item.h"

class Treasure: public Item{
    int amount;
    bool pick;
    int type; //6 - normal gold pile, 7 - small hoard, 8 - merchant hoard, 9 - dragon hoard

    public:
    Treasure(int, int, int, bool, int);
    ~Treasure() { }
    int getAmt();
    bool getPick();
    void setAmt(int);
    void setPick(bool);
    int getType();
};

#endif

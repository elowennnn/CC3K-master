#ifndef _POTION_H_
#define _POTION_H_
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "item.h"

class Potion: public Item{
    int type;

    public:
    Potion(int, int, int);
    ~Potion() { }
    int getType();
};

#endif

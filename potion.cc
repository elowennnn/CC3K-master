#include "potion.h"

Potion::Potion(int row, int col, int type):
    Item{row, col}, type{type} { }

int Potion::getType(){
    return type;
}

#include "item.h"

Item::Item(int row, int col, char origin):
    row{row}, col{col}, originalChar{origin} { }

int Item::getRow(){
    return row;
}

int Item::getCol(){
    return col;
}

char Item::getOrigin(){
    return originalChar;
}

void Item::setRow(int r){
    this->row = r;
}

void Item::setCol(int c){
    this->col = c;
}

void Item::setOrigin(char c){
    originalChar = c;
}

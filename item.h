#ifndef _ITEM_H_
#define _ITEM_H_
#include <iostream>
#include <vector>
#include <memory>

class Item{
protected:
    int row;
    int col;
    char originalChar;

public:
    Item(int, int, char c = '.');
    ~Item() { }
    int getRow();
    int getCol();
    char getOrigin();
    void setRow(int);
    void setCol(int);
    void setOrigin(char);

};

#endif

#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <memory>
class Gold;

class Character{
protected:
    double health;
    double attack;
    double defense;
    int row;
    int col;
    char originalChar;

public:
    Character(double, double, double, int, int, char origin = '.');
    virtual ~Character() { }
    double getHP();
    double getAtk();
    double getDF();
    int getRow();
    int getCol();
    char getOrigin();
    void moveRow(int);
    void moveCol(int);
    void addAtk(double);
    void addDF(double);
    void addHP(double);
    void setRow(int);
    void setCol(int);
    void setOrigin(char);
};
#endif

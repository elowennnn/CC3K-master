#include "character.h"
#include "treasure/sHoard.h"
#include "treasure/gold.h"
#include "treasure/mHoard.h"
#include "treasure/dHoard.h"

Character::Character(double h, double atk, double def, int row, int col, char c):
    health{h}, attack{atk}, defense{def}, row{row}, col{col}, originalChar{c}{ }

double Character::getHP(){
    return health;
}

double Character::getAtk(){
    return attack;
}

double Character::getDF(){
    return defense;
}


int Character::getRow(){
    return row;
}

int Character::getCol(){
    return col;
}

char Character::getOrigin(){
    return originalChar;
}

void Character::moveRow(int r){
    row += r;
}

void Character::moveCol(int c){
    col += c;
}

void Character::addHP(double h){
    health += h;
}

void Character::addAtk(double atk){
    attack += atk;
}

void Character::addDF(double def){
    defense += def;
}

void Character::setRow(int r){
    row = r;
}

void Character::setCol(int c){
    col = c;
}

void Character::setOrigin(char c){
    originalChar = c;
}

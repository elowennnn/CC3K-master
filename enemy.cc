#include "enemy.h"
#include <cmath>
#include <iostream>

#include "enemy/human.h"
#include "enemy/dwarf.h"
#include "enemy/elf.h"
#include "enemy/halfling.h"
#include "enemy/dragon.h"
#include "enemy/merchant.h"
#include "enemy/orcs.h"

using namespace std;

shared_ptr<Enemy> concreteType::getEnemy() {
    shared_ptr<Enemy> e;
    if (type == 'H'){
        e = make_shared<Human>();
    }
    else if (type == 'W'){
        e = make_shared<Dwarf> ();
    }
    else if (type == 'M'){
        e = make_shared<Merchant> ();
    }
    else if (type == 'D'){
        e = make_shared<Dragon> ();
    }
    else if (type == 'O'){
        e = make_shared<Orcs> ();
    }
    else if (type == 'L'){
        e = make_shared<Halfling> ();
    }
    else if (type == 'E'){
        e = make_shared<Elf> ();
    }
    return e;
}

concreteType::concreteType(const char& c):
    type{c} { }

void concreteType::setType(const char& c){
    type = c;
}

Enemy::Enemy(double hp, double atk, double def, int row, int col, char type, bool hostile):
    Character{hp, atk, def, row, col}, type{type}, isHostile{hostile} { }

char Enemy::getType(){
    return type;
}

bool Enemy::getHostile(){
    return isHostile;
}

void Enemy::setHostile(bool b){
    isHostile = b;
}


void Enemy::attackPlayer(Shade& shade){
    int def = shade.getDF();
    int atk = attack;
    int damage = ceil((100.0/(100+def))*atk);
    std::cout << "  The damage is: " << damage << std::endl;
    damage *= -1;
    shade.addHP(damage);
}


void Enemy::attackPlayer(Drow& drow){
    int def = drow.getDF();
    int atk = attack;
    int damage = ceil((100.0/(100+def))*atk);
    std::cout << "  The damage is: " << damage << std::endl;
    damage *= -1;
    drow.addHP(damage);
}

void Enemy::attackPlayer(Vampire& vampire){
    int def = vampire.getDF();
    int atk = attack;
    int damage = ceil((100.0/(100+def))*atk);
    std::cout << "  The damage is: " << damage << std::endl;
    damage *= -1;
    vampire.addHP(damage);
}

void Enemy::attackPlayer(Troll& troll){
    int def = troll.getDF();
    int atk = attack;
    int damage = ceil((100.0/(100+def))*atk);
    std::cout << "  The damage is: " << damage << std::endl;
    damage *= -1;
    troll.addHP(damage);
}

void Enemy::attackPlayer(Goblin& goblin){
    int def = goblin.getDF();
    int atk = attack;
    int damage = ceil((100.0/(100+def))*atk);
    std::cout << "  The damage is: " << damage << std::endl;
    damage *= -1;
    goblin.addHP(damage);
}


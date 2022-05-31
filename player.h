#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include "character.h"
#include "treasure.h"
#include "potion.h"


class Enemy;
class Gold;

class Player: public Character{
    protected:
    int floorID;
    int chamberID;
    int maxHP;
    int gold;
    bool alive;
    std::string type;
    
    std::vector<std::shared_ptr<Potion>> tempPotion;

    public:
    Player(double, double, double, int, int, int, int, int, std::string);
    virtual ~Player();
    virtual void accept(Enemy &) = 0;
    virtual void attackEnemy(std::shared_ptr <Enemy>) = 0;
    virtual void usePotion(std::shared_ptr<Potion>);
    void move(std::string);

    int getFloorID();
    int getChamberID();
    int getMaxHP();
    int getGold();
    std::string getType();
    bool getAlive();

    void setFloor(int);
    void setChamber(int);
    void setAlive(bool);
    void setType(std::string);

    void addGold(int);
    //add only temporary potion to tempPotion.
    void addPotion(std::shared_ptr<Potion>);
    virtual void removeTempPotion();
};

#endif

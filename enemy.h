#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <iostream>
#include <vector>
#include <memory>
#include "character.h"
#include "potion.h"
#include "player.h"
#include "player/shade.h"
#include "player/drow.h"
#include "player/vampire.h"
#include "player/troll.h"
#include "player/goblin.h"
#include "treasure/dHoard.h"

// #include "enemy/dwarf.h"

class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;

class Enemy : public Character{
    protected:
    char type;
    bool isHostile;
    Enemy(double, double, double, int, int, char, bool);
    public:
    char getType();
    bool getHostile();
    void setHostile(bool);
    virtual void attackPlayer(Shade &);
    virtual void attackPlayer(Drow &);
    virtual void attackPlayer(Vampire &);
    virtual void attackPlayer(Troll &);
    virtual void attackPlayer(Goblin &);
};

class Type{
    public:
    virtual std::shared_ptr<Enemy> getEnemy() = 0;
    virtual ~Type() { }
    virtual void setType(const char &) = 0;
};

class concreteType: public Type{
    char type;
    public:
    std::shared_ptr<Enemy> getEnemy() override;
    concreteType(const char&);
    void setType(const char&) override;
};


#endif

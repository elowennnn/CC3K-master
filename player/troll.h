#ifndef _TROLL_h_
#define _TROLL_h_

#include "../player.h"
#include "../enemy.h"

class Enemy;

class Troll: public Player{
    public:
    Troll();
    void accept(Enemy &) override;
    void attackEnemy(std::shared_ptr <Enemy>) override;
};

#endif

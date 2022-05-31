#ifndef _GOBLIN_h_
#define _GOBLIN_h_

#include "../player.h"
#include "../enemy.h"

class Enemy;

class Goblin: public Player{
    public:
    Goblin();
    void accept(Enemy &) override;
    void attackEnemy(std::shared_ptr <Enemy>) override;
};

#endif

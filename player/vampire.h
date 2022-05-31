#ifndef _VAMPIRE_h_
#define _VAMPIRE_h_

#include "../player.h"
#include "../enemy.h"

class Enemy;

class Vampire: public Player{
    public:
    Vampire();
    void accept(Enemy &) override;
    void attackEnemy(std::shared_ptr <Enemy>) override;
};

#endif

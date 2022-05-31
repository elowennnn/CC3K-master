#ifndef _DROW_h_
#define _DROW_h_

#include "../player.h"
#include "../enemy.h"

class Enemy;

class Drow: public Player{
    public:
    Drow();
    void accept(Enemy &) override;
    void attackEnemy(std::shared_ptr <Enemy>) override;
    void usePotion(std::shared_ptr<Potion>) override;
    void removeTempPotion() override;
};

#endif

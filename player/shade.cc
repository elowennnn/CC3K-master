#include "shade.h"
#include <cstdlib>
#include <cmath>
#include <time.h>


Shade::Shade(): 
    Player{125,25,25,0,0,0,0,125,"Shade"} { }

void Shade::accept(Enemy& enemy){
    if (enemy.getType() == 'E'){ // elf get two attacks against Shade
        std::srand(time(NULL));
        int i = rand() % 2;
        if (i == 0){
            std::cout << enemy.getType() << " attacks you:" << std::endl;
            enemy.attackPlayer(*this);
        }
        else{
            std::cout << enemy.getType() << " misses attack" << std::endl;
        }
    }
    std::srand(time(NULL));
    int i = rand() % 2;
    if (i == 0){
        std::cout << enemy.getType() << " attacks you:" << std::endl;
        enemy.attackPlayer(*this);
    }
    else{
        std::cout << enemy.getType() << " misses attack" << std::endl;
    }
}

void Shade::attackEnemy(std::shared_ptr <Enemy> enemy){
    if (enemy->getType() == 'L'){
        std::srand(time(NULL));
        int i = rand() % 2;
        if (i == 0){
            std::cout << "You misse attack to Halfling" << std::endl;
            return;
        }
    }
    int def = enemy->getDF();
    int atk = attack;
    int damage = ceil((100.0/(100+def))*atk);
    std::cout << "You attack enemy " << enemy->getType() << ":" << std::endl;
    std::cout << "  The damage is " << damage << std::endl;
    damage *= -1;
    enemy->addHP(damage);
    std::cout << "  Enemy's health now is: " << enemy->getHP() << std::endl;
}

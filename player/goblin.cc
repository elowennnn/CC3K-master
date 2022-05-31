#include "goblin.h"
#include <cstdlib>
#include <cmath>
#include <time.h>


Goblin::Goblin(): 
    Player{110,15,20,0,0,0,0,110,"Goblin"} { }

void Goblin::accept(Enemy& enemy){
    if (enemy.getType() == 'E'){ // elf get two attacks against Goblin
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

void Goblin::attackEnemy(std::shared_ptr <Enemy> enemy){
    int def = enemy->getDF();
    int atk = attack;
    int damage = ceil((100.0/(100+def))*atk);
    if (enemy->getType() == 'L'){
        std::srand(time(NULL));
        int i = rand() % 2;
        if (i == 0){
            std::cout << "You miss attack to Halfling" << std::endl;
            return;
        }
    }
    std::cout << "You attack enemy " << enemy->getType() << ":" << std::endl;
    std::cout << "  The damage is " << damage << std::endl;
    damage *= -1;
    enemy->addHP(damage);
    std::cout << "  Enemy's health now is: " << enemy->getHP() << std::endl;
    if (enemy->getHP() <= 0){
        gold += 5; 
        std::cout << "  Enemy is dead, you steal 5 gold "<< std::endl;
    }
}

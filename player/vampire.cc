#include "vampire.h"
#include <cstdlib>
#include <cmath>
#include <time.h>


Vampire::Vampire(): 
    Player{50,25,25,0,0,0,0,10000,"Vampire"} { }

void Vampire::accept(Enemy& enemy){
    if (enemy.getType() == 'E'){ // elf get two attacks against Vampire
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

void Vampire::attackEnemy(std::shared_ptr <Enemy> enemy){
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
    if(enemy->getType()=='W'){
        health -= 5;
        std::cout << "  You lost 5 HP"<< std::endl;
    }else{
        health += 5; 
        std::cout << "  You gain 5 HP"<< std::endl;
    }
}

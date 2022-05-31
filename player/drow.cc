#include "drow.h"
#include <cstdlib>
#include <cmath>
#include <stdlib.h>
#include <time.h>


Drow::Drow(): 
    Player{150,25,15,0,0,0,0,150,"Drow"} { }

void Drow::accept(Enemy& enemy){
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

void Drow::attackEnemy(std::shared_ptr <Enemy> enemy){
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

void Drow::usePotion(std::shared_ptr<Potion> potion){
    int type = potion->getType();
    if (type == 0){
        if (health+15 >= maxHP){
            health = maxHP;
        }
        else{
            health += 15;
        }
    }
    else if (type == 1){
        attack += 7.5;
    }
    else if (type == 2){
        defense += 7.5;
    }
    else if (type == 3){
        if (health-15 <= 0){
            health = 0;
            alive = false;
        }
        else{
            health -= 15;
        }
    }
    else if (type == 4){
        if (attack-7.5 <= 0){
            attack = 0;
            alive = false;
        }
        else{
            attack -= 7.5;
        }
    }
    else if (type == 5){
        if (defense-7.5 <= 0){
            defense = 0;
            alive = false;
        }
        else{
            defense -= 7.5;
        }
    }
}

void Drow::removeTempPotion(){
    if (tempPotion.empty()){
        return;
    }
    int size = tempPotion.size();
    for(int i = 0; i < size; i++){
        if (tempPotion[i]->getType() == 1){
            if (attack-7.5 <= 0){
                attack = 0;
                alive = false;
                break;
            }
            else{ attack -= 7.5; }
        }
        else if (tempPotion[i]->getType() == 2){
            if (defense-7.5 <= 0){
                defense = 0;
                alive = false;
                break;
            }
            else{ defense -= 7.5; }
        }
        else if (tempPotion[i]->getType() == 4){
            attack += 7.5;
        }
        else if (tempPotion[i]->getType() == 5){
            defense += 7.5;
        }
    }
    tempPotion.clear();
}

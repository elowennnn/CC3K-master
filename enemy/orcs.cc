#include "orcs.h"
#include <cmath>

Orcs::Orcs(): 
    Enemy{180,30,25,0,0,'O',true} { }


void Orcs::attackPlayer(Goblin & goblin){
    int def = goblin.getDF();
    int atk = attack;
    double damage = ceil((100.0/(100+def))*atk);
    damage *= 1.5;
    std::cout << "  The damage is: " << damage << std::endl;
    damage *= -1;
    goblin.addHP(damage);
}

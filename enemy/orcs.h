
#ifndef _ORCS_h_
#define _ORCS_h_

#include "../enemy.h"

class Orcs: public Enemy{
    friend class concreteLevel;
    public:
    Orcs();
    void attackPlayer(Goblin &) override;
};

#endif

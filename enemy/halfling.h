#ifndef _HALFLING_h_
#define _HALFLING_h_

#include "../enemy.h"

class Halfling: public Enemy{
    friend class concreteType;
    public:
    Halfling(): Enemy{100,15,20,0,0,'L',true} { }
};

#endif

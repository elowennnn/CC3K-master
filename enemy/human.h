#ifndef _HUMAN_h_
#define _HUMAN_h_

#include "../enemy.h"

class Human: public Enemy{
    friend class concreteType;
    public:
    Human(): Enemy{140,20,20,0,0,'H',true} { }
};

#endif

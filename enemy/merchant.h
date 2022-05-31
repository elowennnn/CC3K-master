#ifndef _MERCHANT_h_
#define _MERCHANT_h_

#include "../enemy.h"

class Merchant: public Enemy{
    friend class concreteType;
    public:
    Merchant(): Enemy{30,70,5,0,0,'M',false} { }
};

#endif

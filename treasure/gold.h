#ifndef _GOLD_h_
#define _GOLD_h_

#include "../treasure.h"

class Gold: public Treasure{
    public:
    Gold(): Treasure{0, 0, 2, true, 6} { }
};

#endif

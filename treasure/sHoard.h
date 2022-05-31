#ifndef _SHOARD_h_
#define _SHOARD_h_

#include "../treasure.h"

class Shoard: public Treasure{
    public:
    Shoard(): Treasure{0, 0, 1, true, 7} { }
};

#endif


#ifndef _MHOARD_h_
#define _MHOARD_h_

#include "../treasure.h"

class Mhoard: public Treasure{
    public:
    Mhoard(): Treasure{0, 0, 4, true, 8} { }
};


#endif

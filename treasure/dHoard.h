#ifndef _DHOARD_h_
#define _DHOARD_h_

#include "../treasure.h"

class Dhoard: public Treasure{
    public:
    Dhoard(): Treasure{0, 0, 6, false, 9} { }
};


#endif

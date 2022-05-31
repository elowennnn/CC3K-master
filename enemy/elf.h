#ifndef _ELF_h_
#define _ELF_h_

#include "../enemy.h"

class Elf: public Enemy{
    friend class concreteType;
    public:
    Elf(): Enemy{140,30,10,0,0,'E',true} { }
};

#endif

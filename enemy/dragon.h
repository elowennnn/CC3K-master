#ifndef _DRAGON_h_
#define _DRAGON_h_

#include "../enemy.h"
#include "../treasure/dHoard.h"

class Dragon: public Enemy{
    friend class concretType;
    std::shared_ptr<Dhoard> dhoard;
    public:
    Dragon(): Enemy{150,20,20,0,0,'D',true} { }
    void setDhoard(std::shared_ptr<Dhoard> d) { dhoard = d; }
    std::shared_ptr<Dhoard> getDhoard() { return dhoard; }
};

#endif

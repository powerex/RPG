#ifndef RPG_HEALER_H
#define RPG_HEALER_H


#include "Hero.h"

class Healer: public Hero {

public:
    Healer(char *name);
    Healer(Team *pTeam);
    ~Healer();
};


#endif //RPG_HEALER_H

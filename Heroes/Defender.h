#ifndef RPG_DEFENDER_H
#define RPG_DEFENDER_H

#include "Hero.h"

class Defender: public Hero {

public:
    Defender(char *name);
    Defender(Team *pTeam);
    ~Defender();
};


#endif //RPG_DEFENDER_H

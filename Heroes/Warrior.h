#ifndef RPG_WARRIOR_H
#define RPG_WARRIOR_H

#include "Hero.h"

class Warrior: public Hero {

public:
    Warrior(char *name);
    Warrior(Team *pTeam);
    void specialHit();
    ~Warrior();
};


#endif //RPG_WARRIOR_H

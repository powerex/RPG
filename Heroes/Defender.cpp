//
// Created by Администратор on 26.11.2016.
//

#include "Defender.h"
#include "../Team.h"

Defender::Defender(char *name) : Hero(name) {
    ut = DEF;
    HP += 2;
}

Defender::Defender(Team *pTeam) : Hero(pTeam) {
    ut = DEF;
    HP += 2;
}

Defender::~Defender() {}

void Defender::specialHit() {
    if (fury > 100) {
        fury = 0;
//        std::cout << name << " -> " << myGroup->getName() << " defense +2\n";
        for (int i=0; i < Settings::TEAM; i++) {
            if (myTeam->getUnit(i) != nullptr && myTeam->getUnit(i)->isAlive())
                myTeam->getUnit(i)->setDef(2);
        }
    }
}

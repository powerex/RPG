#include "Healer.h"
#include "../Team.h"

Healer::Healer(char *name) : Hero(name) {
    ut = HEAL;
}

Healer::~Healer() {}

Healer::Healer(Team *pTeam) : Hero(pTeam) {

}

void Healer::specialHit() {
    if (fury > 100) {
        fury = 0;
        double dam = baseDamage();
//        std::cout << name << " -> " << myGroup->getName() << " " << dam << " of healing\n";
        for (int i=0; i<Settings::TEAM; i++) {
            if (myTeam->getUnit(i) != nullptr && myTeam->getUnit(i)->isAlive())
                myTeam->getUnit(i)->changeCurrentHP(dam);
        }
    }
}

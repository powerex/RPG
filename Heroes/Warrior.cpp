//
// Created by Администратор on 26.11.2016.
//

#include "Warrior.h"
#include "../Team.h"

Warrior::Warrior(char *name): Hero(name) {
    ut = WAR;
    damage ++;
}

Warrior::Warrior(Team *pTeam) : Hero(pTeam) {
    ut = WAR;
    damage ++;
}

Warrior::~Warrior() {}

void Warrior::specialHit() {
    if (fury > 100) {
        fury = 0;
        double dam = baseDamage();
//        std::cout << name << " -> " << myGroup->getEnemy()->getName() << " " << dam << " of damage\n";
        Team* t = myTeam->getEnemy();
        for (int i=0; i<Settings::TEAM; i++) {
            if (t->getUnit(i) != nullptr && t->getUnit(i)->isAlive())
                t->getUnit(i)->changeCurrentHP(-dam/3.0);
        }
    }
}

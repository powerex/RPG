//
// Created by Администратор on 26.11.2016.
//

#include "Warrior.h"

Warrior::Warrior(char *name): Hero(name) {
    ut = WAR;
    damage ++;
}

Warrior::Warrior(Team *pTeam) : Hero(pTeam) {
    ut = WAR;
    damage ++;
}

Warrior::~Warrior() {}
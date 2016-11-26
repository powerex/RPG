//
// Created by Администратор on 26.11.2016.
//

#include "Defender.h"

Defender::Defender(char *name) : Hero(name) {
    ut = DEF;
    HP += 2;
}

Defender::Defender(Team *pTeam) : Hero(pTeam) {
    ut = DEF;
    HP += 2;
}

Defender::~Defender() {}
//
// Created by Администратор on 26.11.2016.
//

#include "Healer.h"

Healer::Healer(char *name) : Hero(name) {
    ut = HEAL;
}

Healer::~Healer() {}

Healer::Healer(Team *pTeam) : Hero(pTeam) {

}

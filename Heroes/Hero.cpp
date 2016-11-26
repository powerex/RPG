#include <cstdlib>
#include <cstring>
#include <iostream>
#include "Hero.h"

using namespace std;

UnitType Hero::getUT() const {
    return this->ut;
}

Hero::Hero(char *name) {
    int diff = rand()%31 - 15;
    HP = 100 + diff;
    damage = 30 - diff/3;
    level = 1;
    furyIncrement = 50;
    memcpy(this->name, name, 25);
}

Hero::~Hero() {}

void Hero::setGroup(Team *myTeam) {
    this->myTeam = myTeam;
}

void Hero::showInfo() {
    switch (ut) {
        case WAR: cout << (char)23; break;
        case DEF: cout << (char)15; break;
        case HEAL: cout << '+'; break;
        default: cout << '?';
    }
    cout << name << endl;
    cout << "Level: " << level << endl;
    cout << "HP: " << HP << endl;
    cout << "Damage: " << damage << endl;
}

Hero::Hero(Team *pTeam): myTeam(pTeam) {
    int diff = rand()%21 - 15;
    HP = 100 + diff;
    damage = 20 - diff/2;
    level = 1;
    furyIncrement = 20;
}

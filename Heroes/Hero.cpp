#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
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

ll Hero::getHP() {
    return this->HP;
}

void Hero::incHP() {
    this->HP++;
}

ll Hero::getDamage() {
    return this->damage;
}

void Hero::incDamage() {
    this->damage++;
}

ll Hero::getLevel() {
    return this->level;
}

void Hero::incLevel() {
    this->level++;
}

bool Hero::isAlive() {
    return this->currentHP>0.00000;
}

void Hero::show() {
    switch (ut) {
        case WAR: cout << (char)23; break;
        case DEF: cout << (char)15; break;
        case HEAL: cout << '+'; break;
        default: cout << '?';
    }
    cout << " " << name << endl;
    cout << (char)3 << setw(3) << getHPinPercent() << "% " << HPtoString(getHPinPercent()) << endl;
    cout << "Fury: " << fury << endl;
}

short Hero::getHPinPercent() {
    return (short)(100 * this->currentHP / this->HP);
}

std::string Hero::HPtoString(short hp) {
    string s="";
    int i=0;
    while (hp > 4) {
        s = s + (char)219;
        hp -= 4;
        i++;
    }
    switch (hp) {
        case 3: s = s + (char)178; break;
        case 2: s = s + (char)177; break;
        case 1: s = s + (char)176; break;
        default: break;
    }
    i++;
    for (;i<25;i++) s = s + " ";//(char)249;
    return s;
}

void Hero::showShort() {
    switch (ut) {
        case WAR: cout << (char)23; break;
        case DEF: cout << (char)15; break;
        case HEAL: cout << '+'; break;
        default: cout << '?';
    }
    cout << HPtoString(getHPinPercent());
}

void Hero::setDef(int def) {
    this->defence+=def;
    if (defence < 0) defence = 0;
}

void Hero::increaseFury() {
    this->fury += furyIncrement;
}

void Hero::prepareToFight() {
    defence = 0;
    currentHP = HP;
    fury = 0;
}

double Hero::baseDamage() {
    double k = (rand()%500)/1000.0 + 0.60000;
    return k*damage*(1.0 + level/10.0);
}

void Hero::changeCurrentHP(double d) {
    if (d < 0 && defence > 0) {
        d /= 2;
        defence--;
    }
    this->currentHP += d;
    if (currentHP > HP) currentHP = HP;
    if (currentHP < 0.0) currentHP = 0.0;
    fury += 1;
}

int Hero::getFury() {
    return this->fury;
}
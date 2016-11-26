#ifndef RPG_HERO_H
#define RPG_HERO_H

#include "../Settings.h"

class Team;

class Hero {
public:
    Hero(char *name);
    Hero(Team *pTeam);

    UnitType getUT() const;
    virtual ~Hero();

    void setGroup(Team *myTeam);

    void showInfo();

protected:
    char name[Settings::NAME_LENGTH];
    UnitType ut;
    Team* myTeam;
    long long HP;
    double currentHP;
    int level;
    long long damage;
    int fury;
    int furyIncrement;
    double critChanse;
    int defence;
};

#endif //RPG_HERO_H

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

    ll getHP();

    void incHP();

    ll getDamage();

    void incDamage();

    ll getLevel();

    void incLevel();

    bool isAlive();

    void show();

    short getHPinPercent();

    void showShort();

    void setDef(int def);

    void increaseFury();

    void prepareToFight();

    double baseDamage();

    void changeCurrentHP(double d);

    int getFury();

    virtual void specialHit() = 0;

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
private:
    std::string HPtoString(short hp);
};

#endif //RPG_HERO_H

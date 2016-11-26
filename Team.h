#ifndef RPG_TEAM_H
#define RPG_TEAM_H

#include <iostream>
#include <string>
#include "Settings.h"
#include "Heroes/Hero.h"

class Team {
public:
    Team();
    Team(char *name, Hero *unit1, Hero *unit2, Hero *unit3);
    ~Team();
    const char *getName() const;
    bool saveTeam();

    void setEnemy(Team *pTeam);

    void showDetail();

    static Team* loadTeam(char *team);


    void setExp(long long int exp);
    void setStartPoint(long long int startPoint);
    void setName(char*);
    void setHero(Hero* pHero, size_t pos);
private:
    long long exp;
    char name[Settings::NAME_LENGTH];
    Hero* units[Settings::TEAM];
    Team* enemy;
    long long startPoint;
    //bool isFirst();
    //void startRound(int n);
    //void startFight();
};


#endif //RPG_TEAM_H

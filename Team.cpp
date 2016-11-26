#include "Team.h"
#include "Heroes/Defender.h"
#include "Heroes/Warrior.h"
#include "Heroes/Healer.h"
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

bool Team::saveTeam() {
    string s = name;
    s = s + ".dat";
    ofstream ofs(s, ios::binary | ios::out);

    ofs.write((char*)&exp, sizeof(exp));
    ofs.write(reinterpret_cast<char *>(name), Settings::NAME_LENGTH);
    ofs.write(reinterpret_cast<char *>(&startPoint), sizeof(startPoint));
    for (auto i = 0; i < Settings::TEAM; i++) {
        UnitType ut = units[i]->getUT();
        ofs.write(reinterpret_cast<char *>(&ut), sizeof(UnitType));
        int size = 0;
        switch (ut) {
            case DEF: size = sizeof(Defender); break;
            case WAR: size = sizeof(Warrior); break;
            case HEAL: size = sizeof(Healer); break;
            default: size = 0;
        }
        ofs.write(reinterpret_cast<char *>(units[i]), size);
    }
    ofs.close();
    return true;
}

Team* Team::loadTeam(char *team) {
    string s = team;
    s = s + ".dat";
    Team *t = new Team();
    ifstream ifs;
    ifs.open(s, ios::in | ios::binary);
    if (ifs.is_open()) {

         long long t_exp;
         ifs.read((char*)&t_exp, sizeof(t_exp));
         t->setExp(t_exp);

        char t_name[Settings::NAME_LENGTH];
        ifs.read(reinterpret_cast<char *>(t_name), Settings::NAME_LENGTH);
        t->setName(t_name);

        ifs.read(reinterpret_cast<char *>(&t_exp), sizeof(startPoint));
        t->setStartPoint(t_exp);

        UnitType ut;
        size_t size;
        Hero *t_hero;
        for (auto i = 0; i < Settings::TEAM; i++) {
            ifs.read(reinterpret_cast<char *>(&ut), sizeof(UnitType));
            switch (ut) {
                case WAR:
                    t_hero = new Warrior(t);
                    size = sizeof(Warrior);
                    break;
                case DEF:
                    t_hero = new Defender(t);
                    size = sizeof(Defender);
                    break;
                case HEAL:
                    t_hero = new Healer(t);
                    size = sizeof(Healer);
                    break;
                default:
                    cout << "\nUnknown type in file\n";
                    return nullptr;
            }
            ifs.read(reinterpret_cast<char *>(t_hero), size);
            t->setHero(t_hero, i);
        }
        t->enemy = nullptr;
        ifs.close();
        return t;
    } else {
        cout << "Unable to open file";
        return nullptr;
    }

}

const char *Team::getName() const {
    return name;
}

Team::Team(char *name, Hero *unit1, Hero *unit2, Hero *unit3) {
    memcpy(this->name, name, 25);
    exp = 17;
    startPoint = 3;
    units[0] = unit1;
    units[1] = unit2;
    units[2] = unit3;
}

Team::~Team() {
    for (int i=0; i<Settings::TEAM; i++) {
        if (units[i] != nullptr)
            delete units[i];
    }
}

void Team::setEnemy(Team *pTeam) {
    this->enemy = pTeam;
}

void Team::showDetail() {
    cout << endl << name << endl;
    cout << "Retained experience: " << exp << endl;
    for (int i=0; i<Settings::TEAM; i++) {
        units[i]->showInfo();
        cout << endl;
    }
}

Team::Team() {

}

void Team::setExp(long long int exp) {
    Team::exp = exp;
}

void Team::setStartPoint(long long int startPoint) {
    Team::startPoint = startPoint;
}

void Team::setName(char *newName) {
    memcpy(this->name, newName, Settings::NAME_LENGTH);
}

void Team::setHero(Hero *pHero, size_t pos) {
    units[pos] = pHero;
}

Team *Team::getEnemy() {
    return this->enemy;
}

bool Team::incHP(Hero *u) {
    ll x = u->getHP();
    if (x <= exp) {
        u->incHP();
        exp -= x;
        return true;
    }
    return false;
}

bool Team::incDamage(Hero *u) {
    ll x = u->getDamage();
    if (3*x <= exp) {
        u->incDamage();
        exp -= 3*x;
        return true;
    }
    return false;
}

bool Team::incLevel(Hero *u) {
    ll x = u->getLevel();
    if (x*10 <= exp) {
        u->incLevel();
        exp -= 10*x;
        return true;
    }
    return false;
}

bool Team::isAlive() {
    for (int i=0; i<Settings::TEAM; i++) {
        if (units[i]->isAlive()) return true;
    }
    return false;
}

void Team::show() {
    cout << endl << name << endl;
    for (int i=0; i<Settings::TEAM; i++) {
        units[i]->show();
        cout << endl;
    }
}

void Team::showShort() {
    for (int i=0; i<Settings::TEAM; i++) {
        units[i]->showShort();
        cout << "\t\t\t";
        enemy->getUnit(i)->showShort();
        cout << endl;
    }

}

Hero *Team::getUnit(int k) {
    return units[k];
}

bool Team::fight() {
    startFight();
    int r = 1;
    while (isAlive() && enemy->isAlive()) {
        startRound(r++);
        /*
            update();
            show();
            enemy->show();
            cout << "========================================================";
         */
    }
    if (isAlive()) {
        exp += enemy->getLevel();
    }
    return true;
}

bool Team::isFirst() {
    if (enemy != nullptr && enemy->isAlive()) {
        ll t = startPoint + enemy->getStartPoint();
        ll x = rand()%t;
        return x < startPoint;
    }
    return true;
}

void Team::startRound(int n) {
//    cout << "\nROUND " << n << " starts" << endl;
    for (int i=0; i<Settings::TEAM; i++) {
        if (units[i] != nullptr && units[i]->isAlive()) {
            units[i]->setDef(-1);
            units[i]->increaseFury();
        }
        if (enemy != nullptr) {
            Hero* e = enemy->getUnit(i);
            if (e != nullptr && e->isAlive()) {
                e->setDef(-1);
                e->increaseFury();
            }
        }
    }

    if (isFirst()) {

        attackEnemy();
        enemy -> attackEnemy();
    } else {
        enemy -> attackEnemy();
        attackEnemy();
    }

//    cout << "ROUND " << n << " ends" << endl;
}

void Team::startFight() {
    for (int i=0; i<Settings::TEAM; i++) {
        if (units[i] != nullptr) {
            units[i]->prepareToFight();
        }
        if (enemy != nullptr) {
            Hero* e = enemy->getUnit(i);
            if (e != nullptr) {
                e->prepareToFight();
            }
        }
    }
}

long long int Team::getLevel() {
    ll l=0;
    for (int i=0; i<Settings::TEAM; i++)
        if (units[i] != nullptr) l += units[i]->getLevel();
    return l;
}

bool Team::incStartPoint() {
    if (exp > startPoint * 1000) {
        exp -= 1000*(startPoint++);
        return true;
    }
    return false;
}

long long Team::getStartPoint() {
    return this->startPoint;
}

void Team::attackEnemy() {
    if (isAlive() && enemy != nullptr && enemy->isAlive()) {
//        cout << "\n Team " << name << " attacks team " << enemy->getName() << endl;
        //
        for (int i=0; i<Settings::TEAM; i++) {
            if (enemy->isAlive() && units[i]->isAlive()) {
                int e = -1;
                do {
                    e = rand()%Settings::TEAM;
                } while (enemy->getUnit(e) == nullptr || !enemy->getUnit(e)->isAlive());

                double dd = units[i]->baseDamage();
                enemy->getUnit(e)->changeCurrentHP(-dd);

//                cout << units[i]->getName() << " -> " << enemy->getUnit(e)->getName() << " " << dd << " of damage\n";
//                showShort();
                //printHealth();
//                if (!enemy->getUnit(e)->isAlive()) cout << "                            "
//                                                        << enemy->getUnit(e)->getName() << " is died\n;";
                if (units[i]->getFury() > 100) {
                    units[i]->specialHit();
//                    showShort();
                    //printHealth();
                }
            }
        }
    }
}

std::string Team::getName() {
    return this->name;
}

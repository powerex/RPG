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



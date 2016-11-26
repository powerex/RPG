#ifndef RPG_SETTINGS_H
#define RPG_SETTINGS_H

#include <string>

typedef long long ll;

enum UnitType {NOOB, DEF, WAR, HEAL};

class Settings {
public:
    static const int TEAM = 3;
    static const int NAME_LENGTH = 25;
};

#endif //RPG_SETTINGS_H

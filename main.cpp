#include <iostream>
#include <ctime>
#include <fstream>
#include <cstring>

#include "Settings.h"
#include "Heroes/Warrior.h"
#include "Heroes/Defender.h"
#include "Heroes/Healer.h"
#include "Team.h"

using namespace std;

class st {
private:
    long long x;
    double y;
    char c[10];
public:
    st(): x(200), y(3.25) {
        memcpy(c, "hjkrt", 10);
    }
    void write() {
        ofstream out("file.dat", ios::binary | ios::out);
        out.write((char*)&x, sizeof(x));
        out.write((char*)&y, sizeof(double));
        out.write((char*)&c, 10);
        out.close();
    }
    void read() {
        ifstream in("file.dat", ios::binary | ios::in);
        if (in.is_open()) {
            in.read((char*)&x, sizeof(x));
            in.read((char*)&y, sizeof(y));
            in.read((char*)&c, 10);
        } else { cout << "No open"; }
    }
    void set(int _x, double _y, char _c[]) {
        x = _x;
        y = _y;
        memcpy(c, _c, 10);
    }
    void show() {
        cout << x << " " << y << " : " << c << endl;
    }
};

int main(int argc, char* argv[]) {
    srand(time(NULL));
//*
    Hero* u1 = new Warrior((char*)"myWarrior");
    Hero* u2 = new Defender((char*)"myDefender");
    Hero* u3 = new Healer((char*)"Healer");
    Team myG( (char *)"myTeam", u1, u2, u3);

    u1->setGroup(&myG);
    u2->setGroup(&myG);
    u3->setGroup(&myG);

    Hero* e1 = new Warrior((char*)"e-Warrior");
    Hero* e2 = new Defender((char*)"e-Defender");
    Hero* e3 = new Healer((char*)"e-Healer");
    Team eG( (char*)"enemyTeam", e1, e2, e3);
    e1->setGroup(&eG);
    e2->setGroup(&eG);
    e3->setGroup(&eG);

    myG.setEnemy(&eG);
    eG.setEnemy(&myG);

    myG.showDetail();
    myG.saveTeam();

    Team *newTeam = Team::loadTeam((char *) "myTeam");

    if (newTeam != NULL) newTeam->showDetail();
    else cout << "\nSomethingWrong!\n";
//*/


/*
    st* s = new st();
    s->write();
    s->set(4, 6.7, (char*)"sdf");
    s->show();
    s->read();
    s->show();
    delete s;
//*/


    return 0;
}
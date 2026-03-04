#include "graphics.hpp"
#include <fstream>
#include <iostream>

using namespace genv;
using namespace std;

const int XX = 800;
const int YY = 600;

struct Csirke {
    Csirke(string fajlnev) {
        ifstream befajl(fajlnev);

        if (!befajl.is_open()) {
            cerr << "Hiba: Nem talalhato a fajl: " << fajlnev << endl;
            kep_vaszon.open(1, 1);
            return;
        }

        befajl >> szel >> mag;

        // Memória-vászon megnyitása
        kep_vaszon.open(szel, mag);

        // BEOLVASÁS ÉS RAJZOLÁS CSAK EGYSZER TÖRTÉNIK!
        int r, g, b;
        for (int i = 0; i < mag; i++) {
            for (int j = 0; j < szel; j++) {
                befajl >> r >> g >> b;
                // A vászonra rajzolunk, nem a képernyőre
                kep_vaszon << move_to(j, i) << color(r, g, b) << dot;
            }
        }
        befajl.close();
    }

    void rajzol(int x, int y) {
        // INNEN TŰNT EL A DELAY!
        // Egyetlen lépésben rányomja a memóriában lévő képet az ablakra.
        gout << stamp(kep_vaszon, x, y);
    }

    int szelesseg() { return szel; }
    int magassag() { return mag; }

private:
    canvas kep_vaszon; // A hatalmas 3D vektor helyett egy vásznat tárolunk!
    int szel = 1;
    int mag = 1;
};

int main()
{
    Csirke csirke("a.kep");
    gout.open(XX, YY);
    event ev;

    int eger_x = XX / 2;
    int eger_y = YY / 2;

    gout << move_to(0, 0) << color(0, 0, 0) << box(XX, YY);
    csirke.rajzol(eger_x - csirke.szelesseg() / 2, eger_y - csirke.magassag() / 2);
    gout << refresh;

    while(gin >> ev && ev.keycode != key_escape)
    {
        if (ev.type == ev_mouse) {
            eger_x = ev.pos_x;
            eger_y = ev.pos_y;

            // Képernyő letörlése
            gout << move_to(0, 0) << color(0, 0, 0) << box(XX, YY);

            // Új pozíció kiszámolása (középre)
            int start_x = eger_x - csirke.szelesseg() / 2;
            int start_y = eger_y - csirke.magassag() / 2;

            // Villámgyors újra-kirajzolás pecsételéssel
            csirke.rajzol(start_x, start_y);

            gout << refresh;
        }
    }
    return 0;
}
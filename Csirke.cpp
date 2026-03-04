#include "graphics.hpp"
#include <vector>
#include <fstream>

using namespace genv;
using namespace std;

struct Csirke {
    Csirke(string fajlnev) {
        ifstream befajl(fajlnev);
        int szel, mag;

        befajl >> szel >> mag;

        v = vector<vector<vector<int>>>(mag, vector<vector<int>>(szel, vector<int> (3)));

        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j<v[i].size(); j++) {
                befajl >> v[i][j][0] >> v[i][j][1] >> v[i][j][2];
            }
        }

        befajl.close();
    }

    void rajzol() {

        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j<v[i].size(); j++) {
                gout << color(v[i][j][0],
                                v[i][j][1],
                                v[i][j][2])
                                << dot;
            }
        }
    }
    int szelesseg() {
        return v[0].size();
    }
    int magassag() {
        return v.size();
    }
private:
    vector<vector<vector<int>>> v;
};

int main()
{
    Csirke csirke("C:\\Users\\Balazs\\Desktop\\GKit_\\a.kep");

    gout.open(csirke.szelesseg(),csirke.magassag());

    csirke.rajzol();

    gout << refresh;
    event ev;
    while(gin >> ev)
    {
    }
    return 0;
}

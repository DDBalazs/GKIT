#include "graphics.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace genv;
using namespace std;

const int XX = 800;
const int YY = 600;

struct Pehely {
    float x, y;
    float sebesseg;
    int meret;
};

int main()
{
    srand(time(0));

    gout.open(XX, YY);

    vector<Pehely> pelyhek;
    for(int i = 0; i < 400; i++) {
        Pehely p;
        p.x = rand() % XX;
        p.y = rand() % YY;
        p.sebesseg = 1 + (rand() % 4);
        p.meret = 1 + (rand() % 3);
        pelyhek.push_back(p);
    }

    gin.timer(20);

    event ev;
    int eger_x = XX / 2;

    while(gin >> ev && ev.keycode != key_escape)
    {
        if (ev.type == ev_mouse) {
            eger_x = ev.pos_x;
        }

        if (ev.type == ev_timer) {

            gout << move_to(0, 0) << color(0, 0, 0) << box(XX, YY);

            float szel = (eger_x - XX / 2) / 50.0;

            for (int i = 0; i < pelyhek.size(); i++) {

                pelyhek[i].y += pelyhek[i].sebesseg;
                pelyhek[i].x += szel;

                if (pelyhek[i].y > YY) pelyhek[i].y = 0;

                if (pelyhek[i].x < 0) pelyhek[i].x += XX;
                if (pelyhek[i].x > XX) pelyhek[i].x -= XX;

                gout << move_to(pelyhek[i].x, pelyhek[i].y)
                     << color(255, 255, 255)
                     << box(pelyhek[i].meret, pelyhek[i].meret);
            }

            gout << refresh;
        }
    }
    return 0;
}
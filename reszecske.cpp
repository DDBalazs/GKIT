#include "graphics.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace genv;
using namespace std;

const int XX = 800;
const int YY = 600;
const int NUM_PARTICLES = 5000;

struct Reszecske {
    float x, y;
    float vx, vy;
    int r, g, b;
    float tomeg;
    float surlodas;
    int forgasirany;
};

float randFloat() {
    return (float)rand() / (float)RAND_MAX;
}

int main()
{
    srand(time(0));
    gout.open(XX, YY);
    gin.timer(20);

    vector<Reszecske> reszecskek(NUM_PARTICLES);

    for(int i = 0; i < NUM_PARTICLES; i++) {
        reszecskek[i].x = rand() % XX;
        reszecskek[i].y = rand() % YY;

        reszecskek[i].vx = (randFloat() * 2.0) - 1.0;
        reszecskek[i].vy = (randFloat() * 2.0) - 1.0;

        reszecskek[i].r = rand() % 156 + 100;
        reszecskek[i].g = rand() % 156 + 100;
        reszecskek[i].b = rand() % 156 + 100;

        reszecskek[i].tomeg = 0.5 + randFloat();
        reszecskek[i].surlodas = 0.92 + (randFloat() * 0.06);
        reszecskek[i].forgasirany = (rand() % 2 == 0) ? 1 : -1;
    }

    event ev;
    int eger_x = XX / 2;
    int eger_y = YY / 2;

    int kivalasztott_fazis = 0;
    int aktiv_fazis = 0;

    float aktualis_sugar = 0.0;
    float ido = 0.0; // ÚJ: Globális idő változó a hullámzáshoz

    while(gin >> ev && ev.keycode != key_escape)
    {
        if (ev.type == ev_key) {
            if (ev.keycode == '1') kivalasztott_fazis = 1;
            if (ev.keycode == '2') kivalasztott_fazis = 2;
            if (ev.keycode == '3') kivalasztott_fazis = 3;
            if (ev.keycode == '0') kivalasztott_fazis = 0;
        }

        if (ev.type == ev_mouse) {
            eger_x = ev.pos_x;
            eger_y = ev.pos_y;

            if (ev.button == btn_left) {
                aktiv_fazis = kivalasztott_fazis;
                if (aktiv_fazis == 3) {
                    aktualis_sugar = 0.0;
                }
            }

            if (ev.button == btn_right) {
                aktiv_fazis = 0;
                for(int i = 0; i < NUM_PARTICLES; i++) {
                    reszecskek[i].x = rand() % XX;
                    reszecskek[i].y = rand() % YY;
                    reszecskek[i].vx = (randFloat() * 2.0) - 1.0;
                    reszecskek[i].vy = (randFloat() * 2.0) - 1.0;
                }
            }
        }

        if (ev.type == ev_timer) {
            // ÚJ: Az idő múlása minden képkockánál
            ido += 0.05;

            // ÚJ: A csúszkáló "szellemkurzor" kiszámítása
            // Ez egy 20 pixeles sugarú, folyamatosan mozgó célpontot hoz létre az igazi egered körül.
            // A 0.7-es szorzó miatt nem tökéletes körben, hanem organikus nyolcas alakban hullámzik.
            float cel_x = eger_x + sin(ido) * 20.0;
            float cel_y = eger_y + cos(ido * 0.7) * 20.0;

            gout << move_to(0, 0) << color(0, 0, 0) << box(XX, YY);

            if (aktiv_fazis == 3) {
                if (aktualis_sugar < 70.0) {
                    aktualis_sugar += 0.5;
                }
            }

            for (int i = 0; i < NUM_PARTICLES; i++) {

                // 1-es fázis: Gyors Gravitáció
                if (aktiv_fazis == 1) {
                    // Itt már a cel_x és cel_y felé vonzzuk őket!
                    float dx = cel_x - reszecskek[i].x;
                    float dy = cel_y - reszecskek[i].y;

                    reszecskek[i].vx += dx * 0.002 * reszecskek[i].tomeg;
                    reszecskek[i].vy += dy * 0.002 * reszecskek[i].tomeg;

                    reszecskek[i].vx *= reszecskek[i].surlodas;
                    reszecskek[i].vy *= reszecskek[i].surlodas;
                }

                // 2-es fázis: Lassú, kurzoron áthaladó, sűrű örvény
                else if (aktiv_fazis == 2) {
                    float dx = cel_x - reszecskek[i].x;
                    float dy = cel_y - reszecskek[i].y;

                    float tx = -dy * reszecskek[i].forgasirany;
                    float ty =  dx * reszecskek[i].forgasirany;

                    // TELJESEN KIVETTÜK a taszító pajzsot!
                    // Kellemes, lassú vonzás és forgatás:
                    float befele_huzo_ero = 0.0015;
                    float forgato_ero = 0.0025;

                    reszecskek[i].vx += (dx * befele_huzo_ero + tx * forgato_ero) * reszecskek[i].tomeg;
                    reszecskek[i].vy += (dy * befele_huzo_ero + ty * forgato_ero) * reszecskek[i].tomeg;

                    // Egy icipicit lazítottunk a féken (0.90 helyett 0.92),
                    // így meglesz a lendületük ahhoz, hogy gyönyörűen átcsússzanak a kurzoron!
                    reszecskek[i].vx *= 0.92;
                    reszecskek[i].vy *= 0.92;
                }

                // 3-as fázis: Növekvő Stabil Gyűrű
                else if (aktiv_fazis == 3) {
                    float dx = cel_x - reszecskek[i].x;
                    float dy = cel_y - reszecskek[i].y;

                    float tavolsag = sqrt(dx * dx + dy * dy);
                    if (tavolsag == 0) tavolsag = 0.001;

                    float nx = dx / tavolsag;
                    float ny = dy / tavolsag;

                    float hiba = tavolsag - aktualis_sugar;
                    float rugo_ero = hiba * 0.005;

                    reszecskek[i].vx += nx * rugo_ero * reszecskek[i].tomeg;
                    reszecskek[i].vy += ny * rugo_ero * reszecskek[i].tomeg;

                    reszecskek[i].vx *= 0.90;
                    reszecskek[i].vy *= 0.90;
                }

                reszecskek[i].x += reszecskek[i].vx;
                reszecskek[i].y += reszecskek[i].vy;

                if (aktiv_fazis == 0) {
                    if (reszecskek[i].x < 0) reszecskek[i].x += XX;
                    if (reszecskek[i].x >= XX) reszecskek[i].x -= XX;
                    if (reszecskek[i].y < 0) reszecskek[i].y += YY;
                    if (reszecskek[i].y >= YY) reszecskek[i].y -= YY;
                }

                gout << move_to(reszecskek[i].x, reszecskek[i].y)
                     << color(reszecskek[i].r, reszecskek[i].g, reszecskek[i].b)
                     << dot;
            }

            gout << refresh;
        }
    }
    return 0;
}
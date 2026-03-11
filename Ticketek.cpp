#include "graphics.hpp"
#include<vector>

using namespace genv;
using namespace std;


const int width = 800;
const int heigth = 600;




struct cetli
{


    cetli(int x, int y, int sizex, int sizey): //konstruktor
        x(x),y(y),size_x(sizex),size_y(sizey),
        kivalasztas(false), wheeling(0)
    {
        hatar();
    }


    void draw()
    {
        if(kivalasztas)
        {
            gout << color(153,153,0) << move_to(x,y) << box(size_x,size_y) << color(153,0,76) << move_to(x+5, y+5) << box(size_x -10,size_y -10);
            gout << color(255,255,255) << move_to(x+(size_x / 2), y+(size_y/2)) << text(to_string(wheeling));
        }
        else
        {

            gout << color(255,153,153) << move_to(x,y) << box(size_x,size_y) << color(204,255,153) << move_to(x+5, y+5) << box(size_x -10,size_y -10);
            gout << color(0,0,0) << move_to(x+(size_x / 2), y+(size_y/2)) << text(to_string(wheeling));
        }

    }

    bool folotte(int mouse_x, int mouse_y)
    {
        return mouse_x >= x and mouse_x < x + size_x and mouse_y>= y and mouse_y < y + size_y;
    }

    void kijelol()
    {
        kivalasztas = true;
    }

    void elfelejt()
    {
        kivalasztas = false;
    }


    bool kijelolve()
    {
        return kivalasztas;
    }

    void mozog(int mouse_x, int mouse_y)
    {
        x = mouse_x - (size_x / 2);
        y = mouse_y - (size_y/ 2);

        hatar();
    }

    void novel()
    {
        if(kijelolve())
        {
            wheeling++;
        }
    }

    void csokkent()
    {

        if(kijelolve())
        {
            wheeling--;
        }
    }




private:

    int x,y,size_x,size_y;
    int dx,dy;
    bool kivalasztas;
    int wheeling;

    void hatar()
    {
        if(x > width - size_x)
        {
            x = width - size_x;
        }
        if(y > heigth - size_y)
        {
            y = heigth - size_y;
        }
        if(x < 0)
        {
            x = 0;
        }
        if(y < 0)
        {
            y = 0;
        }
    }
};



int main()
{
    gout.open(width,heigth);
    //int n = 20;
    bool lenyomva = false;

    cetli* elkapva = 0;

    vector<cetli*> cetlik;

    /*for (int i = 0; i < n; ++i)
    {
        cetlik.push_back(new cetli(rand() % width, rand() % heigth, rand() % 40 + 80, rand() % 30+50));

    } */


    gout << refresh;
    event ev;

    while(gin >> ev)
    {

        if(ev.type == ev_mouse)
        {

            if(ev.button == btn_left)
            {
                for(cetli *c: cetlik)
                {
                    c->elfelejt();
                }


                for(int i = cetlik.size()-1; i >= 0;i--)
                {

                    if(cetlik[i]->folotte(ev.pos_x, ev.pos_y))
                    {
                        elkapva = cetlik[i];



                        elkapva->kijelol();
                        break;

                    }
                }

                lenyomva = true;

            }
            else if(ev.button == 0) //eger mozgatas
            {

                if(lenyomva)
                {
                    for(cetli *c: cetlik)
                    {
                        if(c->kijelolve())
                        {
                            c->mozog(ev.pos_x,ev.pos_y);
                        }
                    }

                }
            }
            else if(ev.button == -btn_left)
            {
                lenyomva = false;
            }
            else if(ev.button == btn_right) // jobbklikkre hozzaad plusz post-iteket
            {
                int sz_x = rand() % 40 + 80;
                int sz_y = rand() % 30 + 50;
                cetlik.push_back(new cetli(ev.pos_x - sz_x / 2, ev.pos_y - sz_y / 2, sz_x, sz_y)); // uj hozzaadasa

            }
            else if(ev.button == btn_wheelup)
            {

                for(cetli *c: cetlik)
                {
                    if(c->kijelolve()) // ha igaz gorgessunk
                    {
                        c->novel();
                    }

                }

            }
            else if(ev.button == btn_wheeldown)
            {
                for(cetli *c: cetlik)
                {
                    if(c->kijelolve())
                    {
                        c->csokkent();
                    }

                }

            }

            gout << color(0,0,0) << move_to(0,0) << box(width,heigth);

            for(cetli *c: cetlik)
            {

                c->draw();
            }

            gout << refresh;
        }
    }

    return 0;
}
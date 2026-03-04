#include <iostream>
#include <cmath>

#include "graphics.hpp"

using namespace genv;
using namespace std;

void DrawParabolicCurvePart(int x, int y, int center_x, int center_y);

int main() {
    int width = 500;
    int height = 500;
    gout.open(width, height);

    event ev;
    while (gin >> ev) {
        int x_distance = ev.pos_x - width / 2;
        int y_distance = ev.pos_y - height / 2;

        gout << move_to(0, 0)
        << color(0, 0, 0)
        << box(width, height);

        for(int i = 0; i < 4; i++) {
            DrawParabolicCurvePart(x_distance, y_distance, width / 2, height / 2);
            int temp = x_distance;
            x_distance = -y_distance;
            y_distance = temp;
        }

        gout << refresh;
    }
}

void DrawParabolicCurvePart(int x, int y, int center_x, int center_y) {
    gout << move_to(x + center_x, y + center_y);

    float resolution = 10;
    for (int i = 0; i < resolution; i++) {
        gout << move_to(x - x / resolution * i + center_x, y - y / resolution * i + center_y)
        << color(255 / resolution * i, 0, 255 - 255 / resolution * i)
        << line_to(-y / resolution * i + center_x, x / resolution * i + center_y);
    }
}
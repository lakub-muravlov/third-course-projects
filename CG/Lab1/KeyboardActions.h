//
// Created by kub on 30/11/2020.
//

#ifndef LAB1_KEYBOARDACTIONS_H
#define LAB1_KEYBOARDACTIONS_H
#include <iostream>
#include <cstdio>
#include "Display.h"

using namespace std;

void key(unsigned char key, int x, int y) {
    if (key == 'w') {
        yr = yr + 2;
        xr = xr + 2;
//cout << yr << " " << xr << endl;
        glutPostRedisplay();
    }

    if (key == 's') {
        yr = yr - 2;
        xr = xr - 2;
//cout << yr << " " << xr << endl;
        glutPostRedisplay();
    }
    if (yr == 340) {
        yr = -340;
        xr = -340;
    }
    if (xr == -342) {
        yr = 338;
        xr = 338;
    }

}
#endif //LAB1_KEYBOARDACTIONS_H

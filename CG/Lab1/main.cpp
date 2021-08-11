#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
#include "Display.h"
#include "KeyboardActions.h"

using namespace std;

int main(int argc, char **argv) {
    cout << "use special key:" << endl << "push W to move up diagonaly in direction ofvector (0,1) and s to move down";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(600, 150);

    glutCreateWindow("Lab");

    glutDisplayFunc(display);

    glClearColor(1, 0.265, 0.265, 0);
    gluOrtho2D(0, 600, 0, 600);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);

    glutMainLoop();
    return 0;
}
//
// Created by kub on 30/11/2020.
//

#ifndef LAB1_DISPLAY_H
#define LAB1_DISPLAY_H
#include <GL/glut.h>

//GLOBAL VARS

//Initial window sizes
GLdouble width = 600, height = 600;
//Coordinates to control movement
float xr = 0, yr = 0;

//Array of Vertexes
double X[8] = {226, 250, 274, 304, 315, 321, 345, 374};
double Y[9] = {432, 403, 355, 295, 271, 262, 247, 218, 168};

//Function that draws rabbit
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);

//HEAD
    glBegin(GL_QUADS);
    glVertex2f(X[0] + xr, Y[1] + yr);
    glVertex2f(X[0] + xr, Y[2] + yr);
    glVertex2f(X[2] + xr, Y[2] + yr);
    glVertex2f(X[2] + xr, Y[1] + yr);
    glEnd();

//EAR
    glBegin(GL_POLYGON);
    glVertex2f(X[3] + xr, Y[0] + yr);
    glVertex2f(X[6] + xr, Y[0] + yr);
    glVertex2f(X[4] + xr, Y[1] + yr);
    glVertex2f(X[2] + xr, Y[1] + yr);
    glEnd();

//BODY
    glBegin(GL_POLYGON);
    glVertex2f(X[2] + xr, Y[2] + yr);
    glVertex2f(X[2] + xr, Y[5] + yr);
    glVertex2f(X[7] + xr, Y[8] + yr);
    glVertex2f(X[7] + xr, Y[5] + yr);
    glEnd();

//PAW
    glBegin(GL_TRIANGLES);
    glVertex2f(X[2] + xr, Y[3] + yr);
    glVertex2f(X[2] + xr, Y[6] + yr);
    glVertex2f(X[1] + xr, Y[4] + yr);
    glEnd();

//LEGS
    glBegin(GL_POLYGON);
    glVertex2f(X[7] + xr, Y[8] + yr);
    glVertex2f(X[5] + xr, Y[7] + yr);
    glVertex2f(X[2] + xr, Y[7] + yr);
    glVertex2f(X[2] + xr, Y[8] + yr);
    glEnd();
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}

//Function that controls image coordinates when reshaping
void reshape(GLint w, GLint h) {
    width = w;
    height = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
#endif //LAB1_DISPLAY_H

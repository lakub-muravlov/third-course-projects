#include <cmath>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <unistd.h>
#include <iostream>
#include <ctime>

using namespace std;

#define PI 3.14
int counter10ms=0;
float anglePlanet = 0.0;
GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat yellow[] = {0.7f, 0.2f, 0.0f, 1.0f};
GLfloat qAmb[] = {0.1, 0.1, 0.1, 1.0};
GLfloat qDif[] = {1.0, 1.0, 1.0, 1.0};
GLfloat qSpec[] = {.50, .50, .50, .10};
GLfloat qPos[] = {0, 0, 0, 0.1};
double ang = 2 * PI / 400;

GLdouble Width = 800, Height = 800;
double aspectRatio;
double varray[200][3];
double x = 0.5f, y = 0.5f, z;

typedef struct vector {
    double x;
    double y;
    double z;
} Vector;
Vector up = {0, 0, 1},
        cam = {0, -32, 38},
        eye = {0, 0, 0};

double module(Vector a) {
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

void norm(Vector *a) {
    double n = module(*a);
    a->x /= n;
    a->y /= n;
    a->z /= n;
}

Vector distract(Vector a, Vector b) {
    Vector res = {a.x - b.x, a.y - b.y, a.z - b.z};
    return res;
}

Vector sum(Vector a, Vector b) {
    Vector res = {a.x + b.x, a.y + b.y, a.z + b.z};
    return res;
}

Vector rotate(Vector axis, Vector a, double angle) {
    norm(&axis);
    Vector res;

    res.x = a.x * (cos(angle) + (1 - cos(angle)) * axis.x * axis.x) +
            a.y * ((1 - cos(angle)) * axis.x * axis.y - sin(angle) * axis.z) +
            a.z * ((1 - cos(angle)) * axis.x * axis.z + sin(angle) * axis.y);

    res.y = a.x * (sin(angle) * axis.z + (1 - cos(angle)) * axis.x * axis.y) +
            a.y * ((1 - cos(angle)) * axis.y * axis.y + cos(angle)) +
            a.z * ((1 - cos(angle)) * axis.y * axis.z - sin(angle) * axis.x);

    res.z = a.x * ((1 - cos(angle)) * axis.x * axis.z - sin(angle) * axis.y) +
            a.y * ((1 - cos(angle)) * axis.z * axis.y + sin(angle) * axis.x) +
            a.z * ((1 - cos(angle)) * axis.z * axis.z + cos(angle));

    return res;
}

void orbit() {
    glColor3f(1, 1, 1);
    glRotatef(45, 1.0, 0.0, 0.0);
    glScalef(0.85, 0.85, 0.85);
    glBegin(GL_POINTS);
    double ang1 = 0.0;
    for (int i = 0; i < 400; i++) {
        glVertex3f(47 * cos(ang1), 47 * sin(ang1), 0);
        ang1 += ang;
    }
    glEnd();
    glPopMatrix();

}

void initLighting(int a) {
    if(a%4000==1) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT7);
        glLightfv(GL_LIGHT7, GL_AMBIENT, qAmb);
        glLightfv(GL_LIGHT7, GL_DIFFUSE, qDif);
        glLightfv(GL_LIGHT7, GL_SPECULAR, qSpec);
    } else if(a%4000==2001){
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT7);
    }
}

void Display() {
    glClearColor(0.11, 0, 0.1, 0.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(cam.x, cam.y, cam.z, eye.x, eye.y, eye.z, up.x, up.y, up.z);

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix();
    glColor3f(1, 0.5, 0.0);
    glLightfv(GL_LIGHT7, GL_POSITION, qPos);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
    glTranslatef(0.0, 0.0, 0.0);
    glutSolidSphere(10, 50, 50);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    glPopMatrix();

    glPushMatrix();
    glRotatef(anglePlanet, 0.0, 1.0, -1.0);
    glTranslatef(-40.0, 0.0, 0.0);
    glColor3f(0.0, 0.2, 0.8);
    glutSolidSphere(4, 50, 50);
    glPopMatrix();
    orbit();
    glFinish();
}

void update() {
    counter10ms+=1;
    initLighting(counter10ms);
    anglePlanet += 0.8;
    if (anglePlanet > 360) {
        anglePlanet -= 360;
    }
    //cout<<counter10ms<<endl;
    usleep(10 * 1000);
    glutPostRedisplay();
}


void Reshape(GLint w, GLint h) {
    Width = w;
    Height = h;
    aspectRatio = w / h;

    glViewport(0, 0, Width, Height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-aspectRatio, aspectRatio, -1., 1., 1., 400.0);
}

Vector multiply(Vector a, Vector b) {
    Vector res = {a.y * b.z - a.z * b.y, b.x * a.z - a.x * b.z, a.x * b.y - a.y * b.x};
    return res;
}

void Keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            cam.y += 1.;
            eye.y += 1.;
            break;
        case 's':
            cam.y -= 1.;
            eye.y -= 1.;
            break;
        case 'a':
            cam.x -= 1.;
            eye.x -= 1.;
            break;
        case 'd':
            cam.x += 1.;
            eye.x += 1.;
            break;
        case '-':
            cam.z -= 1.;
            eye.z -= 1.;
            break;
        case '+':
            cam.z += 1.;
            eye.z += 1.;
            break;
    }

    glutPostRedisplay();
}

void Wheel(int wheel, int direction, int x, int y) {
    Vector vision = distract(cam, eye);
    if (direction > 0 && module(vision) > 5) { // Zoom in
        vision.x *= 0.9;
        vision.y *= 0.9;
        vision.z *= 0.9;
    }
    if (direction < 0) // Zoom out
    {
        vision.x /= 0.9;
        vision.y /= 0.9;
        vision.z /= 0.9;
    }
    cam = sum(eye, vision);

    glutPostRedisplay();
}

void Control(int key, int x, int y) {
    cam = distract(cam, eye);
    Vector n = multiply(up, cam);

    switch (key) {
        case GLUT_KEY_UP:
            cam = rotate(n, cam, -3.141527 / 180);
            up = rotate(n, up, -3.141527 / 180);
            //cout << cam.x << ' ' << cam.y << ' ' << cam.z << endl;
            break;
        case GLUT_KEY_DOWN:
            cam = rotate(n, cam, 3.141527 / 180);
            up = rotate(n, up, 3.141527 / 180);
            break;
        case GLUT_KEY_LEFT:
            cam = rotate(up, cam, -3.141527 / 180);
            break;
        case GLUT_KEY_RIGHT:
            cam = rotate(up, cam, 3.141527 / 180);
            break;
    }
    cam = sum(eye, cam);
    glutPostRedisplay();
}

// main loop
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("Lab3");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(Control);
    glutMouseWheelFunc(Wheel);
    glutIdleFunc(update);
    glutMainLoop();
    return 0;
}

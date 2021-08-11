#include <cmath>
#include <GL/freeglut.h>
#include <GL/glu.h>

GLdouble Width = 800, Height = 800;
double aspectRatio;
double varray[200][3];
double x = 0.5f, y = 0.5f, z;

typedef struct vector
{
    double x;
    double y;
    double z;
} Vector;
Vector up = {0, 0, 1},
        cam = {20, -20, 20},
        eye = {0, 0, 0};

double module(Vector a)
{
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

void norm(Vector *a)
{
    double n = module(*a);
    a->x /= n;
    a->y /= n;
    a->z /= n;
}

Vector distract(Vector a, Vector b)
{
    Vector res = {a.x - b.x, a.y - b.y, a.z - b.z};
    return res;
}

Vector sum(Vector a, Vector b)
{
    Vector res = {a.x + b.x, a.y + b.y, a.z + b.z};
    return res;
}

Vector rotate(Vector axis, Vector a, double angle)
{
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

void Display()
{
    glClearColor(1, 1, 1, 0.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(cam.x, cam.y, cam.z, eye.x, eye.y, eye.z, up.x, up.y, up.z);


    //
    for (int i = 0; i < 51; i++)
    {

        for (int k = 0; k < 60; k++)
        {
            if ((i + k) % 2)
                glColor4f(1, 0.94, 0, 0.7);
            else
                glColor4f(0, 1, 0.84, 0.7f);
            for (int j = 0; j < 5; j++)
            {
                x = 1.f * (i + (j % 2));
                y = 1.f * (k + (j / 2.0));
                z = sqrt(x)+sqrt(y);
                varray[j][0] = x;
                varray[j][1] = y;
                varray[j][2] = z;
            }
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_DOUBLE, 0, varray);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDisableClientState(GL_VERTEX_ARRAY);
        }
    }

    glPushMatrix();
    glColor3ub(0, 255, 255);
    glTranslatef(-20.0f, 20.0f, 0.0f);
    glScalef(5.f, 5.f, 5.f);
    glutWireOctahedron();
    glPopMatrix();

    glPushMatrix();
    glColor3ub(0, 0, 0);
    glTranslatef(-20.0f, 20.0f, 0.0f);
    glScalef(5.f, 5.f, 5.f);
    glutSolidOctahedron();
    glPopMatrix();

    glPushMatrix();
    glColor4f(0.f, 0.f, 0.f, 0.f);
    glTranslatef(-20.0f, -20.0f, 0.0f);
    glScalef(10.f, 10.f, 10.f);
    glutWireDodecahedron();
    glPopMatrix();

    glFinish();
}

void Reshape(GLint w, GLint h)
{
    Width = w;
    Height = h;
    aspectRatio = w / h;

    glViewport(0, 0, Width, Height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-aspectRatio, aspectRatio, -1., 1., 1., 400.0);
}

Vector multiply(Vector a, Vector b)
{
    Vector res = {a.y * b.z - a.z * b.y, b.x * a.z - a.x * b.z, a.x * b.y - a.y * b.x};
    return res;
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
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
        case 'o':
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-20,20,-20,20,0,50);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(0,0,40,0,0,0,0,0,0);
            glRotatef(-30,1,0,0);
            break;
        case 'p':
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(140,(Width/Height),0.1,100);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glFrustum(-20,20,-20,20,0,50);
            gluLookAt(0,0,40,0,0,0,0,0,0);
            glRotatef(-30,1,0,0);
            break;
    }
    glClearColor(1., 1., 1., 1.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutPostRedisplay();
}

void Wheel(int wheel, int direction, int x, int y)
{
    Vector vision = distract(cam, eye);
    if (direction > 0 && module(vision) > 5)
    { // Zoom in
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
    glClearColor(1., 1., 1., 1.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutPostRedisplay();
}

void Control(int key, int x, int y)
{
    cam = distract(cam, eye);
    Vector n = multiply(up, cam);

    switch (key)
    {
        case GLUT_KEY_UP:
            cam = rotate(n, cam, -3.141527 / 180);
            up = rotate(n, up, -3.141527 / 180);
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
    glClearColor(1., 1., 1., 1.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutPostRedisplay();
}

// main loop
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("Lab2");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(Control);
    glutMouseWheelFunc(Wheel);

    glutMainLoop();
    return 0;
}

#include <iostream>
#include <cmath>

using namespace std;

double f(double x1, double x2) {
    return x1 * x1 + x2 * x2;
    //return 4*(x1-5)*(x1-5)+(x2-6)*(x2-6);
}

double func(double Xo[1][2], double X[1][2]) {
    double result;
    result = pow((pow((Xo[0][0] - X[0][0]), 2) + pow((Xo[0][1] - X[0][1]), 2)), 1 / 2.0);
    return result;
}

int main() {
    double E = 0.00000001, alfa = 3, beta = -0.5, del_1 = 0.001, del_2 = 0.001;
    int i, j, w1 = 0, w2 = 1;
    int s = 0, n = 2, N = 3, I[100];
    double L1, L2;

    double d1[1][2] = {1, 0};
    double d2[1][2] = {0, 1};
    double X[1][2] = {}, Y[1][2] = {}, Xz[1][2] = {}, Y1[1][2] = {}, Xo[1][2] = {};

    I[s] = 1;
    cout << "Starting coordinates:" << endl;           //Задать начальное Х0
    for (int i = 0; i < 1; i++)
        for (int j = 0; j < 2; j++)
            cin >> X[i][j];

    for (i = 0; i < 1; i++)                //Y1 = Xo
        for (j = 0; j < 2; j++)
            Y[i][j] = X[i][j];
    cout << Y[w1][w1] << " " << Y[w1][w2] << endl;

    Y1[w1][w1] = Y[w1][w1];
    Y1[w1][w2] = Y[w1][w2];

    Xo[w1][w1] = X[w1][w1];
    Xo[w1][w2] = X[w1][w2];      //cout <<Xo[w1][w1]<<" "<<Xo[w1][w2]<<endl;
//.2..............a...................
    TWO:
    if (I[s] == 1) {
        cout << "I =" << I[s] << endl;  //первый случай
        if (f(Y[w1][w1] + del_1 * d1[w1][w1], Y[w1][w2] + del_1 * d1[w1][w2]) <
            f(Y[w1][w1], Y[w1][w2])) {
            cout << " - 2 - " << endl;
            cout << "Shag ydachnui" << endl;
            cout << " f(Y + del_1*d_1)=" << f(Y[w1][w1] + del_1 * d1[w1][w1], Y[w1][w2] + del_1 * d1[w1][w2])
                 << endl;
            cout << " f(Y)=" << f(Y[w1][w1], Y[w1][w2]) << endl;

            Y[w1][w1] = Y[w1][w1] + del_1 * d1[w1][w1];
            cout << "Y(" << Y[w1][w1] << ";";
            Y[w1][w2] = Y[w1][w2] + del_1 * d1[w1][w2];
            cout << Y[w1][w2] << ")" << endl;

            del_1 = alfa * del_1;
            cout << "del_1=" << del_1 << endl;
            goto THREE;   //перейти к шагу три
        }
        if (f(Y[w1][w1] + del_1 * d1[w1][w1], Y[w1][w2] + del_1 * d1[w1][w2]) >=
            f(Y[w1][w1], Y[w1][w2])) {
            cout << " - 2 - " << endl;
            cout << "Shag neydachnui" << endl;
            cout << " f(Y + del_1*d_1)=" << f(Y[w1][w1] + del_1 * d1[w1][w1], Y[w1][w2] + del_1 * d1[w1][w2])
                 << endl;
            cout << " f(Y)=" << f(Y[w1][w1], Y[w1][w2]) << endl;
            cout << "Y(" << Y[w1][w1] << ";" << Y[w1][w2] << ")" << endl;

            del_1 = beta * del_1;
            cout << "del_1=" << del_1 << endl;
            cout << "I[s] = " << I[s] << endl;
            goto THREE;   //перейти к шагу 3
        }
    }
//..............b....................
    if (I[s] == 2) {
        cout << "I =" << I[s] << endl;   //второй случай
        if (f(Y[w1][w1] + del_2 * d2[w1][w1], Y[w1][w2] + del_2 * d2[w1][w2]) <
            f(Y[w1][w1], Y[w1][w2])) {
            cout << " - 2 - " << endl;
            cout << "Shag ydachnui" << endl;
            cout << " f(Y + del_2*d_2)=" << f(Y[w1][w1] + del_2 * d2[w1][w1], Y[w1][w2] + del_2 * d2[w1][w2])
                 << endl;
            cout << " f(Y)" << f(Y[w1][w1], Y[w1][w2]) << endl;

            Y[w1][w1] = Y[w1][w1] + del_2 * d2[w1][w1];
            cout << Y[w1][w1] << " ";
            Y[w1][w2] = Y[w1][w2] + del_2 * d2[w1][w2];
            cout << Y[w1][w2] << endl;

            del_2 = alfa * del_2;
            cout << "del_2=" << del_2 << endl;
            goto THREE;   //перейти к шагу 3
        }
        if (f(Y[w1][w1] + del_2 * d2[w1][w1], Y[w1][w2] + del_2 * d2[w1][w2]) >=
            f(Y[w1][w1], Y[w1][w2])) {
            cout << " - 2 - " << endl;
            cout << "Shag neydachnui" << endl;
            cout << " f(Y + del_2*d_2)=" << f(Y[w1][w1] + del_2 * d2[w1][w1], Y[w1][w2] + del_2 * d2[w1][w2])
                 << endl;
            cout << " f(Y)" << f(Y[w1][w1], Y[w1][w2]) << endl;
            cout << "Y(" << Y[w1][w1] << ";" << Y[w1][w2] << ")" << endl;

            del_2 = beta * del_2;
            cout << "del_2=" << del_2 << endl;
            goto THREE;   //перейти к шагу три
        }
    }
//.3............a........................
    THREE:
    if (I[s] < n) {
        cout << " - 3 - " << endl;
        cout << " I < n " << endl;
        I[s] = I[s] + 1;
        goto TWO;
    }
//..............b........................
    if (I[s] = n) {
        cout << " - 3 - " << endl;
        cout << " I = n " << endl;
        if (f(Y[w1][w1], Y[w1][w2]) < f(Y1[w1][w1], Y1[w1][w2])) {
            cout << " f(Y) < f(Y1)" << endl;
            cout << "f(Y) " << f(Y[w1][w1], Y[w1][w2]) << endl;
            cout << "f(Y1) " << f(Y1[w1][w1], Y1[w1][w2]) << endl;

            Y1[w1][w1] = Y[w1][w1];
            cout << "Yn(" << Y1[w1][w1] << " ";
            Y1[w1][w2] = Y[w1][w2];
            cout << Y1[w1][w2] << ")" << endl;
            I[s] = 1;
            goto TWO;
        }
        if (f(Y[w1][w1], Y[w1][w2]) == f(Y1[w1][w1], Y1[w1][w2])) {
            cout << " f(Y) = f(Y1)" << endl;
            cout << "f(Y) " << f(Y[w1][w1], Y[w1][w2]) << endl;
            cout << "f(Y1) " << f(Y1[w1][w1], Y1[w1][w2]) << endl;

            if (f(Y1[w1][w1], Y1[w1][w2]) == f(X[w1][w1], X[w1][w2])) {
                cout << " f(Y1) == f(X)" << endl;
                Y1[w1][w1] = Y[w1][w1];
                cout << "Yn(" << Y1[w1][w1] << " ";
                Y1[w1][w2] = Y[w1][w2];
                cout << Y1[w1][w2] << ")" << endl;
                I[s] = 1;
                goto TWO;
            }
            if (f(Y[w1][w1], Y[w1][w2]) < f(X[w1][w1], X[w1][w2])) {
                cout << " f(Y) < f(X)" << endl;
                cout << "f(Y) " << f(Y[w1][w1], Y[w1][w2]) << endl;
                cout << "f(X) " << f(X[w1][w1], X[w1][w2]) << endl;
                goto Fourth;
            }
            if (f(Y[w1][w1], Y[w1][w2]) == f(X[w1][w1], X[w1][w2])) {
                cout << " f(Y) == f(X)" << endl;
                if (fabs(del_1) <= E && fabs(del_2) <= E) {
                    cout << " Del_1 && Del_2 <= E" << endl;
                    cout << " fabs(del_1)=" << fabs(del_1) << endl;
                    cout << " fabs(del_2)=" << fabs(del_2) << endl;

                    Xz[w1][w1] = X[w1][w1];
                    Xz[w1][w2] = X[w1][w2];
                }
                if (fabs(del_1) > E || fabs(del_2) > E) {
                    cout << "Del_1 || Del_2 <= E" << endl;
                    cout << " fabs(del_1)=" << fabs(del_1) << endl;
                    cout << " fabs(del_2)=" << fabs(del_2) << endl;

                    Y1[w1][w1] = Y[w1][w1];
                    cout << "Yn(" << Y1[w1][w1] << " ";
                    Y1[w1][w2] = Y[w1][w2];
                    cout << Y1[w1][w2] << ")" << endl;
                    I[s] = 1;
                    goto TWO;
                }

            }
        }
    }
//.4..............a.......................
    Fourth:
    Xo[w1][w1] = Y[w1][w1];
    cout << "Xo(" << Xo[w1][w1] << ";";
    Xo[w1][w2] = Y[w1][w2];
    cout << Xo[w1][w2] << ")" << endl;

    if (func(Xo, X) <= E) {
        Xz[w1][w1] = Xo[w1][w1];
        Xz[w1][w2] = Xo[w1][w2];
        cout << "(Xo - X) <= E" << endl;
        cout << "func(Xo,X) = " << func(Xo, X) << endl;

    }
    if (func(Xo, X) > E) {
        cout << "(Xo - X) > E" << endl;
        cout << "func(Xo,X) = " << func(Xo, X) << endl;

        L1 = Xo[w1][w1] - X[w1][w1];
        cout << "L1 = " << L1 << endl;
        L2 = Xo[w1][w2] - X[w1][w2];
        cout << "L2 = " << L2 << endl;

        double a1[w1][w2], a2[w1][w2];
        a1[w1][w1] = L1;
        a1[w1][w2] = L2;
        cout << "a1(" << a1[w1][w1] << ";" << a1[w1][w2] << ")" << endl;
        a2[w1][w1] = 0;
        a2[w1][w2] = L2;
        cout << "a2(" << a2[w1][w1] << ";" << a2[w1][w2] << ")" << endl;

        double b1[w1][w2], b2[w1][w2];
        b1[w1][w1] = a1[w1][w1];
        b1[w1][w2] = a1[w1][w2];
        cout << "b1(" << b1[w1][w1] << ";" << b1[w1][w2] << ")" << endl;

        double notD_1[w1][w2], notD_2[w1][w2];
        notD_1[w1][w1] = b1[w1][w1] / pow((pow((b1[0][0]), 2) + pow((b1[0][1]), 2)), 1 / 2.0);
        notD_1[w1][w2] = b1[w1][w2] / pow((pow((b1[0][0]), 2) + pow((b1[0][1]), 2)), 1 / 2.0);
        cout << "notD_1 (" << notD_1[w1][w1] << ";" << notD_1[w1][w2] << ")" << endl;

        b2[w1][w1] = a2[w1][w1] - (a2[w1][w1] * notD_1[w1][w1] + a2[w1][w2] * notD_1[w1][w2]) *
                                  notD_1[w1][w1];
        b2[w1][w2] = a2[w1][w2] - (a2[w1][w1] * notD_1[w1][w1] + a2[w1][w2] * notD_1[w1][w2]) *
                                  notD_1[w1][w2];
        cout << b2[w1][w2] << endl;
        cout << "b2(" << b2[w1][w1] << ";" << b2[w1][w2] << ")" << endl;

        notD_2[w1][w1] = b2[w1][w1] / pow((pow((b2[0][0]), 2) + pow((b2[0][1]), 2)), 1 / 2.0);
        notD_2[w1][w2] = b2[w1][w2] / pow((pow((b2[0][0]), 2) + pow((b2[0][1]), 2)), 1 / 2.0);
        cout << "notD_2 (" << notD_2[w1][w1] << ";" << notD_2[w1][w2] << ")" << endl;

        d1[w1][w1] = notD_1[w1][w1];
        cout << "d1(" << d1[w1][w1] << ";";
        d1[w1][w2] = notD_1[w1][w2];
        cout << d1[w1][w2] << ")" << endl;

        d2[w1][w1] = notD_2[w1][w1];
        cout << "d2(" << d2[w1][w1] << ";";
        d2[w1][w2] = notD_2[w1][w2];
        cout << d2[w1][w2] << ")" << endl;

        del_1 = 1;
        del_2 = 2;
        X[w1][w1] = Y[w1][w1];
        cout << "Xo(" << Xo[w1][w1] << ";";
        X[w1][w2] = Y[w1][w2];
        cout << Xo[w1][w2] << ")" << endl;
        I[s] = 1;
        goto TWO;
    }

    cout << "X* = " << Xz[w1][w1] << " " << Xz[w1][w2] << endl;
    cout << "f(X*) = " << f(Xz[w1][w1], Xz[w1][w2]) << endl;
    return 0;
}

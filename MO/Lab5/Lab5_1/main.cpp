#include <cmath>
#include <iostream>

using namespace std;

double f(double x) {
    return x * x - 8 * x + 7;
}

double grad_1x(double x, double h) {
    return (f(x + h) - f(x - h)) / (2.0 * h);
}


int main() {
    double x[10000], a = 0.01, eps = 0.0001;
    x[0] = 10;
    x[1] = x[0] - a * grad_1x(x[0], eps);
    int i = 1;
    while (abs(x[i] - x[i-1]) > eps) {
        cout << "i = " << i << " x[" << i << "] = " <<x[i]<<" x["<<i-1<<"] = "<<x[i-1]<<endl;
        x[i+1] = x[i] - a * grad_1x(x[i], eps);
        i++;
    }
    cout << "xmin = "<<x[i];
}
#include <iostream>
#include <cmath>

using namespace std;

double func(double x){
    return pow(x,2)-8*x+7;
}
int main() {
    int count=0;
    double a=1, b=7, eps=0.001, x_min;
    double l=b-a;
    double x1=a+0.382*l, x2=a+0.618*l;
    double f1=func(x1), f2=func(x2);
    cout<<"|It: "<<count<<"\t|x1 = "<<x1<<"\t|x2 = "<<x2<<"\t|f1 = "<<f1<<"\t|f2 = "<<f2<<"\t|L = "<<l<<endl;
    while((b-a)>eps){
        count++;
        if(f1>f2){
            a=x1; l=b-a;
            x1=x2; f1=f2;
            x2=a+0.618*l;
            f2=func(x2);
        }
        else{
            b=x2; l=b-a;
            x2=x1; f2=f1;
            x1=a+0.382*l;
            f1=func(x1);
        }
        cout<<"|It: "<<count<<"\t|x1 = "<<x1<<"\t|x2 = "<<x2<<"\t|f1 = "<<f1<<"\t|f2 = "<<f2<<"\t|L = "<<l<<endl;
    }
    x_min=(a+b)/2.0;
    cout<<x_min;
    return 0;
}

# include <iostream>
# include <iomanip>
# include <math.h>
# include <vector>
# include <stdlib.h>
# pragma GCC optimize("O2")
using namespace std;
double Bisekcja(double&, int&);
double Newton(double&, int&);
bool StopBisekcja(double, double, double, double, double);
bool StopNewton(double, double, int, unsigned int);
inline double f(double x) {return (pow(x, 3.0) - 71);};
inline double df(double x) {return (3.0 * pow(x, 2.0));};
int main () {
    unsigned int menu;
    bool exit = false;
    double x = 0.0, fx = 0.0;
    int iter = 0;
    while (!exit) {
        cout<<endl<<"Wybierz metode:"<<endl;
        cout<<"1 --> Meotda bisekcji [x^3 - 71 = 0 >> <4, 5>]"<<endl;
        cout<<"2 --> Meotda Newtona [x^3 - 71 = 0 >> x0 = 4]"<<endl;
        cout<<"Wyjscie z programu (3)"<<endl;
        cout<<"Wybor: ";
        cin>>menu;
        switch (menu) {
            case 1: {
                x = Bisekcja(fx, iter);
                cout<<fixed<<setprecision(15)<<endl<<"x = "<<x<<endl;
                cout<<fixed<<setprecision(15)<<"f(x) = "<<fx<<endl;
                cout<<fixed<<setprecision(0)<<"k = "<<iter<<endl;
                break;
            }
            case 2: {
                x = Newton(fx, iter);
                cout<<fixed<<setprecision(15)<<endl<<"x = "<<x<<endl;
                cout<<fixed<<setprecision(15)<<"f(x) = "<<fx<<endl;
                cout<<fixed<<setprecision(0)<<"k = "<<iter<<endl;
                break;
            }
            case 3: {
                exit = true;
                break;
            }
            default: {
                cout<<endl<<"Nieprawidlowy wybor!"<<endl;
                break;
            }
        }
    }
    cout<<"Do widzenia!"<<endl;
    cin.ignore();
    cin.get();
    return 0;
}
bool StopNewton(double fx, double eps, int k, unsigned int maxk) {
    if (fabs(fx) < eps) return true;
    if (k == maxk) return true;
    return false;
}
double Newton(double &fx, int &k) {
    double x = 4.0, eps = 1.0e-06;
    unsigned int maxk = 1;
    cout<<"Podaj dokladnosc dla wartosci funkcji: ";
    cin>>eps;
    cout<<"Podaj maksymalna liczbe iteracji: ";
    cin>>maxk;
    k = 0;
    do {
        x -= (f(x) / df(x));
        k++;
    } while(!StopNewton(f(x), eps, k, maxk));
    fx = f(x);
    return x;
}
bool StopBisekcja(double b, double a, double dlt, double eps, double fx) {
    if (fabs(b - a) < dlt) return true;
    if (fabs(fx) < eps) return true;
    return false;
}
double Bisekcja(double &fx, int &iter) {
    double a = 4.0, b = 5.0, s = 0.0, eps = 1.0e-06, dlt = 1.0e-06;
    cout<<"Podaj dokladnosc dla odleglosci punktow: ";
    cin>>dlt;
    cout<<"Podaj dokladnosc dla wartosci funkcji: ";
    cin>>eps;
    iter = 0;
    do {
        s = (a + b) / 2.0;
        if (fabs(f(s)) < eps) {
            fx = f(s);
            return s;
        }
        else {
            if (f(a) * f(s) < 0) b = s;
            else a = s;
        }
        iter++;
    } while (!StopBisekcja(b, a, dlt, eps, f(s)));
    fx = f(s);
    return s;
}
# include <iostream>
# include <math.h>
# include <vector>
# pragma GCC optimize("O2")
# define PI 3.141592653589324
# define E 2.718281828459045
using namespace std;
double GaussCh () {
    double suma = 0.0;
    for (int i = 0; i <= 3; i++) suma += ((PI / 4.0) * pow(cos((PI * (2.0 * i + 1.0)) / 8.0), 2.0));
    return suma;
}
double GaussLe () {
    double suma = 0.0;
    double x[5] = {-0.906180, -0.538469, 0, 0.538469, 0.906180};
    double H[5] = {0.236927, 0.478629, 0.568889, 0.478629, 0.236927};
    for (int i = 0; i <= 4; i++) suma += H[i] * (1.0 / sqrt(1.0 + pow(x[i], 2.0)));
    return suma;
}
double GaussLa () {
    double x[4] = {0.322548, 1.745761, 4.536620, 9.395071};
    double H[4] = {0.603154, 0.357419, 0.038888, 0.000539};
    double suma = 0.0;
    for (int i = 0; i <= 3; i++) suma += H[i] * pow(E, -x[i]) * sin(x[i]) / x[i];
    return suma;
}
double GaussHe () {
    double suma = 0.0;
    double x[5] = {-2.020183, 0.958572, 0.0, 0.958572, 2.020183};
    double H[5] = {0.019953, 0.393619, 0.945309, 0.393619, 0.019953};
    for (int i = 0; i <= 4; i++) suma += H[i] * cos(x[i]);
    return suma;
}
int main () {
    unsigned int menu, m;
    char metoda;
    bool exit = false;
    while (!exit) {
        cout<<endl<<"Zadanie 8.1."<<endl;
        cout<<"Wybierz calke:"<<endl;
        cout<<"1 --> Calka<-1,1> x^2/sqrt(1-x^2) dx [Gauss-Chebyshev] [n=3]"<<endl;
        cout<<"2 --> Calka<-1,1> 1/sqrt(1+x^2) dx [Gauss-Legendre] [n=4]"<<endl;
        cout<<"3 --> Calka<0,+inf.> e^(-2x) * sin(x)/x dx [Gauss-Laguerre] [n=3]"<<endl;
        cout<<"4 --> Calka<-inf.,+inf.> e^(-x^2) * cos(x) dx [Gauss-Hermite] [n=4]"<<endl;
        cout<<"5 --> Wyjscie z programu"<<endl;
        cout<<"Wybor: ";
        cin>>menu;
        cout<<endl;
        switch (menu) {
            case 1: {
                cout<<"Wynik: "<<GaussCh()<<endl;
                break;
            }
            case 2: {
                cout<<"Wynik: "<<GaussLe()<<endl;
                break;
            }
            case 3: {
                cout<<"Wynik: "<<GaussLa()<<endl;
                break;
            }
            case 4: {
                cout<<"Wynik: "<<GaussHe()<<endl;
                break;
            }
            case 5: {
                exit = true;
                break;
            }
            default: {
                cout<<"Nieprawidlowy wybor!\n"<<endl;
                break;
            }
        }
    }
    cout<<"Do widzenia!"<<endl;
    cin.ignore();
    cin.get();
    return 0;
}
# include <iostream>
# include <math.h>
# include <vector>
# pragma GCC optimize("O2")
# define PI 3.141592653589324
# define E 2.718281845904524
using namespace std;
typedef vector<double> TAB;
bool WybierzMetode(char &wybor) {
    cout<<"Wybierz metode calkowania:"<<endl;
    cout<<"T --> Wzor zlozony trapezow"<<endl;
    cout<<"S --> Wzor zlozony Simpsona"<<endl;
    cout<<"Wybor: ";
    cin>>wybor;
    if (wybor == 'T' || wybor == 'S') return true;
    return false;
}
bool LiczbaM(unsigned int &m) {
    cout<<"Podaj liczbe podprzedzialow (m > 1): ";
    cin>>m;
    if (m > 1) return true;
    return false;
}
double ObliczH (unsigned int nr_calki, unsigned int m) {
    if (nr_calki == 1) return (2.0 * PI) / (m * 1.0);
    return 2.0 / (m * 1.0);
}
TAB ObliczF (unsigned int nr_calki, double h, unsigned int m) {
    TAB f;
    f.resize(m + 1);
    if (nr_calki == 1) {
        for (int i = 0; i < m + 1; i++) f[i] = pow(sin(h * (double) i), 2.0) + 2.0;
        return f;
    }
    for (int i = 0; i < m + 1; i++) f[i] = pow(E, h * (double) i) * 2.0 * pow(h * (double) i, 3.0);
    return f;
}
double SumujNieparzyste (TAB f) {
    double w = 0.0;
    for (int i = 1; i < f.size() - 1; i += 2) w += f[i]; 
    return w;
}
double SumujParzyste (TAB f) {
    double w = 0.0;
    for (int i = 2; i < f.size() - 1; i += 2) w += f[i];
    return w;
}
double Calkuj (unsigned int nr_calki, char metoda, unsigned int m) {
    double wynik = 0.0;
    double h = ObliczH(nr_calki, m);
    TAB f = ObliczF(nr_calki, h, m);
    if (metoda == 'T') {
        wynik += (0.5 * (f[0] + f[m]));
        for (int i = 1; i < m; i++) wynik += f[i];
        wynik *= h;
        return wynik;
    }
    wynik = (h / 3.0) * (f[0] + 4 * SumujNieparzyste(f) + 2 * SumujParzyste(f) + f[m]);
    return wynik;
}
int main () {
    unsigned int menu, m;
    char metoda;
    bool exit = false;
    while (!exit) {
        cout<<endl<<"Zadanie 7.1."<<endl;
        cout<<"Wybierz calke:"<<endl;
        cout<<"1 --> Calka<0,2PI> sin2(x) + 2 dx"<<endl;
        cout<<"2 --> Calka<0,2> e^x * 2x^3 dx"<<endl;
        cout<<"3 --> Wyjscie z programu"<<endl;
        cout<<"Wybor: ";
        cin>>menu;
        cout<<endl;
        switch (menu) {
            case 1: {
                if (!WybierzMetode(metoda)) {
                    cout<<"Nieznana metoda!"<<endl;
                    break;
                }
                if (!LiczbaM(m)) {
                    cout<<"Bledna liczba podprzedzialow!"<<endl;
                    break;
                }
                cout<<"Wynik: "<<Calkuj(menu, metoda, m)<<endl<<endl;
                break;
            }
            case 2: {
                if (!WybierzMetode(metoda)) {
                    cout<<"Nieznana metoda!"<<endl;
                    break;
                }
                if (!LiczbaM(m)) {
                    cout<<"Bledna liczba podprzedzialow!"<<endl;
                    break;
                }
                cout<<"Wynik: "<<Calkuj(menu, metoda, m)<<endl<<endl;
                break;
            }
            case 3: {
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
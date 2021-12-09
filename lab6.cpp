#include <iostream>
#include <math.h>
#include <vector>
#define E 2.718281828459045
using namespace std;
typedef vector<double> TAB;
double SumaWW (TAB ww) {
    double suma = 0.0;
    for (int i = 0; i < ww.size(); i++) suma += ww[i];
    return suma;
}
double SumaWW2 (TAB ww) {
    double suma = 0.0;
    for (int i = 0; i < ww.size(); i++) suma += pow(ww[i],2);
    return suma;
}
double SumaWFW (TAB wfw) {
    double suma = 0.0;
    for (int i = 0; i < wfw.size(); i++) suma += wfw[i];
    return suma;
}
double SumaWFWxWW (TAB ww, TAB wfw) {
    double suma = 0.0;
    for (int i = 0; i < ww.size(); i++) suma += (wfw[i] * ww[i]);
    return suma;
}
TAB Odwrotnosc (TAB tab, unsigned int n) {
    TAB new_tab;
    new_tab.resize(n);
    for (int i = 0; i < n; i++) new_tab[i] = 1.0 / tab[i];
    return new_tab;
}
TAB Logarytm (TAB tab, unsigned int n) {
    TAB new_tab;
    new_tab.resize(n);
    for (int i = 0; i < n; i++) new_tab[i] = log(tab[i]);
    return new_tab;
}
unsigned int Wczytaj (TAB &ww, TAB &wfw) {
    unsigned int lw = 0;
    do {
        cout<<"Podaj liczbe wezlow: ";
        cin>>lw;
    } while (lw < 2);
    ww.resize(lw);
    for (int i = 0; i<lw; i++) {
        cout<<"Podaj wartosc wezla "<<i+1<<": ";
        cin>>ww[i];
    }
    wfw.resize(lw);
    for (int i = 0; i < lw; i++) {
        cout<<"Podaj wartosc funkcji w wezle "<<i+1<<": ";
        cin>>wfw[i];
    }
    return lw;
}
void Approx (TAB ww, TAB wfw, unsigned int lw) {
    double W = lw * SumaWW2(ww) - pow(SumaWW(ww), 2.0);
    double Wa0 = SumaWFW(wfw) * SumaWW2(ww) - SumaWFWxWW(ww, wfw) * SumaWW(ww);
    double Wa1 = lw * SumaWFWxWW(ww, wfw) - SumaWW(ww) * SumaWFW(wfw);
    double a1 = Wa1 / W;
    double a0 = Wa0 / W;
    cout<<"a: "<<a1<<endl;
    cout<<"b: "<<a0<<endl<<endl;
}
void ApproxE (TAB ww, TAB wfw, unsigned int lw) {
    double W = lw * SumaWW2(ww) - pow(SumaWW(ww), 2.0);
    double Wa0 = SumaWFW(wfw) * SumaWW2(ww) - SumaWFWxWW(ww, wfw) * SumaWW(ww);
    double Wa1 = lw * SumaWFWxWW(ww, wfw) - SumaWW(ww) * SumaWFW(wfw);
    double a1 = pow(E, Wa1 / W);
    double a0 = pow(E, Wa0 / W);
    cout<<"a: "<<a1<<endl;
    cout<<"b: "<<a0<<endl<<endl;
}
int main () {
    unsigned int lw = 0, menu;
    TAB ww, wfw;
    bool exit = false;
    while (!exit) {
        cout<<"Zadanie 6.1."<<endl;
        cout<<"1 --> Wczytaj nowe dane"<<endl;
        cout<<"2 --> Wyswietl wspolczynniki funkcji approx g(x) = ax + b"<<endl;
        cout<<"3 --> Wyswietl wspolczynniki funkcji approx g(x) = a/x + b"<<endl;
        cout<<"4 --> Wyswietl wspolczynniki funkcji approx g(x) = b * a^x"<<endl;
        cout<<"5 --> Wyjscie z programu"<<endl;
        cout<<"Wybor: ";
        cin>>menu;
        cout<<endl;
        switch (menu) {
            case 1: {
                lw = Wczytaj(ww, wfw);
                cout<<"Dane wczytane poprawnie\n"<<endl;
                break;
            }
            case 2: {
                if (lw == 0) cout<<"Brak danych!\n"<<endl;
                else Approx(ww, wfw, lw);
                break;
            }
            case 3: {
                if (lw == 0) cout<<"Brak danych!\n"<<endl;
                else Approx(Odwrotnosc(ww, lw), wfw, lw);
                break;
            }
            case 4: {
                if (lw == 0) cout<<"Brak danych!\n"<<endl;
                else ApproxE(ww, Logarytm(wfw, lw), lw);
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
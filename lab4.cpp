# include <iostream>
# include <math.h>
using namespace std;
double iloczyn (double p, double *&ww, int i) {
    double il = 1.0;
    for (int k = 0; k < i; k++) il *= (p - ww[k]);
    return il;
}
void IR (double *&ir, double *&wfw, double *&ww, double lw) {
    int i = 0;
    for (i = 0; i < lw; i++) ir[i] = wfw[i];
    int k = 1;
    for (k = 1; k < lw; k++) {
        for (i = lw - 1; i >= k; i--) ir[i] = (ir[i] - ir[i-1]) / (ww[i] - ww[i-k]);
    }
}
void zadanie_4_1() {
    unsigned int lw = 0;
    do {
        cout<<"Podaj liczbe wezlow: ";
        cin>>lw;
    } while (lw < 2);
    double *ww = new double[lw];
    for (int i=0; i<lw; i++) {
        do {
            cout<<"Podaj wartosc wezla "<<i+1<<": ";
            cin>>ww[i];
        } while (i != 0 && ww[i-1] >= ww[i]);
    }
    double *wfw = new double[lw];
    for (int i=0; i<lw; i++) {
        cout<<"Podaj wartosc funkcji w wezle "<<i+1<<": ";
        cin>>wfw[i];
    }
    double p;
    cout<<"Podaj punkt p: ";
    cin>>p;
    if (p < ww[0] || p > ww[lw-1]) {
        cout<<"Blad warunku interpolacji!"<<endl;
        return;
    }
    double *ir = new double[lw];
    double wynik = 0.0;
    IR(*&ir, *&wfw, *&ww, lw);
    for (int i = 0; i < lw; i++) wynik += (ir[i] * iloczyn(p, *&ww, i));
    cout<<"Wartosc w punkcie x = "<<p<<": "<<wynik<<endl;
}
int main () {
    bool exit = false;
    unsigned int menu = 1;
    while (!exit) {
        cout<<"Wybierz opcje:\n1 --> Zadanie 4.1\n2 --> Wyjscie z programu\nWybor: ";
        cin>>menu;
        cout<<endl;
        switch (menu) {
            case 1: {
                zadanie_4_1();
                cout<<endl;
                break;
            }
            case 2: {
                exit = true;
                cout<<"Do widzenia!"<<endl;
                break;
            }
            default: {
                cout<<"Nieprawidlowy wybor!"<<endl;
                break;
            }
        }
    }
    cin.ignore();
    cin.get();
    return 0;
}

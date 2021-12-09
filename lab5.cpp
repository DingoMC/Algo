# include <iostream>
# include <vector>
using namespace std;
typedef vector <double> TAB;
typedef vector < vector <double> > TAB2D;
typedef vector <unsigned int> SIZE_TAB;
unsigned int Wczytaj (TAB &ww, TAB &wfw, double &p) {
    unsigned int lw = 0;
    do {
        cout<<"Podaj liczbe wezlow: ";
        cin>>lw;
    } while (lw < 2);
    ww.resize(lw);
    for (int i=0; i<lw; i++) {
        do {
            cout<<"Podaj wartosc wezla "<<i+1<<": ";
            cin>>ww[i];
        } while (i != 0 && ww[i-1] >= ww[i]);
    }
    wfw.resize(lw);
    for (int i=0; i<lw; i++) {
        cout<<"Podaj wartosc funkcji w wezle "<<i+1<<": ";
        cin>>wfw[i];
    }
    cout<<"Podaj punkt p: ";
    cin>>p;
    if (p < ww[0] || p > ww[lw-1]) {
        cout<<"Blad warunku interpolacji!"<<endl;
        return 0;
    }
    return lw;
}
unsigned int WczytajHermita (TAB &ww, TAB &wfw, TAB2D &wpfw, SIZE_TAB &krotnosci, double &p) {
    unsigned int lw = 0;
    do {
        cout<<"Podaj liczbe wezlow: ";
        cin>>lw;
    } while (lw < 2);
    ww.resize(lw);
    for (int i=0; i<lw; i++) {
        do {
            cout<<"Podaj wartosc wezla "<<i+1<<": ";
            cin>>ww[i];
        } while (i != 0 && ww[i-1] >= ww[i]);
    }
    krotnosci.resize(lw);
    for (int i=0; i<lw; i++) {
        do {
            cout<<"Podaj krotnosc wezla "<<i+1<<": ";
            cin>>krotnosci[i];
        } while (krotnosci[i] < 1);
    }
    wfw.resize(lw);
    for (int i=0; i<lw; i++) {
        cout<<"Podaj wartosc funkcji w wezle "<<i+1<<": ";
        cin>>wfw[i];
    }
    wpfw.resize(lw);
    for (int i = 0; i < lw; i++) wpfw[i].resize(krotnosci[i] - 1);
    for (int i = 0; i < lw; i++) {
        for (int k = 0; k < wpfw[i].size(); k++) {
            cout<<"Podaj wartosc pochodnej ("<<k+1<<") funkcji w wezle "<<i+1<<": ";
            cin>>wpfw[i][k];
        }
    }
    cout<<"Podaj punkt p: ";
    cin>>p;
    if (p < ww[0] || p > ww[lw-1]) {
        cout<<"Blad warunku interpolacji!"<<endl;
        return 0;
    }
    return lw;
}
TAB2D Utworz2D (unsigned int n) {
    TAB2D T;
    T.resize(n);
    for (int i = 0; i < n; i++) T[i].resize(n);
    return T;
}
void zadanie_5_1() {
    unsigned int lw = 0;
    TAB ww, wfw;
    double p;
    lw = Wczytaj(ww, wfw, p);
    TAB2D P = Utworz2D(lw);
    for (int i = 0; i < lw; i++) P[i][0] = wfw[i];
    for (int k = 1; k < lw; k++) {
        for (int w = 0; w < lw - k; w++) {
            P[w][k] = ((p - ww[w]) * P[w+1][k-1] - (p - ww[w+k]) * P[w][k-1]) / (ww[w+k] - ww[w]);
        }
    }
    cout<<P[0][lw-1]<<endl;
}
void zadanie_5_2() {
    unsigned int lw = 0;
    TAB ww, wfw;
    double p;
    TAB2D wpfw;
    SIZE_TAB krotnosci;
    lw = WczytajHermita(ww, wfw, wpfw, krotnosci, p);
}
int main () {
    bool exit = false;
    unsigned int menu = 1;
    while (!exit) {
        cout<<"Wybierz opcje:\n1 --> Zadanie 5.1\n2 --> Interpolacja Hermita\n3 --> Wyjscie z programu\nWybor: ";
        cin>>menu;
        cout<<endl;
        switch (menu) {
            case 1: {
                zadanie_5_1();
                cout<<endl;
                break;
            }
            case 2: {
                zadanie_5_2();
                cout<<endl;
                break;
            }
            case 3: {
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

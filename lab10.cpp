# include <iostream>
# include <math.h>
# include <vector>
# include <stdlib.h>
# pragma GCC optimize("O2")
using namespace std;
const double eps = 1.0e-06;
typedef vector <vector <double>> Matrix;
typedef vector <double> TAB;
struct Indeks2D {
    int iw;
    int ik;
};
bool WyborDanych ();
unsigned int WczytajDane (Matrix&);
unsigned int WczytajDomyslne (Matrix&, int);
int IndexMAXK (Matrix, int, int);
Indeks2D IndexMAXPelny (Matrix, int, int);
bool Eliminacja (Matrix&, int, int);
bool Oblicz (Matrix, TAB&, int);
void Wyswietl (TAB, int);
void Wyswietl2D (Matrix, int);
void ZamienWiersze (Matrix&, int, int, int);
int main () {
    // Zmienne ukladu
    Matrix Ab;
    TAB X;
    unsigned int n;
    // Zmienne programu
    int menu = 0;
    bool exit = false, daneZewn = false;
    while (!exit) {
        cout<<endl<<"Wybierz metode"<<endl;
        cout<<"1 --> Podstawowa (bez wyboru elementu maksymalnego)"<<endl;
        cout<<"2 --> Z wyborem elementu maksymalnego w kolumnie"<<endl;
        cout<<"3 --> Z pelnym wyborem elementu maksymalnego"<<endl;
        cout<<"Wyjdz z programu (4)"<<endl;
        cout<<"Wybor: ";
        cin>>menu;
        if (cin.fail()) {
            system("cls");
            cin.clear();
            cin.ignore();
            menu = 0;
            cout<<endl<<"Nieprawidlowa wartosc!"<<endl;
            continue;
        }
        switch (menu) {
            case 1: {
                daneZewn = WyborDanych();
                if (daneZewn) n = WczytajDane(Ab);
                else n = WczytajDomyslne(Ab, 1);
                if (Eliminacja(Ab, n, 1)) {
                    cout<<"Podczas wykonywania eliminacji wystapil blad!"<<endl;
                    break;
                }
                if (Oblicz(Ab, X, n)) {
                    cout<<"Podczas wykonywania postepowania odwrotnego wystapil blad!"<<endl;
                    break;
                }
                Wyswietl(X, n);
                break;
            }
            case 2: {
                daneZewn = WyborDanych();
                if (daneZewn) n = WczytajDane(Ab);
                else n = WczytajDomyslne(Ab, 2);
                if (Eliminacja(Ab, n, 2)) {
                    cout<<"Podczas wykonywania eliminacji wystapil blad!"<<endl;
                    break;
                }
                if (Oblicz(Ab, X, n)) {
                    cout<<"Podczas wykonywania postepowania odwrotnego wystapil blad!"<<endl;
                    break;
                }
                Wyswietl(X, n);
                break;
            }
            case 3: {
                daneZewn = WyborDanych();
                if (daneZewn) n = WczytajDane(Ab);
                else n = WczytajDomyslne(Ab, 3);
                break;
            }
            case 4: {
                exit = true;
                break;
            }
            default: {
                system("cls");
                cout<<endl<<"Nieprawidlowy wybor!"<<endl;
                break;
            }
        }
    }
    cout<<endl<<"Program zakonczony. Do widzenia!"<<endl;
    cin.ignore();
    cin.get();
    return 0;
}
int IndexMAXK (Matrix Ab, int k, int n) {
    double max = fabs(Ab[k][k]);
    int imax = k;
    for (int i = k + 1; i < n; i++) {
        if (fabs(Ab[i][k]) > max) {
            max = fabs(Ab[i][k]);
            imax = i;
        }
    }
    return imax;
}
void ZamienWiersze (Matrix &Ab, int i1, int i2, int n) {
    if (i1 == i2) return;
    TAB pom;
    pom = Ab[i1];
    Ab[i1] = Ab[i2];
    Ab[i2] = pom;
}
void Wyswietl (TAB X, int n) {
    cout<<"x = [";
    for (int i = 0; i < n; i++) {
        cout<<X[i];
        if (i < n - 1) cout<<",";
    }
    cout<<"]T"<<endl;
}
void Wyswietl2D (Matrix Ab, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            cout<<Ab[i][j]<<" | ";
        }
        cout<<endl;
    }
}
bool Oblicz (Matrix Ab, TAB &X, int n) {
    if (fabs(Ab[n-1][n-1]) <= eps) {
        system("cls");
        cout<<"Blad w postepowaniu odwrotnym - a"<<n<<n<<" <= eps"<<endl;
        return true;
    }
    X.resize(n);
    X[n-1] = Ab[n-1][n] / Ab[n-1][n-1];
    for (int k = n - 2; k >= 0; k--) {
        double s = 0.0;
        for (int j = k + 1; j < n; j++) s += (X[j] * Ab[k][j]);
        X[k] = (Ab[k][n] - s) / Ab[k][k];
    }
    return false;
}
bool Eliminacja (Matrix &Ab, int n, int metoda) {
    // Krok 1
    int imax;
    if (metoda == 2) {
        imax = IndexMAXK(Ab, 0, n);
        ZamienWiersze(Ab, 0, imax, n);
    }
    if (fabs(Ab[0][0]) <= eps) {
        system("cls");
        cout<<"Blad w kroku 1. eliminacji: a11 <= eps."<<endl;
        return true;
    }
    TAB p;
    p.resize(n - 1);
    for (int i = 0; i < n - 1; i++) p[i] = Ab[i+1][0] / Ab[0][0];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n + 1; j++) Ab[i][j] -= (p[i-1] * Ab[0][j]);
    }
    // Krok k
    for (int k = 2; k < n; k++) {
        if (metoda == 2) {
            imax = IndexMAXK(Ab, k - 1, n);
            ZamienWiersze(Ab, k - 1, imax, n);
        }
        if (fabs(Ab[k-1][k-1]) <= eps) {
            system("cls");
            cout<<"Blad w kroku "<<k<<". eliminacji: a"<<k<<k<<" <= eps"<<endl;
            return true;
        }
        p.resize(n - k);
        for (int i = 0; i < n - k; i++) p[i] = Ab[k+i][k-1] / Ab[k-1][k-1];
        for (int i = k; i < n; i++) {
            for (int j = 0; j < n + 1; j++) Ab[i][j] -= (p[i-k] * Ab[k-1][j]);
        }
    }
    return false;
}
unsigned int WczytajDomyslne (Matrix& Ab, int metoda) {
    unsigned int n;
    if (metoda == 1) {
        // Przyklad 10.1.
        n = 4;
        Ab.resize(n);
        for (int i = 0; i < n; i++) Ab[i].resize(n + 1);
        Ab = {{1, 1, 0, -3, 1}, {1, 4, -1, -4, -2}, {0.5, 0.5, -3, -5.5, 1.5}, {1.5, 3, -5, -9, -0.5}};
        return n;
    }
    if (metoda == 2) {
        // Przyklad 10.2.
        n = 4;
        Ab.resize(n);
        for (int i = 0; i < n; i++) Ab[i].resize(n + 1);
        Ab = {{2.25, -2.5, 4, -5.25, -1}, {-3, -7.5, 6.5, 0, 17}, {-6.25, -12.5, 0.25, 5.25, 24.25}, {9, 10, 7, -21, -33}};
        return n;
    }
    return 0;
}
unsigned int WczytajDane (Matrix &Ab) {
    unsigned int n = 0;
    while (n < 2) {
        system("cls");
        cout<<"Podaj liczbe niewiadomych (n): ";
        cin>>n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            n = 0;
            cout<<endl<<"Nieprawidlowa wartosc!"<<endl;
        }
    }
    Ab.resize(n);
    for (int i = 0; i < n; i++) Ab[i].resize(n + 1);
    system("cls");
    cout<<"Podaj macierz [A|b]:"<<endl;
    for (int i = 0; i < n; i++) {
        cout<<"Wiersz ["<<i+1<<"]: ";
        for (int j = 0; j < n + 1; j++) cin>>Ab[i][j];
    }
    return n;
}
bool WyborDanych () {
    bool ok = false, daneZewn = false;
    while (!ok) {
        system("cls");
        cout<<endl<<"Wybierz dane"<<endl;
        cout<<"0 --> Dane z programu"<<endl;
        cout<<"1 --> Dane od uzytkownika"<<endl;
        cout<<"Wybor: ";
        cin>>daneZewn;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            daneZewn = false;
            cout<<endl<<"Nieprawidlowy wybor!"<<endl;
        }
        else {
            system("cls");
            return daneZewn;
        }
    }
    return false;
}
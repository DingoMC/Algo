# include <iostream>
# include <math.h>
# include <vector>
# include <stdlib.h>
# pragma GCC optimize("O2")
using namespace std;
const double eps = 1.0e-06;
typedef vector <vector <double>> Matrix;
typedef vector <double> TAB;
typedef vector <unsigned int> IndexTAB;
struct Indeks2D {
    int iw;
    int ik;
};
bool WyborDanych ();
unsigned int WczytajDane (Matrix&);
unsigned int WczytajDomyslne (Matrix&, int);
int IndexMAXK (Matrix, int, int);
Indeks2D IndexMAXPelny (Matrix, int, int);
bool Eliminacja (Matrix&, int, int, IndexTAB&);
bool Oblicz (Matrix, TAB&, int);
void Wyswietl (TAB, int, IndexTAB);
void Wyswietl2D (Matrix, int);
void ZamienWiersze (Matrix&, int, int, int);
void ZamienWiK (Matrix&, Indeks2D, Indeks2D, int, IndexTAB&);
int main () {
    // Zmienne ukladu
    Matrix Ab;
    TAB X;
    unsigned int n;
    IndexTAB IndeksyX;
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
                if (Eliminacja(Ab, n, 1, IndeksyX)) {
                    cout<<"Podczas wykonywania eliminacji wystapil blad!"<<endl;
                    break;
                }
                if (Oblicz(Ab, X, n)) {
                    cout<<"Podczas wykonywania postepowania odwrotnego wystapil blad!"<<endl;
                    break;
                }
                Wyswietl(X, n, IndeksyX);
                break;
            }
            case 2: {
                daneZewn = WyborDanych();
                if (daneZewn) n = WczytajDane(Ab);
                else n = WczytajDomyslne(Ab, 2);
                if (Eliminacja(Ab, n, 2, IndeksyX)) {
                    cout<<"Podczas wykonywania eliminacji wystapil blad!"<<endl;
                    break;
                }
                if (Oblicz(Ab, X, n)) {
                    cout<<"Podczas wykonywania postepowania odwrotnego wystapil blad!"<<endl;
                    break;
                }
                Wyswietl(X, n, IndeksyX);
                break;
            }
            case 3: {
                daneZewn = WyborDanych();
                if (daneZewn) n = WczytajDane(Ab);
                else n = WczytajDomyslne(Ab, 3);
                if (Eliminacja(Ab, n, 3, IndeksyX)) {
                    cout<<"Podczas wykonywania eliminacji wystapil blad!"<<endl;
                    break;
                }
                if (Oblicz(Ab, X, n)) {
                    cout<<"Podczas wykonywania postepowania odwrotnego wystapil blad!"<<endl;
                    break;
                }
                Wyswietl(X, n, IndeksyX);
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
Indeks2D IndexMAXPelny (Matrix Ab, int k, int n) {
    double max = fabs(Ab[k][k]);
    Indeks2D imax;
    imax.ik = k;
    imax.iw = k;
    for (int i = k + 1; i < n; i++) {
        for (int j = k + 1; j < n; j++) {
            if (fabs(Ab[i][j]) > max) {
                max = fabs(Ab[i][j]);
                imax.iw = i;
                imax.ik = j;
            }
        }
    }
    return imax;
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
void ZamienWiK (Matrix &Ab, Indeks2D i1, Indeks2D i2, int n, IndexTAB &IndeksyX) {
    if (i1.iw != i2.iw) {
        TAB pom;
        pom = Ab[i1.iw];
        Ab[i1.iw] = Ab[i2.iw];
        Ab[i2.iw] = pom;
    }
    if (i1.ik == i2.ik) return;
    unsigned int iX;
    iX = IndeksyX[i1.ik];
    IndeksyX[i1.ik] = IndeksyX[i2.ik];
    IndeksyX[i2.ik] = iX;
    double p;
    for (int i = 0; i < n; i++) {
        p = Ab[i][i1.ik];
        Ab[i][i1.ik] = Ab[i][i2.ik];
        Ab[i][i2.ik] = p;
    }
}
void Wyswietl (TAB X, int n, IndexTAB IndeksyX) {
    cout<<"x = [";
    for (int i = 0; i < n; i++) {
        cout<<X[IndeksyX[i]];
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
bool Eliminacja (Matrix &Ab, int n, int metoda, IndexTAB &IndeksyX) {
    int imax;
    Indeks2D MAXi, DoZamiany;
    IndeksyX.resize(n);
    for (unsigned int i = 0; i < n; i++) IndeksyX[i] = i;
    // Krok 1
    if (metoda == 2) {
        imax = IndexMAXK(Ab, 0, n);
        ZamienWiersze(Ab, 0, imax, n);
    }
    if (metoda == 3) {
        MAXi = IndexMAXPelny(Ab, 0, n);
        DoZamiany.ik = 0;
        DoZamiany.iw = 0;
        ZamienWiK(Ab, DoZamiany, MAXi, n, IndeksyX);
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
        if (metoda == 3) {
            MAXi = IndexMAXPelny(Ab, k - 1, n);
            DoZamiany.ik = k - 1;
            DoZamiany.iw = k - 1;
            ZamienWiK(Ab, DoZamiany, MAXi, n, IndeksyX);
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
    if (metoda == 3) {
        // Zadanie 10.3.
        n = 5;
        Ab.resize(n);
        for (int i = 0; i < n; i++) Ab[i].resize(n + 1);
        Ab = {{14, -13, 3, -16, -42, -37}, 
            {3.5, -18, 13, -23.75, -21, -5.5}, 
            {3.5, 3, -5.25, 9.25, 10.5, 12.5}, 
            {2, 14.5, -10.5, 18.5, 21, 23.5}, 
            {1.5, 6.75, -9.25, 17, -10.5, -45.25}};
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

# include <iostream>
# include <math.h>
# include <vector>
# include <stdlib.h>
# pragma GCC optimize("O2")
using namespace std;
const double eps = 1.0e-06;                 // Definicja epsilonu
typedef vector <vector <double>> Matrix;    // Definicja typu Macierzowego (Tablica 2D)
typedef vector <double> TAB;                // Definicja typu Wektora (Tablica 1D)
typedef vector <unsigned int> IndexTAB;     // Definicja typu Wektora Indeksów
// Struktura indeksu dwuwymiarowego {Indeks Wiersza, Indeks Kolumny}
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
void Wyswietl (TAB, int);
void Wyswietl2D (Matrix, int);
void ZamienWiersze (Matrix&, int, int, int);
void ZamienWiK (Matrix&, Indeks2D, Indeks2D, int, int, IndexTAB&);
void ZamienX (TAB&, IndexTAB, int);
int main () {
    // Zmienne układu współrzędnych
    Matrix Ab;
    TAB X;
    unsigned int n;
    IndexTAB IndeksyX;
    // Zmienne programu
    int menu = 0;
    bool exit = false;
    // Menu
    while (!exit) {
        cout<<endl<<"Wybierz metode"<<endl;
        cout<<"1 --> Podstawowa (bez wyboru elementu maksymalnego)"<<endl;
        cout<<"2 --> Z wyborem elementu maksymalnego w kolumnie"<<endl;
        cout<<"3 --> Z pelnym wyborem elementu maksymalnego"<<endl;
        cout<<"Wyjdz z programu (4)"<<endl;
        cout<<"Wybor: ";
        cin>>menu;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            menu = 0;
            cout<<endl<<"Nieprawidlowa wartosc!"<<endl;
            continue;
        }
        switch (menu) {
            case 1: {
                if (WyborDanych()) n = WczytajDane(Ab);
                else n = WczytajDomyslne(Ab, 1);
                cout<<endl<<"1. Metoda Podstawowa"<<endl;
                cout<<"Macierz [A|b] przed eliminacja Gaussa:"<<endl;
                Wyswietl2D(Ab, n);
                if (Eliminacja(Ab, n, 1, IndeksyX)) {
                    cout<<"Podczas wykonywania eliminacji wystapil blad!"<<endl;
                    break;
                }
                cout<<endl<<"Macierz [A|b] po eliminacji Gaussa:"<<endl;
                Wyswietl2D(Ab, n);
                if (Oblicz(Ab, X, n)) {
                    cout<<"Podczas wykonywania postepowania odwrotnego wystapil blad!"<<endl;
                    break;
                }
                cout<<endl<<"Macierz wynikowa X:"<<endl;
                Wyswietl(X, n);
                break;
            }
            case 2: {
                if (WyborDanych()) n = WczytajDane(Ab);
                else n = WczytajDomyslne(Ab, 2);
                cout<<endl<<"2. Metoda z wyborem elementu maksymalnego w kolumnie"<<endl;
                cout<<"Macierz [A|b] przed eliminacja Gaussa:"<<endl;
                Wyswietl2D(Ab, n);
                if (Eliminacja(Ab, n, 2, IndeksyX)) {
                    cout<<"Podczas wykonywania eliminacji wystapil blad!"<<endl;
                    break;
                }
                cout<<endl<<"Macierz [A|b] po eliminacji Gaussa:"<<endl;
                Wyswietl2D(Ab, n);
                if (Oblicz(Ab, X, n)) {
                    cout<<"Podczas wykonywania postepowania odwrotnego wystapil blad!"<<endl;
                    break;
                }
                cout<<endl<<"Macierz wynikowa X:"<<endl;
                Wyswietl(X, n);
                break;
            }
            case 3: {
                if (WyborDanych()) n = WczytajDane(Ab);
                else n = WczytajDomyslne(Ab, 3);
                cout<<endl<<"3. Metoda z pelnym wyborem elementu maksymalnego"<<endl;
                cout<<"Macierz [A|b] przed eliminacja Gaussa:"<<endl;
                Wyswietl2D(Ab, n);
                if (Eliminacja(Ab, n, 3, IndeksyX)) {
                    cout<<"Podczas wykonywania eliminacji wystapil blad!"<<endl;
                    break;
                }
                cout<<endl<<"Macierz [A|b] po eliminacji Gaussa:"<<endl;
                Wyswietl2D(Ab, n);
                if (Oblicz(Ab, X, n)) {
                    cout<<"Podczas wykonywania postepowania odwrotnego wystapil blad!"<<endl;
                    break;
                }
                ZamienX(X, IndeksyX, n);
                cout<<endl<<"Macierz wynikowa X:"<<endl;
                Wyswietl(X, n);
                break;
            }
            case 4: {
                exit = true;
                break;
            }
            default: {
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
// Zamiana wartości niewiadomych na zgodne z kolejnością niewiadomych (tylko metoda 3)
void ZamienX (TAB &X, IndexTAB IndeksyX, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (IndeksyX[j] == i) {
                swap(X[i], X[j]);
                swap(IndeksyX[i], IndeksyX[j]);
                break;
            }
        }
    }
}
// Zwracanie indeksów z pełnego wyboru elementu maksymalnego co do modułu (tylko metoda 3)
Indeks2D IndexMAXPelny (Matrix Ab, int k, int n) {
    double max = fabs(Ab[k][k]);
    Indeks2D imax = {k, k};
    for (int i = k; i < n; i++) {
        for (int j = k; j < n; j++) {
            if (fabs(Ab[i][j]) > max) {
                max = fabs(Ab[i][j]);
                imax = {i, j};
            }
        }
    }
    return imax;
}
// Zwracanie indeksów z wyboru elementu maksymalnego co do modułu w wierszu (tylko metoda 2)
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
// Zamiana dwóch wierszy macierzy
void ZamienWiersze (Matrix &Ab, int i1, int i2, int n) {
    if (i1 != i2) swap(Ab[i1], Ab[i2]);
}
// Zamiana dwóch wierszy i dwóch kolumn macierzy
void ZamienWiK (Matrix &Ab, Indeks2D i1, Indeks2D i2, int n, int k, IndexTAB &IndeksyX) {
    if (i1.iw != i2.iw) swap(Ab[i1.iw], Ab[i2.iw]);
    if (i1.ik == i2.ik) return;
    swap(IndeksyX[i1.ik], IndeksyX[i2.ik]);
    for (int i = 0; i < n; i++) swap(Ab[i][i1.ik], Ab[i][i2.ik]);
}
// Wyświetlanie macierzy wynikowej
void Wyswietl (TAB X, int n) {
    cout<<"x = [";
    for (int i = 0; i < n; i++) {
        cout<<X[i];
        if (i < n - 1) cout<<" ; ";
    }
    cout<<"]T"<<endl;
}
// Wyświetlanie macierzy dwuwymiarowej
void Wyswietl2D (Matrix Ab, int n) {
    for (int i = 0; i < n; i++) {
        cout<<"[ ";
        for (int j = 0; j < n + 1; j++) {
            cout<<Ab[i][j]<<"\t";
            if (j == n - 1) cout<<"| ";
        }
        cout<<"]"<<endl;
    }
}
// Postępowanie odwrotne Gaussa
bool Oblicz (Matrix Ab, TAB &X, int n) {
    if (fabs(Ab[n-1][n-1]) <= eps) {
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
// Eliminacja Gaussa
bool Eliminacja (Matrix &Ab, int n, int metoda, IndexTAB &IndeksyX) {
    IndeksyX.resize(n);
    for (unsigned int i = 0; i < n; i++) IndeksyX[i] = i;
    for (int k = 1; k < n; k++) {
        if (metoda == 2) ZamienWiersze(Ab, k-1, IndexMAXK(Ab, k-1, n), n);
        if (metoda == 3) ZamienWiK(Ab, {k-1, k-1}, IndexMAXPelny(Ab, k-1, n), n, k-1, IndeksyX);
        if (fabs(Ab[k-1][k-1]) <= eps) {
            cout<<"Blad w kroku "<<k<<". eliminacji: a"<<k<<k<<" <= eps"<<endl;
            return true;
        }
        TAB p;
        p.resize(n - k);
        for (int i = 0; i < n - k; i++) p[i] = Ab[k+i][k-1] / Ab[k-1][k-1];
        for (int i = k; i < n; i++) {
            for (int j = 0; j < n + 1; j++) Ab[i][j] -= (p[i-k] * Ab[k-1][j]);
        }
    }
    return false;
}
// Wczytanie stałych danych dla każdej z metod
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
// Wczytaj dane z klawiatury
unsigned int WczytajDane (Matrix &Ab) {
    unsigned int n = 0;
    while (n < 2) {
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
    cout<<"Podaj macierz [A|b]:"<<endl;
    for (int i = 0; i < n; i++) {
        cout<<"Wiersz ["<<i+1<<"]: ";
        for (int j = 0; j < n + 1; j++) cin>>Ab[i][j];
    }
    return n;
}
// Menu sposobu wprowadzania danych
bool WyborDanych () {
    bool daneZewn = false;
    while (true) {
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
            return daneZewn;
        }
    }
    return false;
}
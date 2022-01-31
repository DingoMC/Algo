# include <iostream>
# include <math.h>
# include <vector>
# include <stdlib.h>
# include "colored_text.h"
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
        ctext::text("\n&eWybierz metode\n");
        ctext::text("&a1 &7--> &bPodstawowa (bez wyboru elementu maksymalnego)\n");
        ctext::text("&a2 &7--> &bZ wyborem elementu maksymalnego w kolumnie\n");
        ctext::text("&a3 &7--> &bZ pelnym wyborem elementu maksymalnego\n");
        ctext::text("&3Wyjdz z programu &7(&24&7)\n");
        ctext::text("&eWybor&7:&a ");
        cin>>menu;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            menu = 0;
            ctext::text("\n&cNieprawidlowa wartosc!\n");
            fflush(stdin);
            continue;
        }
        switch (menu) {
            case 1: {
                if (WyborDanych()) n = WczytajDane(Ab);
                else n = WczytajDomyslne(Ab, 1);
                ctext::text("\n&a1. Metoda Podstawowa\n");
                ctext::text("\n&eMacierz &7[&dA&7|&db&7]&e przed eliminacja Gaussa&7:\n");
                Wyswietl2D(Ab, n);
                if (Eliminacja(Ab, n, 1, IndeksyX)) {
                    ctext::text("\n&cPodczas wykonywania eliminacji wystapil blad!\n");
                    break;
                }
                if (Oblicz(Ab, X, n)) {
                    ctext::text("\n&cPodczas wykonywania postepowania odwrotnego wystapil blad!\n");
                    break;
                }
                ctext::text("\n&aMacierz wynikowa &dX&7:&a ");
                Wyswietl(X, n);
                break;
            }
            case 2: {
                if (WyborDanych()) n = WczytajDane(Ab);
                else n = WczytajDomyslne(Ab, 2);
                ctext::text("\n&a2. Metoda z wyborem elementu maksymalnego w kolumnie\n");
                ctext::text("\n&eMacierz &7[&dA&7|&db&7]&e przed eliminacja Gaussa&7:\n");
                Wyswietl2D(Ab, n);
                if (Eliminacja(Ab, n, 2, IndeksyX)) {
                    ctext::text("\n&cPodczas wykonywania eliminacji wystapil blad!\n");
                    break;
                }
                if (Oblicz(Ab, X, n)) {
                    ctext::text("\n&cPodczas wykonywania postepowania odwrotnego wystapil blad!\n");
                    break;
                }
                ctext::text("\n&aMacierz wynikowa &dX&7:&a ");
                Wyswietl(X, n);
                break;
            }
            case 3: {
                if (WyborDanych()) n = WczytajDane(Ab);
                else n = WczytajDomyslne(Ab, 3);
                ctext::text("\n&a3. Metoda z pelnym wyborem elementu maksymalnego\n");
                ctext::text("\n&eMacierz &7[&dA&7|&db&7]&e przed eliminacja Gaussa&7:\n");
                Wyswietl2D(Ab, n);
                if (Eliminacja(Ab, n, 3, IndeksyX)) {
                    ctext::text("\n&cPodczas wykonywania eliminacji wystapil blad!\n");
                    break;
                }
                if (Oblicz(Ab, X, n)) {
                    ctext::text("\n&cPodczas wykonywania postepowania odwrotnego wystapil blad!\n");
                    break;
                }
                ZamienX(X, IndeksyX, n);
                ctext::text("\n&aMacierz wynikowa &dX&7:&a ");
                Wyswietl(X, n);
                break;
            }
            case 4: {
                exit = true;
                break;
            }
            default: {
                ctext::text("\n&cNieprawidlowy wybor!\n");
                break;
            }
        }
    }
    ctext::rainbow_text("\nDo widzenia!\n");
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
    ctext::text("&7[&a");
    for (int i = 0; i < n; i++) {
        cout<<X[i];
        if (i < n - 1) ctext::text(" &8;&a ");
    }
    ctext::text("&7]&5T\n");
}
// Wyświetlanie macierzy dwuwymiarowej
void Wyswietl2D (Matrix Ab, int n) {
    for (int i = 0; i < n; i++) {
        ctext::text("&7[ ");
        for (int j = 0; j < n + 1; j++) {
            ctext::text("", ct::CYAN);
            cout<<Ab[i][j]<<"\t";
            if (j == n - 1) ctext::text("&8| ");
        }
        ctext::text("&7]\n");
    }
}
// Postępowanie odwrotne Gaussa
bool Oblicz (Matrix Ab, TAB &X, int n) {
    if (fabs(Ab[n-1][n-1]) <= eps) {
        ctext::text("\n&cBlad w postepowaniu odwrotnym: A" + to_string(n) + to_string(n) +" <= eps\n");
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
            ctext::text("\n&cBlad w kroku " + to_string(k) + ". eliminacji: A" + to_string(k) + to_string(k) +" <= eps\n");
            return true;
        }
        TAB p;
        p.resize(n - k);
        for (int i = 0; i < n - k; i++) p[i] = Ab[k+i][k-1] / Ab[k-1][k-1];
        for (int i = k; i < n; i++) {
            for (int j = 0; j < n + 1; j++) Ab[i][j] -= (p[i-k] * Ab[k-1][j]);
        }
        ctext::text("\n&eMacierz &7[&dA&7|&db&7]&e po &b" + to_string(k) + " &ekroku eliminacji Gaussa:\n");
        Wyswietl2D(Ab, n);
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
        ctext::text("&bPodaj liczbe niewiadomych &7(&an&7):&a ");
        cin>>n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            n = 0;
            ctext::text("\n&cNieprawidlowa wartosc!\n");
        }
    }
    Ab.resize(n);
    for (int i = 0; i < n; i++) Ab[i].resize(n + 1);
    ctext::text("&bPodaj macierz &7[&dA&7|&db&7] &7(&8Nowy wiersz - <Enter>, Nowa kolumna - <Spacja>&7):\n");
    for (int i = 0; i < n; i++) {
        ctext::text("&bWiersz &7[&a" + to_string(i+1) + "&7]:&d ");
        for (int j = 0; j < n + 1; j++) cin>>Ab[i][j];
    }
    return n;
}
// Menu sposobu wprowadzania danych
bool WyborDanych () {
    bool daneZewn = false;
    while (true) {
        ctext::text("\n&eWybierz dane\n");
        ctext::text("&a0 &7--> &bDane z programu\n");
        ctext::text("&a1 &7--> &bDane od uzytkownika\n");
        ctext::text("&eWybor&7:&a ");
        cin>>daneZewn;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            daneZewn = false;
            ctext::text("\n&cNieprawidlowy wybor!\n");
        }
        else {
            return daneZewn;
        }
    }
    return false;
}

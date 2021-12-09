# include <iostream>
# include <math.h>
# include <vector>
# include <stdlib.h>
# pragma GCC optimize("O2")
using namespace std;
typedef vector <vector <double>> Matrix;
typedef vector <double> TAB;
bool WyborDanych ();
unsigned int WczytajDane (Matrix&);
unsigned int WczytajDomyslne (Matrix&, int);
bool Eliminacja (Matrix&, int);
bool Oblicz (Matrix, TAB&, int);
void Wyswietl (TAB, int);
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
                if (Eliminacja(Ab, n)) {
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
void Wyswietl (TAB X, int n) {
    cout<<"x = [";
    for (int i = 0; i < n; i++) {
        cout<<X[i];
        if (i < n - 1) cout<<",";
    }
    cout<<"]"<<endl;
}
bool Oblicz (Matrix Ab, TAB &X, int n) {
    if (Ab[n-1][n-1] == 0) {
        system("cls");
        cout<<"Blad w postepowaniu odwrotnym - a"<<n<<n<<" = 0"<<endl;
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
bool Eliminacja (Matrix &Ab, int n) {
    // Krok 1
    if (Ab[0][0] == 0) {
        system("cls");
        cout<<"Blad w kroku 1. eliminacji: a11 = 0"<<endl;
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
        if (Ab[k-1][k-1] == 0) {
            system("cls");
            cout<<"Blad w kroku "<<k<<". eliminacji: a"<<k<<k<<" = 0"<<endl;
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
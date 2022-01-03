# include <iostream>
# include <math.h>
# include <vector>
# include <stdlib.h>
# pragma GCC optimize("O2")
using namespace std;
typedef vector <vector <double>> Matrix;
typedef vector <double> TAB;
unsigned int wczytajDane (Matrix&, TAB&);
void Wyswietl2D (Matrix, unsigned int);
void Wyswietl1D (TAB, unsigned int);
void obliczL (unsigned int, Matrix, Matrix&);
void rozwL (unsigned int, Matrix, TAB, TAB&);
void dodajLT (unsigned int, Matrix&);
void rozwLT (unsigned int, Matrix, TAB, TAB&);
int main () {
    unsigned int n;
    Matrix A, L;
    TAB b, x, y;
    bool ok = false, daneZewn = false;
    do {
        cout<<endl<<"Wybierz dane"<<endl;
        cout<<"0 --> Dane z zadania 11.2"<<endl;
        cout<<"1 --> Dane z klawiatury"<<endl;
        cout<<"Wybor: ";
        cin>>daneZewn;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            ok = false;
            cout<<endl<<"Nieprawidlowy wybor!"<<endl;
        }
        else ok = true;
    } while (!ok);
    if (daneZewn) n = wczytajDane(A, b);
    else {
        n = 4;
        A = {{4, 6, -4, -6}, {6, 25, 6, -17}, {-4, 6, 14, 1}, {-6, -17, 1, 23}};
        b = {2, -13, -14, 5};
    }
    obliczL(n, A, L);
    cout<<endl<<"Macierz L:"<<endl;
    Wyswietl2D(L, n);
    rozwL(n, L, b, y);
    cout<<endl<<"Wektor y:"<<endl;
    Wyswietl1D(y, n);
    dodajLT(n, L);
    rozwLT(n, L, y, x);
    cout<<endl<<"Wektor x:"<<endl;
    Wyswietl1D(x, n);
    cin.ignore();
    cin.get();
    return 0;
}
void rozwLT (unsigned int n, Matrix L, TAB y, TAB &x) {
    x.resize(n);
    x[n-1] = y[n-1] / L[n-1][n-1];
    for (int k = n - 2; k >= 0; k--) {
        double s = 0.0;
        for (int j = k + 1; j < n; j++) s += (x[j] * L[k][j]);
        x[k] = (y[k] - s) / L[k][k];
    }
}
void dodajLT (unsigned int n, Matrix &L) {
    for (int k = 1; k < n; k++) {
        for (int w = 0; w < k; w++) L[w][k] = L[k][w];
    }
}
void rozwL (unsigned int n, Matrix L, TAB b, TAB &y) {
    y.resize(n);
    for (int i = 0; i < n; i++) {
        double s = 0.0;
        for (int j = 0; j < i; j++) s += (L[i][j] * y[j]);
        y[i] = (b[i] - s) / L[i][i];
    }
}
void obliczL (unsigned int n, Matrix A, Matrix &L) {
    L.resize(n);
    for (int i = 0; i < n; i++) L[i].resize(n);
    for (int k = 0; k < n; k++) {
        for (int w = 0; w < k; w++) L[w][k] = 0.0;
        for (int w = k; w < n; w++) {
            double s = 0.0;
            if (w == k) {
                for (int j = 0; j < k; j++) s += pow(L[w][j], 2.0);
                L[w][k] = sqrt(A[w][k] - s);
            }
            else {
                for (int j = 0; j < k; j++) s += (L[w][j] * L[k][j]);
                L[w][k] = (A[w][k] - s) / L[k][k];
            }
        }
    }
}
void Wyswietl2D (Matrix X, unsigned int n) {
    for (int i = 0; i < n; i++) {
        cout<<"[ ";
        for (int j = 0; j < n; j++) cout<<X[i][j]<<"\t";
        cout<<"]"<<endl;
    }
}
void Wyswietl1D (TAB T, unsigned int n) {
    cout<<"[";
    for (int i = 0; i < n; i++) {
        cout<<T[i];
        if (i < n - 1) cout<<" ; ";
    }
    cout<<"]T"<<endl;
}
unsigned int wczytajDane (Matrix &A, TAB &b) {
    unsigned int n;
    do {
        cout<<"Podaj wymiar macierzy A: ";
        cin>>n;
    } while (n < 2);
    A.resize(n);
    for (int i = 0; i < n; i++) A[i].resize(n);
    cout<<"Podaj macierz A:"<<endl;
    for (int i = 0; i < n; i++) {
        cout<<"Wiersz ["<<i+1<<"]: ";
        for (int j = 0; j < n; j++) cin>>A[i][j];
    }
    cout<<"Podaj wektor b:"<<endl;
    for (int i = 0; i < n; i++) {
        cout<<"b ["<<i<<"]: ";
        cin>>b[i];
    }
    return n;
}
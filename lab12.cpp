# include <iostream>
# include <math.h>
# include <vector>
# include <stdlib.h>
# pragma GCC optimize("O2")
# define SIGN(A) (A > 0 ? 1 : (A < 0 ? -1 : 0))
using namespace std;
typedef vector <double> Wektor;
unsigned int WczytajDane (Wektor&);
double NormaWektora (Wektor, unsigned int);
Wektor WektorE (unsigned int, double);
void Wyswietl (Wektor, unsigned int);
int main () {
    unsigned int n;
    Wektor a, e;
    double nw, t;
    n = WczytajDane(a);
    nw = NormaWektora(a, n);
    t = -SIGN(a[0]) * nw;
    e = WektorE(n, t);
    Wyswietl(e, n);
    cin.ignore();
    cin.get();
    return 0;
}
void Wyswietl (Wektor e, unsigned int n) {
    cout<<"Wektor e: [";
    for (int i = 0; i < n; i++) {
        cout<<e[i];
        if (i < n - 1) cout<<", ";
    }
    cout<<"]"<<endl;
}
Wektor WektorE (unsigned int n, double t) {
    Wektor e;
    e.resize(n);
    for (int i = 0; i < n; i++) {
        if (i == 0) e[i] = t;
        else e[i] = 0;
    }
    return e;
}
double NormaWektora (Wektor a, unsigned int n) {
    double s = 0.0;
    for (int i = 0; i < n; i++) s += pow(a[i], 2.0);
    return sqrt(s);
}
unsigned int WczytajDane (Wektor &a) {
    unsigned int n;
    do {
        cout<<"Podaj dlugosc wektora a: ";
        cin>>n;
    } while (n < 1);
    a.resize(n);
    cout<<"Podaj wektor a: ";
    for (int i = 0; i < n; i++) cin>>a[i];
    return n;
}
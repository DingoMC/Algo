# include <iostream>
# include <math.h>
using namespace std;
double silnia (int n) {
    if (n == 0) return 1;
    double w = 1;
    for (int i=1; i<=n; i++) w *= i;
    return w;
}
double Horner (double *&wsp, int st, int i, double punkt) {
    for (int j=1; j<=st-i; j++) wsp[j] = wsp[j-1] * punkt + wsp[j];
    return wsp[st-i] * silnia(i);
}
void zadanie_2_1() {
    unsigned int st;
    do {
        cout<<"Podaj stopien wielomianu: ";
        cin>>st;
    } while (st < 1);
    double *wsp = new double[st+1];
    for (int i=0; i<st+1; i++) {
        cout<<"Podaj wspolczynnik przy x^"<<st-i<<": ";
        cin>>wsp[i];
    }
    double punkt;
    cout<<"Punkt, w ktorym liczona bedzie wartosc wielomianu: ";
    cin>>punkt;
    double wynik = wsp[0];
    for (int i=1; i<=st; i++) wynik = wynik * punkt + wsp[i];
    cout<<"Wartosc wielomianu w punkcie x = "<<punkt<<": "<<wynik<<endl;
    double *pochodna = new double[st+1];
    for (int i=0; i<=st; i++) pochodna[i] = Horner(*&wsp, st, i, punkt);
    for (int i=0; i<=st; i++) cout<<"Wartosc pochodnej("<<i<<") w punkcie x = "<<punkt<<": "<<pochodna[i]<<endl;
}
int main () {
    bool exit = false;
    unsigned int menu = 1;
    while (!exit) {
        cout<<"Wybierz opcje:\n1 --> Zadanie 2.1\n2 --> Wyjscie z programu\nWybor: ";
        cin>>menu;
        cout<<endl;
        switch (menu) {
            case 1: {
                zadanie_2_1();
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

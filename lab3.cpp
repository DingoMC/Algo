# include <iostream>
# include <math.h>
# include <vector>
using namespace std;
double wfl (int i, double *ww, int lw, double p) {
    double wynik = 1.0;
    for (int k=0; k<lw; k++) {
        if (k != i) wynik *= ((p - ww[k]) / (ww[i] - ww[k]));
    }
    return wynik;
}
void zadanie_3_1() {
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
    double wynik = 0.0;
    for (int i=0; i<lw; i++) {
        wynik += (wfw[i] * wfl(i, *&ww, lw, p));
    }
    cout<<"Wartosc w punkcie x = "<<p<<": "<<wynik<<endl;
}
vector <double> MulPolynomialBinomial (vector <double> PN_Coeff, int PNC_Count, double BI_A, double BI_B) {
    vector <double> PN_New;
    PN_New.resize(PNC_Count + 1);
    PN_New[PNC_Count] = BI_A * PN_Coeff[PNC_Count-1];
    for (int i = PNC_Count - 1; i >= 1; i--) PN_New[i] = BI_B * PN_Coeff[i] + BI_A * PN_Coeff[i-1];
    PN_New[0] = PN_Coeff[0] * BI_B;
    return PN_New;
}
vector <double> CountWFL(int i, double *ww, int lw) {
    vector <double> WFL_Coeff;
    WFL_Coeff.resize(lw);
    bool init = false;
    int cnt = 1;
    WFL_Coeff[0] = 1;
    for (int k = 0; k < lw; k++) {
        if (k != i) {
            WFL_Coeff = MulPolynomialBinomial(WFL_Coeff, cnt, 1.0 / (ww[i] - ww[k]), (-ww[k]) / (ww[i] - ww[k]));
            cnt++;
        }
    }
    return WFL_Coeff;
}
void zadanie_3_2() {
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
    vector <double> W;
    W.resize(lw);
    for (int i = 0; i < lw; i++) W[i] = 0.0;
    vector <vector <double>> L;
    L.resize(lw);
    for (int i = 0; i < lw; i++) {
        L[i].resize(lw);
        L[i] = CountWFL(i, *&ww, lw);
        for (int j = 0; j < lw; j++) {
            L[i][j] *= wfw[i];
            W[j] += L[i][j];
        }
    }
    for (int i = lw - 1; i >= 0; i--) {
        if (W[i] != 0) {
            if (i < lw - 1) cout<<" + ";
            if (W[i] > 0) {
                if (W[i] != 1) cout<<W[i];
            }
            else cout<<"("<<W[i]<<")";
            if (i > 0) cout<<"x";
            if (i > 1) cout<<"^"<<i;
        }
    }
    cout<<endl;
}
int main () {
    bool exit = false;
    unsigned int menu = 1;
    while (!exit) {
        cout<<"Wybierz opcje:\n1 --> Zadanie 3.1\n2 --> Zadanie 3.2\n3 --> Wyjscie z programu\nWybor: ";
        cin>>menu;
        cout<<endl;
        switch (menu) {
            case 1: {
                zadanie_3_1();
                cout<<endl;
                break;
            }
            case 2: {
                zadanie_3_2();
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

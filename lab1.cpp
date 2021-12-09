# include <iostream>
# include <math.h>
# include <vector>
using namespace std;
float signum (double);
void zadanie_1_1 () {
    int liczba = 0;
    cout<<"Podaj liczbe w systemie dziesietnym: ";
    cin>>liczba;
    int podst = 2;
    do {
        cout<<"Podaj podstawe systemu (2 ~ 10): ";
        cin>>podst;
    } while (podst < 2 || podst > 10);
    vector <unsigned int> wynik;
    unsigned int licznik = 0;
    while (liczba > 0) {
        licznik++;
        wynik.resize(licznik);
        wynik[licznik-1] = liczba % podst;
        liczba /= podst;
    }
    cout<<"Wynik w systemie ("<<podst<<"): ";
    for (int i=licznik-1; i>=0; i--) cout<<wynik[i];
    cout<<endl;
}
void zadanie_1_2 () {
    double a, b, c, x1, x2;
    cout<<"Podaj wspolczynniki rownania kwadratowego:\nPodaj a: ";
    cin>>a;
    cout<<"Podaj b: ";
    cin>>b;
    cout<<"Podaj c: ";
    cin>>c;
    x1 = (-b - sqrt(pow(b, 2.0) - 4.0 * a * c)) / (2.0 * a);
    x2 = (-b + sqrt(pow(b, 2.0) - 4.0 * a * c)) / (2.0 * a);
    cout<<"Pierwiastki obliczone wzorami \"klasycznymi\": "<<x1<<", "<<x2<<endl;
    x1 = (-b) / (2.0 * a) + signum((-b) / (2.0 * a)) * sqrt(pow(b / (2.0 * a), 2.0) - (c / a));
    x2 = c / (a * x1);
    cout<<"Pierwiastki obliczone wzorami Viete\'a: "<<x1<<", "<<x2<<endl;
}
int main () {
    bool exit = false;
    unsigned int menu = 1;
    while (!exit) {
        cout<<"Wybierz opcje:\n1 --> Zadanie 1.1\n2 --> Zadanie 1.2\n3 --> Wyjscie z programu\nWybor: ";
        cin>>menu;
        cout<<endl;
        switch (menu) {
            case 1: {
                system("cls");
                zadanie_1_1();
                cout<<endl;
                break;
            }
            case 2: {
                system("cls");
                zadanie_1_2();
                cout<<endl;
                break;
            }
            case 3: {
                exit = true;
                system("cls");
                cout<<"Do widzenia!"<<endl;
                break;
            }
            default: {
                system("cls");
                cout<<"Nieprawidlowy wybor!"<<endl;
                break;
            }
        }
    }
    cin.ignore();
    cin.get();
    return 0;
}
float signum (double n) {
    if (n > 0) return 1.0;
    if (n == 0) return 0.0;
    return -1.0;
}
#include <iostream>
#include <math.h>
#define PI 3.141592653589793238462
using namespace std;
/*
(1/(2x-3))^3
*/
float czebyszew(int w) {
    float suma = 0.0;
    for (int i = 0; i <= w; i++) {
        float x = cos(2.0 * i + 1.0) * PI / (2.0 * (w + 1.0));
        float f = pow((1.0 / (2.0 * x - 3.0)), 3.0);
        float H = PI / (w + 1);
        suma += (H * f);
    }
    return suma;
}
int main () {
    cout<<czebyszew(10)<<endl;
    cin.ignore();
    cin.get();
    return 0;
}

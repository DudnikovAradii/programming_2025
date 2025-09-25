#include <iostream>
#include <cmath> //подключение math дл€ использовани€ функции pow
using namespace std;


int main() {
    int A, B, C;
    cin >> A; // как input в питоне
    cin >> B; // как input в питоне
    cin >> C; // как input в питоне
    float P; //созданиеи числа с плавующей точкой с помощью float
    P = (A + B + C) / 2.0; // »щем полупериметр треугольника
    float S; //созданиеи числа с плавующей точкой с помощью float
    S= P * (P - A) * (P - B) * (P - C); // формула герона без корн€
    float ROOT; //созданиеи числа с плавующей точкой с помощью float
    ROOT = pow(S, 0.5); // с помощью pow ищем степень 0.5 числа (квадратный корень)

    cout << ROOT << endl;
    cout << "int " << "32 bits, " << -2147483648 << 2147483647 << endl;
    cout << "float " << "32 bits, " << -3.4E-38 << 3.4E+38 << endl;


    return 0;
}
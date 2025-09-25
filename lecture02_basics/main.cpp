#include <iostream>
#include <cmath> //подключение math для использования функции pow
using namespace std;


int main() {
    int A, B, C;
    cin >> A; // как input в питоне
    cin >> B; // как input в питоне
    cin >> C; // как input в питоне
    float P; //созданиеи числа с плавующей точкой с помощью float
    P = (A + B + C) / 2.0; // Ищем полупериметр треугольника
    float S; //созданиеи числа с плавующей точкой с помощью float
    S = pow((P * (P - A) * (P - B) * (P - C)), 0.5); // формула герона

    setlocale(LC_ALL, ""); // Функция для корректного использования русских букв 
    cout << "Площадь треугольника: " << S << " float" << endl; // вывод переменных
    cout << "int " << "32 bits, " << -2147483648 << " " << 2147483647 << endl;
    cout << "float " << "32 bits, " << -3.4E-38 << " " << 3.4E+38 << endl;


    return 0;
}
#include <iostream>
#include <cmath> //подключение math для использования функции pow
using namespace std;


int main() {
    int A, B, C; // вводим переменные A, B, C
    cin >> A; // как input в питоне
    cin >> B; // как input в питоне
    cin >> C; // как input в питоне
    float P; //созданиеи числа с плавующей точкой с помощью float
    P = (A + B + C) / 2.0; // Ищем полупериметр треугольника
    float S; //созданиеи числа с плавующей точкой с помощью float
    S = pow((P * (P - A) * (P - B) * (P - C)), 0.5); // формула герона

    setlocale(LC_ALL, "Russian"); // Функция для корректного использования русских букв 
    cout << "Площадь треугольника: " << S << " float" << endl; // вывод переменных
    cout << "int " << sizeof(int) * 8<< " бита, " << "от " << numeric_limits<int>::min() << " до " << numeric_limits<int>::max() << endl;
    cout << "float " << sizeof(int) * 8 << " бита, " << "от " << numeric_limits<float>::lowest() << " до " << numeric_limits<float>::max() << endl;


    return 0;
}
/*kaskdfkfa
osdfgpsgdp*/
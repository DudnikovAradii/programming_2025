#include <iostream>
#include <cmath>
using namespace std;
// Функция для склеивания двух чисел
int skleitDvaChisla(int a, int b) {
    cout << "исп. функция склеивания 2х чисел" << endl;
    // Находим количество цифр во втором числе
    int temp = b;
    int count = 1;
    while (temp >= 10) {
        temp /= 10;
        count *= 10;
    }
    // Склеиваем числа: a * (10 в степени количество_цифр_b) + b
    return a * (count * 10) + b;
}
// Функция для нахождения противоположного числа
int skleitDvaChisla(int a) {
    cout << "исп. функция противоположного числа" << endl;
    return -a;
}
// Функция для трех чисел (площадь треугольника по формуле Герона)
void ploshadTreugolnika(int a, int b, int c) {
    cout << "исп. функция площади треугольника по формуле Герона" << endl;
    double p = (a + b + c) / 2.0;
    double S = sqrt(p * (p - a) * (p - b) * (p - c));
    double result = S;
    cout << "Результат: " << result << endl;
}
int main() {
    setlocale(LC_ALL, "Russian");
    int vibor;
    cout << "Выберите пункт для выполнения (1 или 2): ";
    cin >> vibor;
    if (vibor == 1) {
        cout << "=== Пункт 1 ===" << endl;
        int num1, num2, num3;
        cout << "Введите три числа (если число = 0, считаем что его нет): ";
        cin >> num1 >> num2 >> num3;
        // Определяем количество ненулевых чисел
        int count = 0;
        if (num1 != 0) count++;
        if (num2 != 0) count++;
        if (num3 != 0) count++;

        int result;

        if (count == 2) {
            // Определяем какие именно два числа ненулевые
            if (num1 != 0 && num2 != 0) {
                result = skleitDvaChisla(num1, num2);
                cout << "Результат склеивания " << num1 << " и " << num2 << ": " << result << endl;
            }
            else if (num1 != 0 && num3 != 0) {
                result = skleitDvaChisla(num1, num3);
                cout << "Результат склеивания " << num1 << " и " << num3 << ": " << result << endl;
            }
            else {
                result = skleitDvaChisla(num2, num3);
                cout << "Результат склеивания " << num2 << " и " << num3 << ": " << result << endl;
            }
        }
        else if (count == 1) {
            // Определяем какое именно число ненулевое
            if (num1 != 0) {
                result = skleitDvaChisla(num1);
                cout << "Противоположное число для " << num1 << ": " << result << endl;
            }
            else if (num2 != 0) {
                result = skleitDvaChisla(num2);
                cout << "Противоположное число для " << num2 << ": " << result << endl;
            }
            else {
                result = skleitDvaChisla(num3);
                cout << "Противоположное число для " << num3 << ": " << result << endl;
            }
        }
        else {
            cout << "Все числа нулевые или больше 2 чисел" << endl;
        }
    }
    else if (vibor == 2) {
        cout << "=== Пункт 2 ===" << endl;
        int a, b, c;
        cout << "Введите три стороны треугольника: ";
        cin >> a >> b >> c;
        // Проверяем корректность ввода
        if (a <= 0 || b <= 0 || c <= 0) {
            cout << "Ошибка: стороны треугольника должны быть положительными числами!" << endl;
            return 1;
        }
        ploshadTreugolnika(a, b, c);
    }
    else {
        cout << "Неверный выбор. Должено быть 1 или 2" << endl;
        return 1;
    }
    return 0;
}

#include <iostream>
#include <bitset>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    short A;
    cout << "Число А: ";
    cin >> A;
    short i;
    cout << "Введите номер бита i (0-7): ";
    cin >> i;
    if (i < 0 || i > 7) {
        cout << "Ошибка: номер бита должен быть от 0 до 7" << endl;
        return 1;
    }
    bitset<8> b2 = A;
    cout << "Двоичное представление числа A: " << b2.to_string() << endl;
    int bitI = (A >> i) & 1;
    cout << "i элемент: " << bitI << endl;
    if (bitI == 0) {
        int result = A * A;
        result = result & ~(1 << i);
        bitset<32> result2 = result;
        cout << "Результат A^2 с установленным в 0 битом i в 10-ой СС: " << result<< "," << " в 2-ой СС: " << result2.to_string() << endl;
    }
    else {
        short number = 125;
        bitset<8> number2 = number;
        int chet = 170; // в двоичном виде выглядит как 10101010 (при конъюнкцию с числом заменяет все четные биты на нули)
        short result = number & chet;
        bitset<8> result2 = result;
        cout << "Исходное число: " << number << ", в двоичном виде: " << number2.to_string() << endl;
        cout << "После замены четных битов на 0: " << result << ", в двоичном виде: " << result2.to_string() << endl;
    }

}
// Number 2
/*
int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Введите номер рейсового автобуса ";
    cin >> n;
    switch (n)
    {
    case 113:
        cout << "КАЛИНИНГРАД – ЧАПАЕВО" << endl;
        break;
    case 114:
        cout << "КАЛИНИНГРАД - ЗЕЛЕНОГРАДСК" << endl;
        break;
    case 117:
        cout << "КАЛИНИНГРАД - МАМОНОВО" << endl;
        break;
    case 118:
        cout << "КАЛИНИНГРАД - СВЕТЛОГОРСК" << endl;
        break;
    case 119:
        cout << "КАЛИНИНГРАД - ПИОНЕРСКИЙ" << endl;
        break;
    case 125:
        cout << "КАЛИНИНГРАД - ДОНСКОЕ" << endl;
        break;
    case 139:
        cout << "КАЛИНИНГРАД - ПАРТИЗАНСКОЕ" << endl;
        break;
    case 141:
        cout << "КАЛИНИНГРАД - ЗЕЛЕНОГРАДСК" << endl;
        break;
    case 148:
        cout << "КАЛИНИНГРАД - БАГРАТИОНОВСК" << endl;
        break;
    case 161:
        cout << "КАЛИНИНГРАД - СВЕТЛОЕ" << endl;
        break;
    case 191:
        cout << "КАЛИНИНГРАД - БАГРАТИОНОВСК" << endl;
        break;
    case 593:
        cout << "КАЛИНИНГРАД - МОРСКОЕ" << endl;
        break;
    case 802:
        cout << "КАЛИНИНГРАД - ГДАНЬСК" << endl;
        break;
    default:
        cout << "Такого автобуса нет!" << endl;
        break;
    }
}
*/
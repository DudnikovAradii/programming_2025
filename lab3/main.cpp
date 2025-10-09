#include <iostream>]
using namespace std;
int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Колличество элементов последовательность: ";
    int N;
    std::cin >> N;
    int countN = 0;
    int product = 0;
    int max = -2147483648;
    int minNumCnt = -1;
    for (N; N > 0; --N) {
        ++countN;
        std::cout << "Введите " << countN << " номер последовательности: ";
        int num;
        std::cin >> num;
        if ((num % 3 != 0) && (num % 5 != 0) && (num % 7 != 0)) {
            product = product + num;
            if (num > max) {
                max = num;
                minNumCnt = countN;
            }
        }
    }
    if (minNumCnt != -1) {
        cout << "Сумма всех подходящих чисел = " << product << std::endl;
        cout << "Максимальный подходящий элемент последовательности = " << max << std::endl;
        cout << "Номер максимального элемента последовательности = " << minNumCnt << std::endl;
        std::cout << "Крнец" << std::endl;
    }
    else {
        std::cout << "Нет подходящих элементов" << std::endl;
        std::cout << "Конец" << std::endl;
    } 
    // Задание 2
    /*
    std::cout << "Введите номер ";
    short num;
    int сuntRazrd = 0;
    std::cin >> num;
    short num1;
    num1 = abs(num);
    if(num1 > 1000) {
        std::cout << "Ошибка: |x| > 1000" << std::endl;
        return 1;
    }
    else if (num == 0) {
        cout << "Число: 0" << endl;
        cout << "Количество разрядов: 1" << endl;
        cout << "Первая цифра: 0" << endl;
        return 0;
    }
    else {
        while (num1 > 0) {
            сuntRazrd++;
            num1 /= 10;
        }
    }
    int firstnum = abs(num);
    while (firstnum >= 10) {
        firstnum /= 10;
    }
    cout << "Число: " << num << endl;
    cout << "Количество разрядов: " << сuntRazrd << endl;
    cout << "Первая цифра: " << firstnum << endl;
    */
}
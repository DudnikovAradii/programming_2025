#include <iostream>
using namespace std;
int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Введите количество чисел в последовательности: ";
    cin >> n;
    int total_sum = 0;
    int max_number = 0;
    int max_index = -1;
    int count = 0;
    bool found = false;

    cout << "Введите числа последовательности:" << endl;
    for (int i = 1; i <= n; i++) {
        int num;
        cout << "A" << i << " = ";
        cin >> num;
        if (num % 3 != 0 && num % 5 != 0 && num % 7 != 0) {
            total_sum += num;
            count++;
            if (num > max_number || !found) {
                max_number = num;
                max_index = i;
                found = true;
            }
        }
    }
    if (count == 0) {
        cout << "В последовательности нет подходящих чисел" << endl;
    }
    else {
        cout << "Сумма чисел, не кратных 3, 5 и 7: " << total_sum << endl;
        cout << "Наибольшее число: " << max_number << endl;
        cout << "Номер этого числа в последовательности: " << max_index << endl;
        cout << "Количество подходящих чисел: " << count << endl;
    }
    return 0;

    // Задание 2
  
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
    
}

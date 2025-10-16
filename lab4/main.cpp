#include <iostream>
#include <cmath>


int main() {
    using namespace std;
    setlocale(LC_ALL, "Russian");

    /*
    // Задание 1

    int x[9];
    for (int i = 0; i < 9; ++i) {
        cout << i + 1 << " Элемент массива: ";
        cin >> x[i];
    }
    cout << "Исходный массив: ";
    for (int i = 0; i < 9; i++) {
        cout << x[i] << " ";
    }
    cout << endl;

    bool Three = false;

    for (int i = 0; i < 9; i++) {
        int num = abs(x[i]);

        int firstDigit = num;
        while (firstDigit >= 10) {
            firstDigit = firstDigit / 10;
        }

        // Проверяем, равна ли первая цифра 3
        if (firstDigit == 3) {
            Three = true;
            break; // выходим из цикла, так как достаточно одного числа
        }
    }

    // Сортировка массива, если есть число, начинающееся с 3
    if (Three) {
        cout << "В массиве есть число, начинающееся с 3. Сортируем массив" << endl;

        for (int i = 0; i < 8; ++i) {
            for (int j = i + 1; j < 9; ++j) {                  // Упорядочивание массива
                if (x[i] > x[j]) {
                    std::swap(x[i], x[j]);
                }
            }
        }
    
    for (int i = 0; i < 9; ++i) {
        std::cout << x[i] << " ";
    }
    cout << "Конец" << std::endl;
    }
    else {
        cout << "В массиве нет чисел, начинающихся с 3. Сортировка не выполняется." << endl;
    }

    return 0; 
 */

  // Задание 2

    int f[3][4];

    for (int i = 0; i < 3; i++) {
        cout << "Строка " << i + 1 << " 4 числа: ";
        for (int j = 0; j < 4; j++) {
            cin >> f[i][j];
        }
    }
        
  

    // Поиск строки с максимально отдаленной от 0 суммой элементов
    int maxdistance = -1;
    int stroka = -1;

    for (int i = 0; i < 3; i++) {
        int Summ = 0;
        // Вычисляем сумму элементов строки
        for (int j = 0; j < 4; j++) {
            Summ += f[i][j];
        }

        // Вычисляем расстояние от 0
        int distance = abs(Summ);

        // Если нашли большее расстояние обновляем результат
        if (distance > maxdistance) {
            maxdistance = distance;
            stroka = i;
        }
    }
    // Замена всех значений в найденной строке на 999
    for (int j = 0; j < 4; j++) {
        f[stroka][j] = 999;
    }
    // Вывод результата
    cout << "Строка с максимально отдаленной от 0 суммой: "
        << stroka + 1 << endl;

    cout << "Конечная матрица:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << f[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

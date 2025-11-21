#include <iostream>

using namespace std;

void matrixResult(int top, int left, int** mas) {
    // Просто выводим матрицу
    for (int i = 0; i < top; i++) {
        for (int j = 0; j < left; j++) {
            cout << mas[i][j] << " ";
        }
        cout << endl;
    }
}

void removeZeroRows(int**& mas, int& top, int left) {
    int coZ = 0;
    int* zeroRow = 0;
    // Есть ли нули в строке или нет (если есть хоть 1 нолик, то переходим на следующую строку)
    for (int i = 0; i < top; i++) {
        for (int j = 0; j < left; j++) {
            if (mas[i][j] == 0) {
                coZ++;
                break;
            }
        }
    }

    // Выделяем память для coZ значений, туда мы поместим индексы строк, которые содержат нули.
    if (coZ > 0) {
        zeroRow = (int*)malloc(coZ * sizeof(int));
        int index = 0;
        for (int i = 0; i < top; i++) {
            for (int j = 0; j < left; j++) {
                if (mas[i][j] == 0) {
                    zeroRow[index] = i;
                    index++;
                    break;
                }
            }
        }

        cout << "Строки с нулями: ";
        for (int i = 0; i < coZ; i++) {
            cout << zeroRow[i] << " ";
        }
        cout << endl;

        // Удаляем строки с нулями из исходного массива
        int newTop = top;
        for (int i = 0; i < newTop; i++) {
            bool flZ = false;

            // Проверяем, есть ли в строке нули
            for (int j = 0; j < left; j++) {
                if (mas[i][j] == 0) {
                    flZ = true;
                    break;
                }
            }

            // Если нашли строку с нулем, удаляем её
            if (flZ) {
                free(mas[i]);

                // Сдвигаем все последующие строки на одну позицию вверх
                for (int k = i; k < newTop - 1; k++) {
                    mas[k] = mas[k + 1];
                }
                newTop--;
                i--;
            }
        }

        // Изменяем размер массива указателей
        if (newTop < top) {
            mas = (int**)realloc(mas, newTop * sizeof(int*));
            top = newTop;
        }

        // Выводим результат после удаления строк с нулями
        for (int i = 0; i < top; i++) {
            for (int j = 0; j < left; j++) {
                cout << mas[i][j] << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    // создаём 2-х мерный массив с помощью 2-х указателей
    int** mas = (int**)malloc(2 * sizeof(int*));

    for (int i = 0; i < 2; i++) {
        mas[i] = (int*)malloc(2 * sizeof(int));
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> mas[i][j];
            if (i == 0 && mas[i][j] < 0) {
                int fl = 1;
                while (fl == 1) {
                    cout << "Введите новое НЕ отрицательное число: ";
                    cin >> mas[i][j];
                    if (mas[i][j] >= 0) {
                        fl = 0;
                    }
                }
            }
        }
    }

    int A = mas[0][0];
    int B = mas[0][1];
    int C = mas[1][0];
    int D = mas[1][1];

    int top = 2 + A;
    int left = 2 + B;

    // расширяю массив с помощью функции realloc
    mas = (int**)realloc(mas, top * sizeof(int*));

    for (int i = 2; i < top; i++) {
        mas[i] = (int*)malloc(left * sizeof(int));
    }

    // сохраняю данные и заполняем матрицу
    int old_block[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            old_block[i][j] = mas[i][j];
        }
    }

    // Расширяем существующие строки 0 и 1
    for (int i = 0; i < 2; i++) {
        mas[i] = (int*)realloc(mas[i], left * sizeof(int));
    }

    // Заполняем ВСЮ матрицу формулой
    for (int i = 0; i < top; i++) {
        for (int j = 0; j < left; j++) {
            mas[i][j] = i * C + j * D;
        }
    }

    // Восстанавливаем исходный блок в правом нижнем углу
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            mas[i + A][j + B] = old_block[i][j];
        }
    }

    matrixResult(top, left, mas);

    removeZeroRows(mas, top, left);

    // Освобождаем память
    for (int i = 0; i < top; i++) {
        free(mas[i]);
    }
    free(mas);

    return 0;
}
/*int a1, b1;
std::cout << "Введите A:" << std::endl;
std::cin >> a1;
std::cout << "Введите B:" << std::endl;
std::cin >> b1;

std::cout << "A: " << a1 << std::endl;
std::cout << "B: " << b1 << std::endl;

int* pa1 = new int(a1);
int* pb1 = new int(b1);

*pa1 *= 2;
a1 = *pa1;
std::cout << "новое A: " << a1 << std::endl;

int temp = *pa1;
*pa1 = *pb1;
*pb1 = temp;

a1 = *pa1;
b1 = *pb1;

std::cout << "A: " << a1 << std::endl;
std::cout << "B: " << b1 << std::endl;

delete pa1;
delete pb1;
*/

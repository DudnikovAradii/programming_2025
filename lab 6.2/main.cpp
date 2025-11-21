#include <iostream>

using namespace std;

// Функция для поиска строк с нулями
// Функция для поиска строк с нулями
int* findZeroRows(int** ukazatel, int kolichestvoStrok, int kolichestvoStolbtsov, int& schetchik) {
    schetchik = 0;

    // Первый проход: подсчитываем строки с нулями
    for (int nomerStroki = 0; nomerStroki < kolichestvoStrok; nomerStroki++) {
        bool naydenNol = false;
        for (int nomerStolbtsa = 0; nomerStolbtsa < kolichestvoStolbtsov; nomerStolbtsa++) {
            if (ukazatel[nomerStroki][nomerStolbtsa] == 0) {
                naydenNol = true;
                break;
            }
        }
        if (naydenNol) {
            schetchik++;
        }
    }

    // Выделяем память для результата
    int* strokiSNulyami = (int*)malloc(schetchik * sizeof(int));

    // заполняем массив индексами строк с нулями
    int tekushchiyIndex = 0;
    for (int nomerStroki = 0; nomerStroki < kolichestvoStrok; nomerStroki++) {
        for (int nomerStolbtsa = 0; nomerStolbtsa < kolichestvoStolbtsov; nomerStolbtsa++) {
            if (ukazatel[nomerStroki][nomerStolbtsa] == 0) {
                strokiSNulyami[tekushchiyIndex] = nomerStroki;
                tekushchiyIndex++;
                break;
            }
        }
    }

    return strokiSNulyami;
}

void matrixResult(int**& massiv, int& stroki, int stolbtsy) {
    // Сначала выводим исходную матрицу
    cout << "Исходная матрица:" << endl;
    for (int i = 0; i < stroki; i++) {
        for (int j = 0; j < stolbtsy; j++) {
            cout << massiv[i][j] << " ";
        }
        cout << endl;
    }

    // Используем функцию findZeroRows для поиска строк с нулями
    int schetchikNuley = 0;
    int* strokiSNulyami = findZeroRows(massiv, stroki, stolbtsy, schetchikNuley);

    // Если есть строки с нулями
    if (schetchikNuley > 0) {
        cout << "Строки с нулями: ";
        for (int i = 0; i < schetchikNuley; i++) {
            cout << strokiSNulyami[i] << " ";
        }
        cout << endl;

        // Удаляем строки с нулями
        int novyeStroki = stroki;
        for (int i = 0; i < novyeStroki; i++) {
            bool estNol = false;

            // Проверяем, есть ли в строке нули
            for (int j = 0; j < stolbtsy; j++) {
                if (massiv[i][j] == 0) {
                    estNol = true;
                    break;
                }
            }

            // Если нашли строку с нулем, удаляем её
            if (estNol) {
                free(massiv[i]);

                // Сдвигаем все последующие строки на одну позицию вверх
                for (int k = i; k < novyeStroki - 1; k++) {
                    massiv[k] = massiv[k + 1];
                }
                novyeStroki--;
                i--;
            }
        }

        // Изменяем размер массива указателей
        if (novyeStroki < stroki) {
            massiv = (int**)realloc(massiv, novyeStroki * sizeof(int*));
            stroki = novyeStroki;
        }

        // Выводим результат после удаления строк с нулями
        cout << "Матрица после удаления строк с нулями:" << endl;
        for (int i = 0; i < stroki; i++) {
            for (int j = 0; j < stolbtsy; j++) {
                cout << massiv[i][j] << " ";
            }
            cout << endl;
        }

        free(strokiSNulyami);
    }
    else {
        cout << "Строк с нулями не найдено" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Ru");
    // создаём 2-х мерный массив с помощью 2-х указателей
    int** massiv = (int**)malloc(2 * sizeof(int*));

    for (int i = 0; i < 2; i++) {
        massiv[i] = (int*)malloc(2 * sizeof(int));
    }

    // Заполняем матрицу с проверкой на отрицательные числа в первой строке
    cout << "Введите 4 числа для матрицы 2x2:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << (i == 0 ? "Первая строка (A и B): " : "Вторая строка (C и D): ");
        for (int j = 0; j < 2; j++) {
            while (true) {
                cin >> massiv[i][j];
                if (i != 0 || massiv[i][j] >= 0) break;
                cout << "A и B должны быть неотрицательными. Повторите ввод: ";
            }
        }
    }
    // Сохраняем исходные значения матрицы
    int A = massiv[0][0];
    int B = massiv[0][1];
    int C = massiv[1][0];
    int D = massiv[1][1];

    // Вычисляем новые размеры матрицы
    int stroki = 2 + A;
    int stolbtsy = 2 + B;

    // Расширяем массив с помощью функции realloc
    massiv = (int**)realloc(massiv, stroki * sizeof(int*));

    // Выделяем память для новых строк
    for (int i = 2; i < stroki; i++) {
        massiv[i] = (int*)malloc(stolbtsy * sizeof(int));
    }

    // Сохраняем исходный блок 2x2
    int ishodnyyBlok[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            ishodnyyBlok[i][j] = massiv[i][j];
        }
    }

    // Расширяем существующие строки 0 и 1
    for (int i = 0; i < 2; i++) {
        massiv[i] = (int*)realloc(massiv[i], stolbtsy * sizeof(int));
    }

    // Заполняем ВСЮ матрицу формулой
    for (int i = 0; i < stroki; i++) {
        for (int j = 0; j < stolbtsy; j++) {
            massiv[i][j] = i * C + j * D;
        }
    }

    // Восстанавливаем исходный блок в правом нижнем углу
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            massiv[i + A][j + B] = ishodnyyBlok[i][j];
        }
    }

    // Используем объединённую функцию для обработки матрицы
    matrixResult(massiv, stroki, stolbtsy);

    // Освобождаем память
    for (int i = 0; i < stroki; i++) {
        free(massiv[i]);
    }
    free(massiv);

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

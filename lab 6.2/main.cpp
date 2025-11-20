#include <iostream>

using namespace std;

/*
void matrixResult(int stroki, int stolbtsy, int** matritsa) {
    int kolichestvoNulevyhStrok = 0;

    // Подсчет количества строк, содержащих нули
    for (int i = 0; i < stroki; i++) {
        for (int j = 0; j < stolbtsy; j++) {
            if (matritsa[i][j] == 0) {
                kolichestvoNulevyhStrok++;
                break; // Переходим к следующей строке
            }
        }
    }

    if (kolichestvoNulevyhStrok > 0) {
        // Создаем массив для хранения номеров строк с нулями
        int* massivNulevyhStrok = (int*)malloc(kolichestvoNulevyhStrok * sizeof(int));
        int indeks = 0;

        // Заполняем массив номерами строк с нулями
        for (int i = 0; i < stroki; i++) {
            for (int j = 0; j < stolbtsy; j++) {
                if (matritsa[i][j] == 0) {
                    massivNulevyhStrok[indeks] = i;
                    indeks++;
                    break;
                }
            }
        }

        // Выводим номера строк с нулями
        cout << "Строки с нулями: ";
        for (int i = 0; i < kolichestvoNulevyhStrok; i++) {
            cout << massivNulevyhStrok[i] << " ";
        }
        cout << endl;

        // Создаем новую матрицу без строк с нулями
        int novyeStroki = stroki - kolichestvoNulevyhStrok;
        int** novayaMatritsa = (int**)malloc(novyeStroki * sizeof(int*));
        int novyyIndeks = 0;

        // Копируем только строки без нулей
        for (int i = 0; i < stroki; i++) {
            int udalit = 0;
            // Проверяем, нужно ли удалять текущую строку
            for (int k = 0; k < kolichestvoNulevyhStrok; k++) {
                if (i == massivNulevyhStrok[k]) {
                    udalit = 1;
                    break;
                }
            }

            // Если строка без нулей - копируем ее
            if (udalit == 0) {
                novayaMatritsa[novyyIndeks] = (int*)malloc(stolbtsy * sizeof(int));
                for (int j = 0; j < stolbtsy; j++) {
                    novayaMatritsa[novyyIndeks][j] = matritsa[i][j];
                }
                novyyIndeks++;
            }
        }

        // Выводим результат
        cout << "Матрица после удаления строк с нулями:" << endl;
        for (int i = 0; i < novyeStroki; i++) {
            for (int j = 0; j < stolbtsy; j++) {
                cout << novayaMatritsa[i][j] << " ";
            }
            cout << endl;
        }

        // Освобождаем память новой матрицы
        for (int i = 0; i < novyeStroki; i++) {
            free(novayaMatritsa[i]);
        }
        free(novayaMatritsa);
        free(massivNulevyhStrok);
    }
    else {
        // Если нулей нет - выводим исходную матрицу
        cout << "Строки с нулями не найдены..." << endl;
        cout << "Исходная матрица:" << endl;
        for (int i = 0; i < stroki; i++) {
            for (int j = 0; j < stolbtsy; j++) {
                cout << matritsa[i][j] << " ";
            }
            cout << endl;
        }
    }
}
*/
int main() {
    
    setlocale(LC_ALL, "Russian");
    /*
    // Выделение памяти для исходной матрицы 2x2
    int** matritsa = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        matritsa[i] = (int*)malloc(2 * sizeof(int));
    }

    // Ввод данных с проверкой неотрицательности для A и B
    cout << "Введите 4 числа для матрицы 2x2:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << (i == 0 ? "Первая строка (A и B): " : "Вторая строка (C и D): ");
        for (int j = 0; j < 2; j++) {
            while (true) {
                cin >> matritsa[i][j];
                if (i != 0 || matritsa[i][j] >= 0) break;
                cout << "A и B должны быть неотрицательными. Повторите ввод: ";
            }
        }
    }

    // Сохраняем значения A, B, C, D
    int A = matritsa[0][0];
    int B = matritsa[0][1];
    int C = matritsa[1][0];
    int D = matritsa[1][1];

    // Вычисляем новые размеры матрицы
    int stroki = 2 + A;
    int stolbtsy = 2 + B;

    // Увеличиваем матрицу до новых размеров
    matritsa = (int**)realloc(matritsa, stroki * sizeof(int*));
    for (int i = 2; i < stroki; i++) {
        matritsa[i] = (int*)malloc(stolbtsy * sizeof(int));
    }

    // Обрабатываем существующие строки (0 и 1)
    for (int i = 0; i < 2; i++) {
        int staryeZnacheniya[2];
        // Сохраняем исходные значения
        for (int j = 0; j < 2; j++) {
            staryeZnacheniya[j] = matritsa[i][j];
        }

        // Расширяем строку и заполняем по формуле
        matritsa[i] = (int*)realloc(matritsa[i], stolbtsy * sizeof(int));
        for (int j = 0; j < stolbtsy; j++) {
            matritsa[i][j] = i * C + j * D;
        }

        // Восстанавливаем исходные значения в новых позициях
        for (int j = 0; j < 2; j++) {
            matritsa[i][j + B] = staryeZnacheniya[j];
        }
    }

    // Заполняем новые строки (начиная с 2) по формуле
    for (int i = 2; i < stroki; i++) {
        for (int j = 0; j < stolbtsy; j++) {
            matritsa[i][j] = i * C + j * D;
        }
    }

    // Сохраняем угловые элементы перед перемещением
    int** sohranennyeElementy = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        sohranennyeElementy[i] = (int*)malloc(2 * sizeof(int));
        for (int j = 0; j < 2; j++) {
            sohranennyeElementy[i][j] = matritsa[i][j + B];
        }
    }

    // Перемещаем сохраненные элементы в новые позиции
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matritsa[i + A][j + B] = sohranennyeElementy[i][j];
        }
    }

    // Заполняем оставшиеся элементы по формуле
    for (int i = 0; i < stroki; i++) {
        for (int j = 0; j < stolbtsy; j++) {
            if (i < A || j < B) {
                matritsa[i][j] = i * C + j * D;
            }
        }
    }

    // Освобождаем память временного массива
    for (int i = 0; i < 2; i++) {
        free(sohranennyeElementy[i]);
    }
    free(sohranennyeElementy);

    // Выводим итоговую матрицу
    cout << "Итоговая матрица размером " << stroki << "x" << stolbtsy << ":" << endl;
    for (int i = 0; i < stroki; i++) {
        for (int j = 0; j < stolbtsy; j++) {
            cout << matritsa[i][j] << " ";
        }
        cout << endl;
    }

    // Обрабатываем матрицу: удаляем строки с нулями
    matrixResult(stroki, stolbtsy, matritsa);

    return 0;
*/
int a1, b1;
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
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для просмотра вектора
void viewVector(const vector<int>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << " ";
        }
    }
    cout << "]" << endl;
}

// Добавление элемента в начало
void addToBeginning(vector<int>& vec, int value) {
    cout << "До: ";
    viewVector(vec);
    vec.insert(vec.begin(), value);
    cout << "После: ";
    viewVector(vec);
}

// Добавление элемента в конец
void addToEnd(vector<int>& vec, int value) {
    cout << "До: ";
    viewVector(vec);
    vec.push_back(value);
    cout << "После: ";
    viewVector(vec);
}

// Очистка вектора
void clearVector(vector<int>& vec) {
    cout << "До: ";
    viewVector(vec);
    vec.clear();
    cout << "После: ";
    viewVector(vec);
    cout << "Вектор очищен!" << endl;
}

// Поиск элемента в векторе
void findElement(const vector<int>& vec, int value) {
    vector<int> indices;
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == value) {
            indices.push_back(i);
        }
    }

    if (indices.empty()) {
        cout << "[]" << endl;
    }
    else {
        cout << "[";
        for (int i = 0; i < indices.size(); ++i) {
            cout << indices[i];
            if (i < indices.size() - 1) {
                cout << ",";
            }
        }
        cout << "]" << endl;
    }
}

// Задание варианта: после каждого нечетного числа на четной позиции вставить 0
void variantTask(vector<int>& vec) {
    cout << "Вектор до преобразования: ";
    viewVector(vec);

    bool found = false;

    // Сначала проверим, есть ли такие элементы
    for (int i = 0; i < vec.size(); i += 2) { // четные позиции
        if (i < vec.size() && vec[i] % 2 != 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        // Добавляем -1 в начале и в конце
        vec.insert(vec.begin(), -1);
        vec.push_back(-1);
    }
    else {
        // Вставляем 0 после нечетных чисел на четных позициях
        for (int i = 0; i < vec.size(); i += 2) {
            if (i < vec.size() && vec[i] % 2 != 0) {
                // Вставляем 0 после текущего элемента
                vec.insert(vec.begin() + i + 1, 0);
                i++; // Пропускаем только что вставленный элемент
            }
        }
    }

    cout << "Вектор после преобразования: ";
    viewVector(vec);
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<int> vec;
    vec.reserve(100'000);
    int choice;

    do {
        cout << "\n=== Меню ===" << endl;
        cout << "0. Выход" << endl;
        cout << "1. Просмотр вектора" << endl;
        cout << "2. Добавить элемент в начало" << endl;
        cout << "3. Добавить элемент в конец" << endl;
        cout << "4. Очистка всего вектора" << endl;
        cout << "5. Поиск элемента в векторе" << endl;
        cout << "6. Задание варианта" << endl;
        cout << "Выберите пункт: ";
        cin >> choice;

        switch (choice) {
        case 0:
            cout << "Выход из программы..." << endl;
            break;

        case 1:
            cout << "Текущий вектор: ";
            viewVector(vec);
            break;

        case 2: {
            int value;
            cout << "Введите значение для добавления в начало: ";
            cin >> value;
            addToBeginning(vec, value);
            break;
        }

        case 3: {
            int value;
            cout << "Введите значение для добавления в конец: ";
            cin >> value;
            addToEnd(vec, value);
            break;
        }

        case 4:
            clearVector(vec);
            break;

        case 5: {
            int value;
            cout << "Введите значение для поиска: ";
            cin >> value;
            cout << "Индексы элемента " << value << ": ";
            findElement(vec, value);
            break;
        }

        case 6:
            variantTask(vec);
            break;

        default:
            cout << "Неверный выбор!" << endl;
        }

    } while (choice != 0);

    return 0;
} 
/*
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

using Vector = vector<int>;
using Array = array<int, 10>;

// Функция сортировки с передачей массива по значению (создается копия)
void sortOne(Array dataArray) {
    int arraySize = 10;
    for (int i = 0; i < arraySize - 1; i++)
        for (int j = i + 1; j < arraySize; j++)
            if (dataArray[i] > dataArray[j]) {
                swap(dataArray[i], dataArray[j]);
            }
    // Массив отсортирован только внутри функции, оригинал не меняется
}

// Функция сортировки с передачей массива по ссылке (работает с оригиналом)
void sortTwo(Array& dataArray) {
    int arraySize = 10;
    // Сортировка методом пузырька
    for (int i = 0; i < arraySize - 1; i++)
        for (int j = i + 1; j < arraySize; j++)
            if (dataArray[i] > dataArray[j]) {
                swap(dataArray[i], dataArray[j]); // Обмен элементов местами
            }
    // Изменения применяются к оригинальному массиву
}

// Функция сортировки с передачей массива через указатель
void sortThree(Array* dataArrayPtr) {
    int arraySize = 10;
    // Сортировка методом пузырька
    for (int i = 0; i < arraySize - 1; i++)
        for (int j = i + 1; j < arraySize; j++)
            if ((*dataArrayPtr)[i] > (*dataArrayPtr)[j]) {
                swap((*dataArrayPtr)[i], (*dataArrayPtr)[j]); // Обмен элементов через указатель
            }
    // Изменения применяются к оригинальному массиву через указатель
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Инициализация массива случайными значениями
    Array numbers = { 9, 1, 2, 0, 4, 3, 6, 8, 7, 5 };
    // Вывод исходного массива
    cout << "Исходный массив:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Сортировка передачей по значению (не изменяет исходный массив)
    sortOne(numbers);
    cout << "После сортировки по значению:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Восстановление исходного порядка элементов
    numbers = { 9, 1, 2, 0, 4, 3, 6, 8, 7, 5 };
    cout << "Восстановленный массив:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Сортировка передачей по ссылке (изменяет исходный массив)
    sortTwo(numbers);
    cout << "После сортировки по ссылке:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Восстановление исходного порядка элементов
    numbers = { 9, 1, 2, 0, 4, 3, 6, 8, 7, 5 };
    cout << "Восстановленный массив:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Сортировка передачей по указателю (изменяет исходный массив)
    sortThree(&numbers);
    cout << "После сортировки по указателю:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
} */
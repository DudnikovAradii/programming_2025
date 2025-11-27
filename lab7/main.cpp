#include <iostream>
#include <vector>
#include <algorithm>

// Функция для просмотра вектора
void viewVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

// Добавление элемента в начало
void addToBeginning(std::vector<int>& vec, int value) {
    std::cout << "До: ";
    viewVector(vec);
    vec.insert(vec.begin(), value);
    std::cout << "После: ";
    viewVector(vec);
}

// Добавление элемента в конец
void addToEnd(std::vector<int>& vec, int value) {
    std::cout << "До: ";
    viewVector(vec);
    vec.push_back(value);
    std::cout << "После: ";
    viewVector(vec);
}

// Очистка вектора
void clearVector(std::vector<int>& vec) {
    std::cout << "До: ";
    viewVector(vec);
    vec.clear();
    std::cout << "После: ";
    viewVector(vec);
    std::cout << "Вектор очищен!" << std::endl;
}

// Поиск элемента в векторе
void findElement(const std::vector<int>& vec, int value) {
    std::vector<int> indices;
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == value) {
            indices.push_back(i);
        }
    }

    if (indices.empty()) {
        std::cout << "[]" << std::endl;
    }
    else {
        std::cout << "[";
        for (int i = 0; i < indices.size(); ++i) {
            std::cout << indices[i];
            if (i < indices.size() - 1) {
                std::cout << ",";
            }
        }
        std::cout << "]" << std::endl;
    }
}

// Задание варианта: после каждого нечетного числа на четной позиции вставить 0
void variantTask(std::vector<int>& vec) {
    std::cout << "Вектор до преобразования: ";
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

    std::cout << "Вектор после преобразования: ";
    viewVector(vec);
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<int> vec;
    vec.reserve(100'000);
    int choice;

    do {
        std::cout << "\n=== Меню ===" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "1. Просмотр вектора" << std::endl;
        std::cout << "2. Добавить элемент в начало" << std::endl;
        std::cout << "3. Добавить элемент в конец" << std::endl;
        std::cout << "4. Очистка всего вектора" << std::endl;
        std::cout << "5. Поиск элемента в векторе" << std::endl;
        std::cout << "6. Задание варианта" << std::endl;
        std::cout << "Выберите пункт: ";
        std::cin >> choice;

        switch (choice) {
        case 0:
            std::cout << "Выход из программы..." << std::endl;
            break;

        case 1:
            std::cout << "Текущий вектор: ";
            viewVector(vec);
            break;

        case 2: {
            int value;
            std::cout << "Введите значение для добавления в начало: ";
            std::cin >> value;
            addToBeginning(vec, value);
            break;
        }

        case 3: {
            int value;
            std::cout << "Введите значение для добавления в конец: ";
            std::cin >> value;
            addToEnd(vec, value);
            break;
        }

        case 4:
            clearVector(vec);
            break;

        case 5: {
            int value;
            std::cout << "Введите значение для поиска: ";
            std::cin >> value;
            std::cout << "Индексы элемента " << value << ": ";
            findElement(vec, value);
            break;
        }

        case 6:
            variantTask(vec);
            break;

        default:
            std::cout << "Неверный выбор!" << std::endl;
        }

    } while (choice != 0);

    return 0;
} 
/*#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using Vector = std::vector<int>;  
using Array = std::array<int, 10>; 


// Функция сортировки, принимающая массив по значению (копия массива)
void sort1(Array arr) {
    std::sort(arr.begin(), arr.end()); // Сортировка копии массива
}

// Функция сортировки, принимающая массив по ссылке
void sort2(Array& arr) {
    std::sort(arr.begin(), arr.end()); // Сортировка исходного массива
}

// Функция сортировки, принимающая указатель на массив
void sort3(Array* arr) {
    std::sort((*arr).begin(), (*arr).end()); // Сортировка массива через указатель
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Исходный неотсортированный массив
    Array arr = { 5, 7, 0, 9, 4, 2, 6, 8, 3, 1 };

    // Вывод исходного массива
    std::cout << "Массив:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Сортировка передачей по значению (не изменяет исходный массив)
    sort1(arr);
    std::cout << "Отсортированный массив по значению:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Восстановление исходного массива
    arr = { 5, 7, 0, 9, 4, 2, 6, 8, 3, 1 };

    // Вывод восстановленного массива
    std::cout << "Массив:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Сортировка передачей по ссылке (изменяет исходный массив)
    sort2(arr);
    std::cout << "Отсортированный массив по ссылке:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Восстановление исходного массива
    arr = { 5, 7, 0, 9, 4, 2, 6, 8, 3, 1 };

    // Вывод восстановленного массива
    std::cout << "Массив:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Сортировка передачей по указателю (изменяет исходный массив)
    sort3(&arr);
    std::cout << "Отсортированный массив по указателю:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
*/
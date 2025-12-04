#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Funktsiya dlya prosmotra vektora
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

// Dobavlenie elementa v nachalo
void addToBeginning(vector<int>& vec, int value) {
    cout << "Do: ";
    viewVector(vec);
    vec.insert(vec.begin(), value);
    cout << "Posle: ";
    viewVector(vec);
}

// Dobavlenie elementa v konets
void addToEnd(vector<int>& vec, int value) {
    cout << "Do: ";
    viewVector(vec);
    vec.push_back(value);
    cout << "Posle: ";
    viewVector(vec);
}

// Ochistka vektora
void clearVector(vector<int>& vec) {
    cout << "Do: ";
    viewVector(vec);
    vec.clear();
    cout << "Posle: ";
    viewVector(vec);
    cout << "Vector ochishchen!" << endl;
}

// Poisk elementa v vektore
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

// Zadanie varianta: posle kajdogo nechetnogo chisla na chetnoj pozitsii vstavit' 0
void variantTask(vector<int>& vec) {
    cout << "Vector do preobrazovaniya: ";
    viewVector(vec);

    bool found = false;

    // Snachala proverim, est' li takie elementy
    for (int i = 0; i < vec.size(); i += 2) { // chetnye pozitsii
        if (i < vec.size() && vec[i] % 2 != 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        // Dobavlyaem -1 v nachale i v kontse
        vec.insert(vec.begin(), -1);
        vec.push_back(-1);
    }
    else {
        // Vstavlyaem 0 posle nechetnyh chisel na chetnyh pozitsiyah
        for (int i = 0; i < vec.size(); i += 2) {
            if (i < vec.size() && vec[i] % 2 != 0) {
                // Vstavlyaem 0 posle tekuschego elementa
                vec.insert(vec.begin() + i + 1, 0);
                i++; // Propuskaem tol'ko chto vstavlennyj element
            }
        }
    }

    cout << "Vector posle preobrazovaniya: ";
    viewVector(vec);
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<int> vec;
    vec.reserve(100'000);
    int choice;

    do {
        cout << "\n Menu " << endl;
        cout << "0. Vyhod" << endl;
        cout << "1. Prosmotr vektora" << endl;
        cout << "2. Dobavit element v nachalo" << endl;
        cout << "3. Dobavit element v konets" << endl;
        cout << "4. Ochistka vsego vektora" << endl;
        cout << "5. Poisk elementa v vektore" << endl;
        cout << "6. Zadanie varianta" << endl;
        cout << "Vyberite punkt: ";
        cin >> choice;

        switch (choice) {
        case 0:
            cout << "Vyhod iz programmy..." << endl;
            break;

        case 1:
            cout << "Tekuschij vector: ";
            viewVector(vec);
            break;

        case 2: {
            int value;
            cout << "Vvedite znachenie dlya dobavleniya v nachalo: ";
            cin >> value;
            addToBeginning(vec, value);
            break;
        }

        case 3: {
            int value;
            cout << "Vvedite znachenie dlya dobavleniya v konets: ";
            cin >> value;
            addToEnd(vec, value);
            break;
        }

        case 4:
            clearVector(vec);
            break;

        case 5: {
            int value;
            cout << "Vvedite znachenie dlya poiska: ";
            cin >> value;
            cout << "Indeksy elementa " << value << ": ";
            findElement(vec, value);
            break;
        }

        case 6:
            variantTask(vec);
            break;

        default:
            cout << "Nevernyj vybor!" << endl;
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

// Funktsiya sortirovki s peredachej massiva po znacheniyu (sozdaetsya kopiya)
void sortOne(Array dataArray) {
    int arraySize = 10;
    for (int i = 0; i < arraySize - 1; i++)
        for (int j = i + 1; j < arraySize; j++)
            if (dataArray[i] > dataArray[j]) {
                swap(dataArray[i], dataArray[j]);
            }
    // Massiv otsortirovan tol'ko vnutri funktsii, original ne menyaetsya
}

// Funktsiya sortirovki s peredachej massiva po ssylke (rabotaet s originalom)
void sortTwo(Array& dataArray) {
    int arraySize = 10;
    for (int i = 0; i < arraySize - 1; i++)
        for (int j = i + 1; j < arraySize; j++)
            if (dataArray[i] > dataArray[j]) {
                swap(dataArray[i], dataArray[j]); // Obmen elementov mestami
            }
    // Izmeneniya primenyayutsya k original'nomu massivu
}

// Funktsiya sortirovki s peredachej massiva cherez ukazatel'
void sortThree(Array* dataArrayPtr) {
    int arraySize = 10;
    for (int i = 0; i < arraySize - 1; i++)
        for (int j = i + 1; j < arraySize; j++)
            if ((*dataArrayPtr)[i] > (*dataArrayPtr)[j]) {
                swap((*dataArrayPtr)[i], (*dataArrayPtr)[j]); // Obmen elementov cherez ukazatel'
            }
    // Izmeneniya primenyayutsya k original'nomu massivu cherez ukazatel'
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Initsializatsiya massiva sluchajnymi znacheniyami
    Array numbers = { 9, 1, 2, 0, 4, 3, 6, 8, 7, 5 };
    // Vyvod iskhodnogo massiva
    cout << "Iskhodnyj massiv:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Sortirovka peredachej po znacheniyu (ne izmenyaet iskhodnyj massiv)
    sortOne(numbers);
    cout << "Posle sortirovki po znacheniyu:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Vosstanovlenie iskhodnogo poryadka elementov
    numbers = { 9, 1, 2, 0, 4, 3, 6, 8, 7, 5 };
    cout << "Vosstanovlennyj massiv:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Sortirovka peredachej po ssylke (izmenyaet iskhodnyj massiv)
    sortTwo(numbers);
    cout << "Posle sortirovki po ssylke:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Vosstanovlenie iskhodnogo poryadka elementov
    numbers = { 9, 1, 2, 0, 4, 3, 6, 8, 7, 5 };
    cout << "Vosstanovlennyj massiv:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Sortirovka peredachej po ukazatelyu (izmenyaet iskhodnyj massiv)
    sortThree(&numbers);
    cout << "Posle sortirovki po ukazatelyu:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}
*/
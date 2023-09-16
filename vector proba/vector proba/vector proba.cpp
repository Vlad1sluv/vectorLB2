// В головному файлі main.cpp
#include "vector_library.h"

int main() {
    // Налаштування кодування для вводу і виводу кирилиці у консолі Windows
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    string command;
    while (true) {
        cout << "Введіть команду (створити, список, виконати, вийти): ";
        cin >> command;

        if (command == "створити") {
            createVector();
        }
        else if (command == "список") {
            listVectors();
        }
        else if (command == "виконати") {
            performOperation();
        }
        else if (command == "вийти") {
            break;
        }
        else {
            cout << "Недійсна команда." << endl;
        }
    }

    return 0;
}

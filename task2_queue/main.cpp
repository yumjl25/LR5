#include "queue.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int windowCount;
    
    cout << "Введите количество окон: ";
    cin >> windowCount;
    
    ElectronicQueue eq(windowCount);
    
    string command;
    
    cout << "\nДоступные команды:\n";
    cout << "  ENQUEUE <время>\n";
    cout << "  DISTRIBUTE\n";
    cout << "  EXIT\n\n";
    
    while (true) {
        cout << ">>> ";
        cin >> command;
        
        // Переводим в верхний регистр
        for (char& c : command) {
            c = toupper(c);
        }
        
        if (command == "ENQUEUE") {
            int duration;
            cin >> duration;
            
            if (duration <= 0) {
                cout << "Ошибка: время должно быть положительным\n";
            } else {
                eq.enqueue(duration);
            }
        }
        else if (command == "DISTRIBUTE") {
            eq.distribute();
            eq.printResult();
        }
        else if (command == "EXIT") {
            cout << "До свидания!\n";
            break;
        }
        else {
            cout << "Неизвестная команда\n";
            cin.ignore(10000, '\n');
        }
    }
    
    return 0;
}
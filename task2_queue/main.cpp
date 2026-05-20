#include "queue.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    int windowCount;
    
    cout << "Введите количество окон: ";
    cin >> windowCount;
    
    windows.resize(windowCount);
    
    string command;
    
    cout << "\nДоступные команды:\n";
    cout << "  ENQUEUE <время>\n";
    cout << "  DISTRIBUTE\n";
    cout << "  EXIT\n\n";
    
    while (true) {
        cout << ">>> ";
        cin >> command;
        
        for (char& c : command) {
            c = toupper(c);
        }
        
        if (command == "ENQUEUE") {
            int duration;
            cin >> duration;
            
            if (duration <= 0) {
                cout << "Ошибка: время должно быть положительным\n";
            } else {
                enqueue(duration);
            }
        }
        else if (command == "DISTRIBUTE") {
            distribute();
            printResult();
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
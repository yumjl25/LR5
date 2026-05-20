#include "warehouse.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    string command;
    
    cout << "Добро пожаловать в систему управления складом\n";
    cout << "Доступные команды:\n";
    cout << "  ADD <товар> <количество> <адрес>\n";
    cout << "  REMOVE <товар> <количество> <адрес>\n";
    cout << "  INFO\n";
    cout << "  EXIT\n\n";
    
    while (true) {
        cout << ">>> ";
        cin >> command;
        
        for (char& c : command) {
            c = toupper(c);
        }
        
        if (command == "ADD") {
            string product, address;
            int quantity;
            cin >> product >> quantity >> address;
            add(product, quantity, address);
        }
        else if (command == "REMOVE") {
            string product, address;
            int quantity;
            cin >> product >> quantity >> address;
            remove(product, quantity, address);
        }
        else if (command == "INFO") {
            info();
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
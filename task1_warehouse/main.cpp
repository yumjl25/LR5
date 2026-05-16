#include "warehouse.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    // Параметры склада (3 зоны, 14 стеллажей, 4 секции, 8 полок)
    Warehouse warehouse(3, 14, 4, 8); //Warehouse Тип объекта (класс)
    
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
        
        // Переводим команду в верхний регистр для удобства
        for (char& c : command) {
            c = toupper(c);
        }
        
        if (command == "ADD") {
            string product, address;
            int quantity;
            
            cin >> product >> quantity >> address;
            warehouse.add(product, quantity, address);
        }
        else if (command == "REMOVE") {
            string product, address;
            int quantity;
            
            cin >> product >> quantity >> address;
            warehouse.remove(product, quantity, address);
        }
        else if (command == "INFO") {
            warehouse.info();
        }
        else if (command == "EXIT") {
            cout << "До свидания!\n";
            break;
        }
        else {
            cout << "Неизвестная команда. Используйте ADD, REMOVE, INFO или EXIT\n";
            // Очищаем строку ввода
            cin.ignore(10000, '\n'); //Игнорируем до 10000 символов или до перевода строки (\n)01
        }
    }
    
    return 0;
}
#include "warehouse.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Конструктор (функция, которая вызывается при создании объекта)
Warehouse::Warehouse(int z, int r, int sec, int sh) 
    : zones(z), racks(r), sections(sec), shelves(sh) {} //Список инициализации — присваиваем значения полям класса

// Получить общее количество ячеек на складе
int Warehouse::getTotalCellsCount() const { //Метод класса Warehouse, const - метод не изменяет объект
    return zones * racks * sections * shelves;
}

// Получить количество ячеек в одной зоне
int Warehouse::getZoneCellsCount() const {
    return racks * sections * shelves;
}

// Получить общее количество товаров на складе
int Warehouse::getTotalItems() const {
    int total = 0;
    for (const auto& [address, cell] : cells) { //перебираем все ячейки в map, раскладываем ключ, значение на отдельные переменные
        total += cell.quantity; //Добавляем количество товаров из каждой ячейки
    }
    return total;
}

// Получить количество товаров в конкретной зоне
int Warehouse::getZoneItems(char zone) const {
    int total = 0;
    for (const auto& [address, cell] : cells) {
        if (address[0] == zone) { //проверяем первый символ адреса
            total += cell.quantity;
        }
    }
    return total;
}

// Проверка корректности адреса
bool Warehouse::validateAddress(const string& address) const {
    // Проверка длины
    if (address.length() != 5) return false;
    
    // Проверка зоны
    char zone = address[0];
    if (zone < 'A' || zone >= 'A' + zones) return false;
    
    // Проверка, что все остальные символы - цифры
    for (size_t i = 1; i < address.length(); i++) {
        if (!isdigit(address[i])) return false;
    }
    
    // Проверка стеллажа (первые 2 цифры после зоны)
    int rack = stoi(address.substr(1, 2));
    if (rack < 1 || rack > racks) return false;
    
    // Проверка секции (индекс 3)
    int section = address[3] - '0';
    if (section < 1 || section > sections) return false;
    
    // Проверка полки (индекс 4)
    int shelf = address[4] - '0';
    if (shelf < 1 || shelf > shelves) return false;
    
    return true;
}

// Генерация всех возможных адресов
void Warehouse::generateAllAddresses(vector<string>& addresses) const {
    addresses.clear();
    
    // Зоны: A, B, C 
    for (char zone = 'A'; zone < 'A' + zones; zone++) {
        // Стеллажи
        for (int rack = 1; rack <= racks; rack++) {
            // Секции
            for (int section = 1; section <= sections; section++) {
                // Полки
                for (int shelf = 1; shelf <= shelves; shelf++) {
                    string address;
                    address += zone;
                    
                    if (rack < 10) {
                        address += "0"; //добавляем ведущий ноль для стеллажей 1-9.
                    }
                    address += to_string(rack);
                    
                    // Секция: 1 цифра
                    address += to_string(section);
                    
                    // Полка: 1 цифра
                    address += to_string(shelf);
                    
                    addresses.push_back(address); //добавляем адрес в конец вектора
                }
            }
        }
    }
}

// Метод добавления товара
void Warehouse::add(const string& product, int quantity, const string& address) {
    // Проверка количества
    if (quantity > 10) {
        cout << "Ошибка: Превышена вместимость ячейки (максимум 10)\n";
        return;
    }
    
    if (quantity <= 0) {
        cout << "Ошибка: Количество должно быть положительным\n";
        return;
    }
    
    if (!validateAddress(address)) {
    cout << "Ошибка: Неверный адрес ячейки\n";
    return;
    }

    // Ищем ячейку
    auto it = cells.find(address); //Ищем адрес в map. it — итератор (указатель на найденный элемент)
    
    if (it != cells.end()) {
        // Ячейка существует
        if (it->second.productName != product) { //it->second.productName — название товара в найденной ячейке
            cout << "Ошибка: Ячейка " << address << " занята товаром " 
                 << it->second.productName << "\n";
        } else if (it->second.quantity + quantity > 10) {
            cout << "Ошибка: Превышена вместимость ячейки (максимум 10)\n";
        } else {
            it->second.quantity += quantity; 
            cout << "Добавлено " << quantity << " " << product << " в " << address << "\n";
        }
    } else {
        cells[address] = {product, quantity}; //создаём новую ячейку
        cout << "Добавлено " << quantity << " " << product << " в " << address << "\n";
    }
}

// Метод удаления товара
void Warehouse::remove(const string& product, int quantity, const string& address) {
    if (quantity <= 0) {
        cout << "Ошибка: Количество должно быть положительным\n";
        return;
    }
    
    if (!validateAddress(address)) {
    cout << "Ошибка: Неверный адрес ячейки\n";
    return;
    }
    
    // Ищем ячейку
    auto it = cells.find(address);
    
    if (it == cells.end()) {
        cout << "Ошибка: Товар " << product << " не найден в ячейке " << address << "\n";
        return;
    }
    
    // Проверяем, что товар совпадает
    if (it->second.productName != product) {
        cout << "Ошибка: Товар " << product << " не найден в ячейке " << address 
             << " (там " << it->second.productName << ")\n";
        return;
    }
    
    // Проверяем, хватает ли количества
    if (it->second.quantity < quantity) {
        cout << "Ошибка: Недостаточно товаров для удаления (есть " 
             << it->second.quantity << ", запрошено " << quantity << ")\n";
        return;
    }
    
    // Удаляем
    it->second.quantity -= quantity;
    
    if (it->second.quantity == 0) {
        // Ячейка освободилась
        cells.erase(it); //удаляем ячейку из map, если она стала пустой.
        cout << "Удалено " << quantity << " " << product << " (ячейка " << address << " освобождена)\n";
    } else {
        cout << "Удалено " << quantity << " " << product << " (остаток: " << it->second.quantity << ")\n";
    }
}

// Метод вывода информации о складе
void Warehouse::info() const {
    cout << fixed << setprecision(2);
    
    // 1. Общая загруженность склада
    int totalCells = getTotalCellsCount();
    int totalItems = getTotalItems();
    double totalLoad = (totalItems * 100.0) / (totalCells * 10.0); //товары / ячейки
    cout << "Загруженность склада: " << totalLoad << " %\n";
    
    // 2. Загруженность каждой зоны
    int zoneCells = getZoneCellsCount();
    for (char zone = 'A'; zone < 'A' + zones; zone++) {
        int zoneItems = getZoneItems(zone);
        double zoneLoad = (zoneItems * 100.0) / (zoneCells * 10.0);
        cout << "Загруженность зоны " << zone << ": " << zoneLoad << " %\n";
    }
    
    // 3. Заполненные ячейки
    cout << "\nЗаполненные ячейки:\n";
    if (cells.empty()) {
        cout << "  (нет заполненных ячеек)\n";
    } else {
        for (const auto& [address, cell] : cells) { //Перебираем занятые ячейки и выводим.
            cout << "  " << address << ": " << cell.productName << " (" << cell.quantity << ")\n";
        }
    }
    
    // 4. Пустые ячейки
    cout << "\nПустые ячейки:\n";
    
    vector<string> allAddresses;
    generateAllAddresses(allAddresses); //Генерируем все адреса, потом проверяем, каких нет в cells - пустые.
    
    vector<string> emptyAddresses;
    for (const string& addr : allAddresses) {
        if (cells.find(addr) == cells.end()) {
            emptyAddresses.push_back(addr);
        }
    }
    
    if (emptyAddresses.empty()) {
        cout << "  (нет пустых ячеек)\n";
    } else {
        // Выводим первые 10 адресов и "..."
        int showCount = min(10, (int)emptyAddresses.size()); //берём минимум: либо 10, либо сколько есть.
        for (int i = 0; i < showCount; i++) {
            if (i > 0) cout << ", ";
            cout << emptyAddresses[i];
        }
        
        if (emptyAddresses.size() > 10) {
            cout << ", ... (всего " << emptyAddresses.size() << " пустых ячеек)";
        }
        cout << "\n";
    }
    
    cout << "\n";
}
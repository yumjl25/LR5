#include "warehouse.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Глобальные переменные (определение)
map<string, Cell> cells;
const int ZONES = 3;
const int RACKS = 14;
const int SECTIONS = 4;
const int SHELVES = 8;

int getTotalCellsCount() {
    return ZONES * RACKS * SECTIONS * SHELVES;
}

int getZoneCellsCount() {
    return RACKS * SECTIONS * SHELVES;
}

int getTotalItems() {
    int total = 0;
    for (const auto& [address, cell] : cells) {
        total += cell.quantity;
    }
    return total;
}

int getZoneItems(char zone) {
    int total = 0;
    for (const auto& [address, cell] : cells) {
        if (address[0] == zone) {
            total += cell.quantity;
        }
    }
    return total;
}

bool validateAddress(const string& address) {
    if (address.length() != 5) return false;
    
    char zone = address[0];
    if (zone < 'A' || zone >= 'A' + ZONES) return false;
    
    for (size_t i = 1; i < address.length(); ++i) {
        if (!isdigit(address[i])) return false;
    }
    
    int rack = stoi(address.substr(1, 2));
    if (rack < 1 || rack > RACKS) return false;
    
    int section = address[3] - '0';
    if (section < 1 || section > SECTIONS) return false;
    
    int shelf = address[4] - '0';
    if (shelf < 1 || shelf > SHELVES) return false;
    
    return true;
}

void generateAllAddresses(vector<string>& addresses) {
    addresses.clear();
    
    for (char zone = 'A'; zone < 'A' + ZONES; ++zone) {
        for (int rack = 1; rack <= RACKS; ++rack) {
            for (int section = 1; section <= SECTIONS; ++section) {
                for (int shelf = 1; shelf <= SHELVES; ++shelf) {
                    string address;
                    address += zone;
                    
                    if (rack < 10) {
                        address += "0";
                    }
                    address += to_string(rack);
                    address += to_string(section);
                    address += to_string(shelf);
                    
                    addresses.push_back(address);
                }
            }
        }
    }
}

void add(const string& product, int quantity, const string& address) {
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

    auto it = cells.find(address);
    
    if (it != cells.end()) {
        if (it->second.productName != product) {
            cout << "Ошибка: Ячейка " << address << " занята товаром " 
                 << it->second.productName << "\n";
        } else if (it->second.quantity + quantity > 10) {
            cout << "Ошибка: Превышена вместимость ячейки (максимум 10)\n";
        } else {
            it->second.quantity += quantity;
            cout << "Добавлено " << quantity << " " << product << " в " << address << "\n";
        }
    } else {
        cells[address] = {product, quantity};
        cout << "Добавлено " << quantity << " " << product << " в " << address << "\n";
    }
}

void remove(const string& product, int quantity, const string& address) {
    if (quantity <= 0) {
        cout << "Ошибка: Количество должно быть положительным\n";
        return;
    }
    
    if (!validateAddress(address)) {
        cout << "Ошибка: Неверный адрес ячейки\n";
        return;
    }
    
    auto it = cells.find(address);
    
    if (it == cells.end()) {
        cout << "Ошибка: Товар " << product << " не найден в ячейке " << address << "\n";
        return;
    }
    
    if (it->second.productName != product) {
        cout << "Ошибка: Товар " << product << " не найден в ячейке " << address 
             << " (там " << it->second.productName << ")\n";
        return;
    }
    
    if (it->second.quantity < quantity) {
        cout << "Ошибка: Недостаточно товаров для удаления (есть " 
             << it->second.quantity << ", запрошено " << quantity << ")\n";
        return;
    }
    
    it->second.quantity -= quantity;
    
    if (it->second.quantity == 0) {
        cells.erase(it);
        cout << "Удалено " << quantity << " " << product << " (ячейка " << address << " освобождена)\n";
    } else {
        cout << "Удалено " << quantity << " " << product << " (остаток: " << it->second.quantity << ")\n";
    }
}

void info() {
    cout << fixed << setprecision(2);
    
    int totalCells = getTotalCellsCount();
    int totalItems = getTotalItems();
    double totalLoad = (totalItems * 100.0) / (totalCells * 10.0);
    cout << "Загруженность склада: " << totalLoad << " %\n";
    
    int zoneCells = getZoneCellsCount();
    for (char zone = 'A'; zone < 'A' + ZONES; ++zone) {
        int zoneItems = getZoneItems(zone);
        double zoneLoad = (zoneItems * 100.0) / (zoneCells * 10.0);
        cout << "Загруженность зоны " << zone << ": " << zoneLoad << " %\n";
    }
    
    cout << "\nЗаполненные ячейки:\n";
    if (cells.empty()) {
        cout << "  (нет заполненных ячеек)\n";
    } else {
        for (const auto& [address, cell] : cells) {
            cout << "  " << address << ": " << cell.productName << " (" << cell.quantity << ")\n";
        }
    }
    
    cout << "\nПустые ячейки:\n";
    
    vector<string> allAddresses;
    generateAllAddresses(allAddresses);
    
    vector<string> emptyAddresses;
    for (const string& addr : allAddresses) {
        if (cells.find(addr) == cells.end()) {
            emptyAddresses.push_back(addr);
        }
    }
    
    if (emptyAddresses.empty()) {
        cout << "  (нет пустых ячеек)\n";
    } else {
        int showCount = min(10, (int)emptyAddresses.size());
        for (int i = 0; i < showCount; ++i) {
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
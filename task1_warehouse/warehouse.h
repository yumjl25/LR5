#ifndef WAREHOUSE_H //если символ WAREHOUSE_H ещё не определён
#define WAREHOUSE_H

#include <string>
#include <map>
#include <vector>

using namespace std;

// Структура для хранения информации о товаре в ячейке
struct Cell { //В struct все поля по умолчанию public (доступны всем)
    string productName;
    int quantity;
};

// Класс для управления складом
class Warehouse {
private: //всё, что ниже, доступно только внутри класса. Никто снаружи не может напрямую трогать эти переменные
    map<string, Cell> cells;
    
    // Параметры склада. Задаются в конструкторе и больше не меняются
    int zones;      // количество зон
    int racks;      // количество стеллажей в каждой зоне
    int sections;   // количество секций в каждом стеллаже
    int shelves;    // количество полок в каждой секции
    
    // Вспомогательные методы. они нужны только внутри класса для работы других методов
    //Пользователь класса не должен их вызывать напрямую
    int getTotalCellsCount() const; // const - метод не изменяет объект 
    int getZoneCellsCount() const;
    int getTotalItems() const;
    int getZoneItems(char zone) const;
    bool validateAddress(const string& address) const;
    void generateAllAddresses(vector<string>& addresses) const;
    
public: //доступно снаружи, интерфейс класса
    // Конструктор
    Warehouse(int z, int r, int sec, int sh);
    
    // Основные методы
    void add(const string& product, int quantity, const string& address);
    void remove(const string& product, int quantity, const string& address);
    void info() const;
}; //Закрываем класс

#endif
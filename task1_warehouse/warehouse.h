#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <map>
#include <vector>

using namespace std;

struct Cell {
    string productName;
    int quantity;
};

extern map<string, Cell> cells;
extern const int ZONES;
extern const int RACKS;
extern const int SECTIONS;
extern const int SHELVES;

// Объявления функций
int getTotalCellsCount();
int getZoneCellsCount();
int getTotalItems();
int getZoneItems(char zone);
bool validateAddress(const string& address);
void generateAllAddresses(vector<string>& addresses);
void add(const string& product, int quantity, const string& address);
void remove(const string& product, int quantity, const string& address);
void info();

#endif
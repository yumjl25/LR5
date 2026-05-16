#ifndef PLANES_H
#define PLANES_H

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

// Типы команд
enum class Type { //строго типизированное перечисление
    CREATE_PLANE,
    PLANES_FOR_TOWN,
    TOWNS_FOR_PLANE,
    PLANES,
    UNKNOWN
};

// Класс системы управления самолётами
class PlaneSystem {
private:
    // самолёт - список городов
    map<string, vector<string>> planes;
    
    // Вспомогательные методы
    bool planeExists(const string& name) const;
    vector<string> getPlanesForTown(const string& town) const;
    
public:
    // Основные команды
    void createPlane(const string& name, const vector<string>& towns);
    void planesForTown(const string& town) const;
    void townsForPlane(const string& name) const;
    void printAllPlanes() const;
    
    // Парсинг команд
    static Type getCommandType(const string& cmd); //static	Метод принадлежит классу, а не объекту. Можно вызывать без создания объекта
};

#endif
#include "planes.h"
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

// Проверка существования самолёта
bool PlaneSystem::planeExists(const string& name) const {
    return planes.find(name) != planes.end(); //Ищем самолёт с именем name в map
}

// Получить список самолётов для города
vector<string> PlaneSystem::getPlanesForTown(const string& town) const {
    vector<string> result;
    
    for (const auto& [planeName, route] : planes) { //Перебираем все самолёты (ключ=имя, значение=маршрут)
        for (const string& city : route) { //Перебираем все города в маршруте
            if (city == town) {
                result.push_back(planeName);
                break; //Прерываем внутренний цикл (чтобы не добавить тот же самолёт дважды)
            }
        }
    }
    
    return result;
}

// CREATE_PLANE
void PlaneSystem::createPlane(const string& name, const vector<string>& towns) {
    // Проверка: существует ли уже
    if (planeExists(name)) {
        cout << "Ошибка: Самолёт " << name << " уже создан\n";
        return;
    }
    
    // Проверка: минимум 2 города
    if (towns.size() < 2) {
        cout << "Ошибка: Самолёт не может быть создан с одним городом\n";
        return;
    }
    
    // Проверка: повторяющиеся города
    for (size_t i = 0; i + 1 < towns.size(); ++i) {
        if (towns[i] == towns[i + 1]) {
            cout << "Ошибка: Самолёт не может быть создан с двумя одинаковыми городами подряд\n";
            return;
        }
    }
    
    // Все проверки пройдены - создаём
    planes[name] = towns; //Добавляем в map
    cout << "Самолёт " << name << " создан\n";
}

// PLANES_FOR_TOWN
void PlaneSystem::planesForTown(const string& town) const {
    vector<string> result = getPlanesForTown(town); //Получаем список самолётов для города
    
    if (result.empty()) {
        cout << "Ошибка: Город " << town << " не найден\n";
    } else {
        cout << "Самолёты на городе " << town << ": ";
        for (size_t i = 0; i < result.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << result[i];
        }
        cout << "\n";
    }
}

// TOWNS_FOR_PLANE
void PlaneSystem::townsForPlane(const string& name) const {
    auto it = planes.find(name);
    
    // Проверка: существует ли самолёт
    if (it == planes.end()) {
        cout << "Ошибка: Самолёт " << name << " не найден\n";
        return;
    }
    
    const vector<string>& route = it->second;
    
    // Вывод городов самолёта
    cout << "Города самолёта " << name << ": ";
    for (size_t i = 0; i < route.size(); ++i) {
        if (i > 0) cout << " ";
        cout << route[i];
    }
    cout << "\n\n";
    
    // Для каждого города выводим другие самолёты
    for (const string& city : route) {
        cout << "Город " << city << ": ";
        
        vector<string> otherPlanes;
        for (const auto& [otherName, otherRoute] : planes) {
            if (otherName == name) continue;  // otherName == name - пропускаем
            
            for (const string& otherCity : otherRoute) { //Проверяем, есть ли этот город в маршруте другого самолёта
                if (otherCity == city) { 
                    otherPlanes.push_back(otherName);
                    break;
                }
            }
        }
        
        if (otherPlanes.empty()) {
            cout << "-\n";
        } else {
            for (size_t i = 0; i < otherPlanes.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << otherPlanes[i];
            }
            cout << "\n";
        }
    }
}

// PLANES - вывод всех самолётов
void PlaneSystem::printAllPlanes() const {
    if (planes.empty()) {
        cout << "Ошибка: Самолёты не найдены\n";
        return;
    }
    
    for (const auto& [name, route] : planes) {
        cout << "Самолёт " << name << ": ";
        
        // для вывода городов
        bool first = true;
        for (const string& city : route) {
            if (!first) cout << " ";
            cout << city;
            first = false;
        }
        cout << "\n";
    }
}

// Определение команды по строке
Type PlaneSystem::getCommandType(const string& cmd) { //Преобразует строку  в значение перечисления Type
    if (cmd == "CREATE_PLANE") return Type::CREATE_PLANE;
    if (cmd == "PLANES_FOR_TOWN") return Type::PLANES_FOR_TOWN;
    if (cmd == "TOWNS_FOR_PLANE") return Type::TOWNS_FOR_PLANE;
    if (cmd == "PLANES") return Type::PLANES;
    return Type::UNKNOWN;
}
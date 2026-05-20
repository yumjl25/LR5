#include "planes.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    PlaneSystem system; 
    string line; 
    
    cout << "Система управления маршрутами самолётов\n";
    cout << "Команды:\n";
    cout << "  CREATE_PLANE <имя> <город1> <город2> ... <городN>\n";
    cout << "  PLANES_FOR_TOWN <город>\n";
    cout << "  TOWNS_FOR_PLANE <имя>\n";
    cout << "  PLANES\n";
    cout << "  EXIT\n\n";
    
    while (true) {
        cout << ">>> ";
        getline(cin, line);
        
        if (line.empty()) continue;
        
        stringstream ss(line);
        string command;
        ss >> command; 

        for (char& c : command) {
            c = toupper(c);
        }
        
        Type cmdType = PlaneSystem::getCommandType(command);
        
        switch (cmdType) {
            case Type::CREATE_PLANE: {
                string planeName;
                ss >> planeName;
                
                vector<string> towns;
                string town;
                while (ss >> town) {
                    towns.push_back(town);
                }
                
                if (planeName.empty() || towns.empty()) {
                    cout << "Ошибка: Неверный формат команды\n";
                } else {
                    system.createPlane(planeName, towns);
                }
                break;
            }
            
            case Type::PLANES_FOR_TOWN: {
                string town;
                ss >> town;
                
                if (town.empty()) {
                    cout << "Ошибка: Не указан город\n";
                } else {
                    system.planesForTown(town);
                }
                break;
            }
            
            case Type::TOWNS_FOR_PLANE: {
                string planeName;
                ss >> planeName;
                
                if (planeName.empty()) {
                    cout << "Ошибка: Не указан самолёт\n";
                } else {
                    system.townsForPlane(planeName);
                }
                break;
            }
            
            case Type::PLANES:
                system.printAllPlanes();
                break;
            
            case Type::UNKNOWN:
                if (command == "EXIT") {
                    cout << "До свидания!\n";
                    return 0;
                }
                cout << "Неизвестная команда: " << command << "\n";
                break;
        }
    }
    
    return 0;
}
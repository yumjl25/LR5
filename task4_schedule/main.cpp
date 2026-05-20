#include "schedule.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

int main() {
    months = {
        {"Январь", 31},
        {"Февраль", 28},
        {"Март", 31},
        {"Апрель", 30},
        {"Май", 31},
        {"Июнь", 30},
        {"Июль", 31},
        {"Август", 31},
        {"Сентябрь", 30},
        {"Октябрь", 31},
        {"Ноябрь", 30},
        {"Декабрь", 31}
    };
    
    int n;
    
    cout << "Введите количество запросов (N):\n>>> ";
    cin >> n;
    cin.ignore();
    
    for (int i = 0; i < n; ++i) {
        string line;
        cout << ">>> ";
        getline(cin, line);
        
        if (line.empty()) {
            --i;
            continue;
        }
        
        stringstream ss(line);
        string command;
        ss >> command;
        
        for (char& c : command) {
            c = toupper(c);
        }
        
        if (command == "CLASS") {
            int day;
            string discipline;
            ss >> day >> discipline;
            addClass(day, discipline);
        }
        else if (command == "NEXT") {
            nextMonth();
        }
        else if (command == "VIEW") {
            int day;
            ss >> day;
            viewDay(day);
        }
        else {
            cout << "Неизвестная команда: " << command << "\n";
        }
    }
    
    return 0;
}
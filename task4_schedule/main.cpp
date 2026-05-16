#include "schedule.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>   // для toupper

using namespace std;

int main() {
    Schedule schedule; // создаём объект расписания
    int n;
    
    cout << "Введите количество запросов (N):\n>>> ";
    cin >> n;
    cin.ignore();  // очищаем буфер после cin, сли его не убрать, следующий getline прочитает пустую строку
    
    for (int i = 0; i < n; ++i) {
        string line;
        cout << ">>> ";
        getline(cin, line); //Читаем всю строку целиком
        
        if (line.empty()) {
            --i; //откатываем счётчик, чтобы этот запрос не засчитался
            continue;
        }
        
        stringstream ss(line); // превращаем строку в поток
        string command;
        ss >> command;  // читаем первое слово — это команда
        
        // Переводим команду в верхний регистр
        for (char& c : command) {
            c = toupper(c);
        }
        
        if (command == "CLASS") {
            int day;
            string discipline;
            ss >> day >> discipline; //Читаем из потока день и дисциплину
            schedule.addClass(day, discipline);
        }
        else if (command == "NEXT") {
            schedule.nextMonth();
        }
        else if (command == "VIEW") {
            int day;
            ss >> day; //Читаем день из потока и вызываем метод
            schedule.viewDay(day);
        }
        else {
            cout << "Неизвестная команда: " << command << "\n";
        }
    }
    
    return 0;
}
#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include <vector>
#include <map>

using namespace std;

// Структура месяца
struct Month {
    string name;
    int days;
};

// Класс расписания
class Schedule {
private:
    vector<Month> months;
    int currentMonth;                          // индекс текущего месяца
    map<int, vector<string>> schedule;         // день -> дисциплины
    
    int getDaysInMonth(int monthIndex) const;
    string getMonthName(int monthIndex) const;
    
public:
    Schedule(); //Вызывается при создании объекта. Инициализирует месяцы и устанавливает currentMonth = 0 (январь).
    
    void addClass(int day, const string& discipline);
    void nextMonth();
    void viewDay(int day) const;
};

#endif
#include "schedule.h"
#include <iostream>
#include <algorithm>

using namespace std;

vector<Month> months;
int currentMonth = 0;
map<int, vector<string>> schedule;

int getDaysInMonth(int monthIndex) {
    return months[monthIndex].days;
}

string getMonthName(int monthIndex) {
    return months[monthIndex].name;
}

void addClass(int day, const string& discipline) {
    int daysInMonth = getDaysInMonth(currentMonth);
    
    if (day < 1 || day > daysInMonth) {
        cout << "Ошибка: В этом месяце всего " << daysInMonth << " дней\n";
        return;
    }
    
    auto& disciplines = schedule[day];
    for (const string& existing : disciplines) {
        if (existing == discipline) {
            cout << "Ошибка: Дисциплина " << discipline << " уже есть в этот день\n";
            return;
        }
    }
    
    disciplines.push_back(discipline);
    cout << "Добавлена дисциплина " << discipline << " на день " << day << "\n";
}

void nextMonth() {
    currentMonth++;
    
    if (currentMonth >= 12) {
        currentMonth = 11;
        cout << "Ошибка: Дальше декабря нельзя перейти\n";
        return;
    }
    
    int newDays = getDaysInMonth(currentMonth);
    map<int, vector<string>> newSchedule;
    
    for (const auto& [oldDay, disciplines] : schedule) {
        int newDay = oldDay;
        
        if (newDay > newDays) {
            newDay = newDays;
        }
        
        for (const string& disc : disciplines) {
            newSchedule[newDay].push_back(disc);
        }
    }
    
    schedule = newSchedule;
    cout << "Переход на следующий месяц (" << getMonthName(currentMonth) << ")\n";
}

void viewDay(int day) {
    int daysInMonth = getDaysInMonth(currentMonth);
    
    if (day < 1 || day > daysInMonth) {
        cout << "Ошибка: В этом месяце всего " << daysInMonth << " дней\n";
        return;
    }
    
    auto it = schedule.find(day);
    
    if (it == schedule.end() || it->second.empty()) {
        cout << "В день " << day << " мы свободны!\n";
    } else {
        cout << "В день " << day << " занятия в университете: ";
        for (size_t i = 0; i < it->second.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << it->second[i];
        }
        cout << "\n";
    }
}
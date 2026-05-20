#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include <vector>
#include <map>

using namespace std;

struct Month {
    string name;
    int days;
};

extern vector<Month> months;
extern int currentMonth;
extern map<int, vector<string>> schedule;

// Объявления функций
int getDaysInMonth(int monthIndex);
string getMonthName(int monthIndex);
void addClass(int day, const string& discipline);
void nextMonth();
void viewDay(int day);

#endif
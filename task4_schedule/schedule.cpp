#include "schedule.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Конструктор
Schedule::Schedule() { //вызывается при создании объекта Schedule
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
    currentMonth = 0;  // начинаем с января
}

// Количество дней в месяце
int Schedule::getDaysInMonth(int monthIndex) const { //Принимает индекс месяца (0-11)
    return months[monthIndex].days; //Обращается к вектору месяцев, берёт поле days
}

// Название месяца
string Schedule::getMonthName(int monthIndex) const {
    return months[monthIndex].name;
}

// CLASS <день> <дисциплина>
void Schedule::addClass(int day, const string& discipline) {
    int daysInMonth = getDaysInMonth(currentMonth); //Получаем количество дней в текущем месяце
    
    // Проверка: существует ли такой день в текущем месяце
    if (day < 1 || day > daysInMonth) {
        cout << "Ошибка: В этом месяце всего " << daysInMonth << " дней\n";
        return;
    }
    
    // Проверка: есть ли уже такая дисциплина в этот день
    auto& disciplines = schedule[day]; //Получаем ссылку на вектор дисциплин для этого дня (если дня нет в map, он создаётся автоматически)
    for (const string& existing : disciplines) {
        if (existing == discipline) {
            cout << "Ошибка: Дисциплина " << discipline << " уже есть в этот день\n";
            return;
        }
    }
    
    // Если все проверки пройдены — добавляем дисциплину в вектор.
    disciplines.push_back(discipline);
    cout << "Добавлена дисциплина " << discipline << " на день " << day << "\n";
}

// NEXT - переход на следующий месяц
void Schedule::nextMonth() {
    currentMonth++;
    
    // Если перешли за декабрь, останавливаемся
    if (currentMonth >= 12) {
        currentMonth = 11;
        cout << "Ошибка: Дальше декабря нельзя перейти\n";
        return;
    }
    
    int newDays = getDaysInMonth(currentMonth); //Получаем количество дней в новом месяце
    map<int, vector<string>> newSchedule; //Создаём новое пустое расписание
    
    // Переносим расписание
    for (const auto& [oldDay, disciplines] : schedule) { //Перебираем все дни из старого расписания
        int newDay = oldDay; //Тот же день
        
        // Если дня нет в новом месяце - переносим на последний день
        if (newDay > newDays) { //Если старый день больше, чем дней в новом месяце
            newDay = newDays; //Переносим на последний день этого месяца
        }
        
        // Копируем дисциплины
        for (const string& disc : disciplines) {
            newSchedule[newDay].push_back(disc);
        }
    }
    
    schedule = newSchedule;
    cout << "Переход на следующий месяц (" << getMonthName(currentMonth) << ")\n";
}

// VIEW <день>
void Schedule::viewDay(int day) const {
    int daysInMonth = getDaysInMonth(currentMonth);
    
    // Проверка: существует ли день
    if (day < 1 || day > daysInMonth) {
        cout << "Ошибка: В этом месяце всего " << daysInMonth << " дней\n";
        return;
    }
    
    // Ищем дисциплины
    auto it = schedule.find(day); //Ищем день в расписании. it — итератор (указатель на найденный элемент)
    
    if (it == schedule.end() || it->second.empty()) {
        cout << "В день " << day << " мы свободны!\n";
    } else {
        cout << "В день " << day << " занятия в университете: ";
        for (size_t i = 0; i < it->second.size(); i++) {
            if (i > 0) cout << ", ";
            cout << it->second[i];
        }
        cout << "\n";
    }
}
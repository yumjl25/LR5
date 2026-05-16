#include "queue.h"
#include <iostream>
#include <iomanip>
#include <climits>

using namespace std;

// Конструктор
ElectronicQueue::ElectronicQueue(int windowCount) { //Конструктор класса (вызывается при создании объекта)
    windows.resize(windowCount); //Изменяем размер вектора windows на windowCount
    nextTicketNum = 1;
}

// Генерация номера талона (T001, T002...)
string ElectronicQueue::generateTicketNumber() {
    string ticket = "T";
    
    if (nextTicketNum < 10) {
        ticket += "00";
    } else if (nextTicketNum < 100) {
        ticket += "0";
    }
    
    ticket += to_string(nextTicketNum); //Добавляем число в конец строки
    nextTicketNum++;
    
    return ticket;
}

// Добавление посетителя в очередь
void ElectronicQueue::enqueue(int duration) {
    string ticket = generateTicketNumber(); //Генерируем новый номер талона
    waitingQueue.push_back({ticket, duration}); //Добавляем посетителя в конец очереди. {ticket, duration} создаёт структуру Visitor на месте
    cout << "Выдан талон " << ticket << "\n";
}

// Распределение посетителей по окнам
void ElectronicQueue::distribute() {
    if (windows.empty()) {
        cout << "Ошибка: нет окон для распределения\n";
        return;
    }
    
    // Для каждого посетителя в очереди
    for (const Visitor& visitor : waitingQueue) { //перебираем всех посетителей в очереди.
        // Ищем окно с минимальной загрузкой
        int minTime = INT_MAX;
        int bestWindow = 0;
        
        for (size_t i = 0; i < windows.size(); i++) { //Перебираем все окна
            if (windows[i].totalTime < minTime) {
                minTime = windows[i].totalTime;
                bestWindow = i;
            }
        }
        
        // Назначаем посетителя в лучшее окно
        windows[bestWindow].totalTime += visitor.duration; //Увеличиваем общее время окна на длительность визита
        windows[bestWindow].tickets.push_back(visitor.ticket + "(" + to_string(visitor.duration) + ")"); //Добавляем талон в список окна.
    }
    
    // Очищаем очередь
    waitingQueue.clear();
}

// Вывод результата
void ElectronicQueue::printResult() const {
    if (waitingQueue.size() > 0) {
        cout << "Сначала выполните DISTRIBUTE\n";
        return;
    }
    
    cout << "\nРезультат распределения:\n";
    for (size_t i = 0; i < windows.size(); i++) {
        cout << "Окно " << (i + 1) << ": общее время " << windows[i].totalTime << " мин, талоны: ";
        
        if (windows[i].tickets.empty()) { //Если список талонов пуст
            cout << "(нет посетителей)";
        } else {
            for (size_t j = 0; j < windows[i].tickets.size(); j++) {
                if (j > 0) cout << ", "; //Перед каждым талоном, кроме первого, ставим запятую
                cout << windows[i].tickets[j];
            }
        }
        cout << "\n";
    }
}
#include "queue.h"
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

// Глобальные переменные (определение)
vector<Visitor> waitingQueue;
vector<Window> windows;
int nextTicketNum = 1;

string generateTicketNumber() {
    string ticket = "T";
    
    if (nextTicketNum < 10) {
        ticket += "00";
    } else if (nextTicketNum < 100) {
        ticket += "0";
    }
    
    ticket += to_string(nextTicketNum);
    nextTicketNum++;
    
    return ticket;
}

void enqueue(int duration) {
    string ticket = generateTicketNumber();
    waitingQueue.push_back({ticket, duration});
    cout << "Выдан талон " << ticket << "\n";
}

void distribute() {
    if (windows.empty()) {
        cout << "Ошибка: нет окон для распределения\n";
        return;
    }
    
    // Сортируем посетителей по времени (по убыванию)
    vector<Visitor> sortedQueue = waitingQueue;
    sort(sortedQueue.begin(), sortedQueue.end(), 
         [](const Visitor& a, const Visitor& b) {
             return a.duration > b.duration;
         });
    
    // Вектор для хранения пар (время, индекс окна)
    vector<pair<int, int>> windowLoad;
    for (size_t i = 0; i < windows.size(); ++i) {
        windowLoad.push_back({0, i});
    }
    
    // Распределяем посетителей
    for (const Visitor& visitor : sortedQueue) {
        sort(windowLoad.begin(), windowLoad.end());
        int bestWindow = windowLoad[0].second;
        
        windows[bestWindow].totalTime += visitor.duration;
        windows[bestWindow].tickets.push_back(visitor.ticket + "(" + to_string(visitor.duration) + ")");
        windowLoad[0].first += visitor.duration;
    }
    
    // Сортируем талоны в каждом окне по номеру
    for (size_t i = 0; i < windows.size(); ++i) {
        sort(windows[i].tickets.begin(), windows[i].tickets.end(),
             [](const string& a, const string& b) {
                 int numA = stoi(a.substr(1, a.find('(') - 1));
                 int numB = stoi(b.substr(1, b.find('(') - 1));
                 return numA < numB;
             });
    }
    
    waitingQueue.clear();
}

void printResult() {
    if (waitingQueue.size() > 0) {
        cout << "Сначала выполните DISTRIBUTE\n";
        return;
    }
    
    cout << "\nРезультат распределения:\n";
    for (size_t i = 0; i < windows.size(); ++i) {
        cout << "Окно " << (i + 1) << ": общее время " << windows[i].totalTime << " мин, талоны: ";
        
        if (windows[i].tickets.empty()) {
            cout << "(нет посетителей)";
        } else {
            for (size_t j = 0; j < windows[i].tickets.size(); ++j) {
                if (j > 0) cout << ", ";
                cout << windows[i].tickets[j];
            }
        }
        cout << "\n";
    }
}
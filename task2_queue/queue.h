#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <vector>

using namespace std;

struct Visitor {
    string ticket;
    int duration;
};

struct Window {
    int totalTime;
    vector<string> tickets;
};

// Глобальные переменные (объявление)
extern vector<Visitor> waitingQueue;
extern vector<Window> windows;
extern int nextTicketNum;

// Объявления функций
string generateTicketNumber();
void enqueue(int duration);
void distribute();
void printResult();

#endif
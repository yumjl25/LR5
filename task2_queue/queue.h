#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <vector>

using namespace std;

// Структура посетителя
struct Visitor {
    string ticket;
    int duration;
};

// Структура окна
struct Window {
    int totalTime; // общая загрузка окна в минутах
    vector<string> tickets; // список талонов, обслуженных этим окном
    
    Window() : totalTime(0) {} // конструктор: при создании totalTime = 0
};

// Класс электронной очереди
class ElectronicQueue {
private:
    vector<Visitor> waitingQueue;   // очередь ожидания
    vector<Window> windows;         // массив окон
    int nextTicketNum;              // следующий номер талона
    
    string generateTicketNumber();
    
public:
    ElectronicQueue(int windowCount);
    
    void enqueue(int duration);
    void distribute();
    void printResult() const;
};

#endif
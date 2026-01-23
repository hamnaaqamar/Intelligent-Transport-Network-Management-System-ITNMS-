#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
using namespace std;

// Structure to represent a passenger
struct Passenger {
    int id;
    string name;
    int sourceStation;
    int destinationStation;
    Passenger(int i, string n, int src, int dest) 
        : id(i), name(n), sourceStation(src), destinationStation(dest) {}
};

// Node for linked list queue
struct QueueNode {
    Passenger data;
    QueueNode* next;
    QueueNode(Passenger p) : data(p), next(nullptr) {}
};

// Queue class using linked list (FIFO)
class Queue {
private:
    QueueNode* front;
    QueueNode* rear;
    int size;
    
public:
    Queue();
    ~Queue();
    
    // Queue operations
    void enqueue(Passenger passenger);
    Passenger dequeue();
    Passenger peek() const;
    bool isEmpty() const;
    int getSize() const;
    void display() const;
    void clear();
};

#endif


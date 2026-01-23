#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
using namespace std;

// Structure to represent an action/operation
struct Action {
    string type;  // "ADD_STATION", "DELETE_STATION", "ADD_ROUTE", etc.
    int stationId;
    string stationName;
    int sourceId;
    int destId;
    int weight;
    
    Action(string t, int sid = -1, string sname = "", int src = -1, int dest = -1, int w = 0)
        : type(t), stationId(sid), stationName(sname), sourceId(src), destId(dest), weight(w) {}
};

// Node for linked list stack
struct StackNode {
    Action data;
    StackNode* next;
    StackNode(Action a) : data(a), next(nullptr) {}
};

// Stack class using linked list (LIFO)
class Stack {
private:
    StackNode* top;
    int size;
    
public:
    Stack();
    ~Stack();
    
    // Stack operations
    void push(Action action);
    Action pop();
    Action peek() const;
    bool isEmpty() const;
    int getSize() const;
    void display() const;
    void clear();
};

#endif


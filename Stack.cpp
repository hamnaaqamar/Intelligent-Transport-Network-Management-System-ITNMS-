#include "Stack.h"
#include <iostream>

Stack::Stack() : top(nullptr), size(0) {}

Stack::~Stack() {
    clear();
}

// Push - Time: O(1), Space: O(1)
void Stack::push(Action action) {
    StackNode* newNode = new StackNode(action);
    newNode->next = top;
    top = newNode;
    size++;
}

// Pop - Time: O(1), Space: O(1)
Action Stack::pop() {
    if (isEmpty()) {
        return Action("EMPTY");
    }
    
    StackNode* temp = top;
    Action action = top->data;
    top = top->next;
    delete temp;
    size--;
    
    return action;
}

// Peek - Time: O(1), Space: O(1)
Action Stack::peek() const {
    if (isEmpty()) {
        return Action("EMPTY");
    }
    return top->data;
}

bool Stack::isEmpty() const {
    return top == nullptr;
}

int Stack::getSize() const {
    return size;
}

// Display - Time: O(n), Space: O(1)
void Stack::display() const {
    if (isEmpty()) {
        cout << "History stack is empty!" << endl;
        return;
    }
    
    cout << "\n=== Operation History (LIFO) ===" << endl;
    StackNode* current = top;
    int position = 1;
    
    while (current != nullptr) {
        cout << position << ". " << current->data.type;
        if (current->data.type == "ADD_STATION" || current->data.type == "DELETE_STATION") {
            cout << " - Station ID: " << current->data.stationId 
                 << ", Name: " << current->data.stationName;
        } else if (current->data.type == "ADD_ROUTE" || current->data.type == "DELETE_ROUTE") {
            cout << " - Route: " << current->data.sourceId 
                 << " -> " << current->data.destId 
                 << " (weight: " << current->data.weight << ")";
        }
        cout << endl;
        current = current->next;
        position++;
    }
    cout << "Total operations: " << size << endl;
}

void Stack::clear() {
    while (!isEmpty()) {
        pop();
    }
}


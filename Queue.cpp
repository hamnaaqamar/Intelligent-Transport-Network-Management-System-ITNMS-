#include "Queue.h"
#include <iostream>

Queue::Queue() : front(nullptr), rear(nullptr), size(0) {}

Queue::~Queue() {
    clear();
}

// Enqueue - Time: O(1), Space: O(1)
void Queue::enqueue(Passenger passenger) {
    QueueNode* newNode = new QueueNode(passenger);
    
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
    cout << "Passenger " << passenger.name << " (ID: " << passenger.id 
         << ") added to queue." << endl;
}

// Dequeue - Time: O(1), Space: O(1)
Passenger Queue::dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty!" << endl;
        return Passenger(-1, "", -1, -1);
    }
    
    QueueNode* temp = front;
    Passenger passenger = front->data;
    front = front->next;
    
    if (front == nullptr) {
        rear = nullptr;
    }
    
    delete temp;
    size--;
    return passenger;
}

// Peek - Time: O(1), Space: O(1)
Passenger Queue::peek() const {
    if (isEmpty()) {
        return Passenger(-1, "", -1, -1);
    }
    return front->data;
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

int Queue::getSize() const {
    return size;
}

// Display - Time: O(n), Space: O(1)
void Queue::display() const {
    if (isEmpty()) {
        cout << "Queue is empty!" << endl;
        return;
    }
    
    cout << "\n=== Passenger Queue (FIFO) ===" << endl;
    QueueNode* current = front;
    int position = 1;
    
    while (current != nullptr) {
        cout << position << ". Passenger ID: " << current->data.id 
             << " | Name: " << current->data.name
             << " | Route: Station " << current->data.sourceStation 
             << " -> Station " << current->data.destinationStation << endl;
        current = current->next;
        position++;
    }
    cout << "Total passengers in queue: " << size << endl;
}

void Queue::clear() {
    while (!isEmpty()) {
        dequeue();
    }
}


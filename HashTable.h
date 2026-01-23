#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
using namespace std;

// Structure to represent a vehicle
struct Vehicle {
    int id;
    string type;  // "Bus", "Metro", "Train", etc.
    string model;
    int capacity;
    double speed;  // km/h
    Vehicle* next;  // For manual linked list
    
    Vehicle(int i, string t, string m, int c, double s)
        : id(i), type(t), model(m), capacity(c), speed(s), next(nullptr) {}
};

// Manual linked list for hash table chaining
class VehicleList {
private:
    Vehicle* head;
    
public:
    VehicleList() : head(nullptr) {}
    
    ~VehicleList() {
        clear();
    }
    
    void push_back(Vehicle* vehicle) {
        if (head == nullptr) {
            head = vehicle;
        } else {
            Vehicle* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = vehicle;
        }
    }
    
    void clear() {
        while (head != nullptr) {
            Vehicle* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    bool empty() const {
        return head == nullptr;
    }
    
    int size() const {
        int count = 0;
        Vehicle* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
    
    Vehicle* begin() const { return head; }
    Vehicle* end() const { return nullptr; }
    
    Vehicle* find(int id) const {
        Vehicle* current = head;
        while (current != nullptr) {
            if (current->id == id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    
    bool remove(int id) {
        if (head == nullptr) return false;
        
        // If head needs to be removed
        if (head->id == id) {
            Vehicle* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        
        // Find and remove
        Vehicle* current = head;
        while (current->next != nullptr) {
            if (current->next->id == id) {
                Vehicle* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

// Hash Table class with chaining (using manual linked lists)
class HashTable {
private:
    static const int TABLE_SIZE = 101;  // Prime number for better distribution
    VehicleList table[TABLE_SIZE];  // Manual linked list instead of std::list
    int numVehicles;
    
    // Hash function - Time: O(1), Space: O(1)
    int hashFunction(int key) const {
        return key % TABLE_SIZE;
    }
    
public:
    HashTable();
    
    // Hash table operations
    void insert(Vehicle vehicle);
    Vehicle* search(int id);
    bool remove(int id);
    void display() const;
    void displayVehicle(int id) const;
    int getNumVehicles() const { return numVehicles; }
    
    // Statistics
    double getLoadFactor() const;
    int getLongestChain() const;
};

#endif


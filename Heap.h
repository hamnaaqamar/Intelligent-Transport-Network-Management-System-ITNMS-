#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
using namespace std;

// Structure for vehicle priority (min-heap for fastest vehicle)
struct VehiclePriority {
    int vehicleId;
    double speed;
    int capacity;
    string type;
    
    VehiclePriority(int id, double s, int c, string t)
        : vehicleId(id), speed(s), capacity(c), type(t) {}
    
    bool operator>(const VehiclePriority& other) const {
        // For min-heap: higher speed = higher priority
        if (speed != other.speed) {
            return speed > other.speed;
        }
        return capacity > other.capacity;
    }
    
    bool operator<(const VehiclePriority& other) const {
        return !(*this > other);
    }
};

// Min-Heap class (Priority Queue)
class Heap {
private:
    vector<VehiclePriority> heap;
    
    // Helper functions
    void heapifyUp(int index);
    void heapifyDown(int index);
    int parent(int index) const { return (index - 1) / 2; }
    int leftChild(int index) const { return 2 * index + 1; }
    int rightChild(int index) const { return 2 * index + 2; }
    
public:
    Heap();
    
    // Heap operations
    void insert(VehiclePriority vehicle);
    VehiclePriority extractMin();
    VehiclePriority peek() const;
    bool isEmpty() const;
    int getSize() const;
    void display() const;
    void clear();
    
    // Heap sort - Time: O(n log n), Space: O(1)
    static void heapSort(vector<VehiclePriority>& arr);
};

#endif


#include "Heap.h"
#include <iostream>

Heap::Heap() {
    heap.clear();
}

// Insert - Time: O(log n), Space: O(1)
void Heap::insert(VehiclePriority vehicle) {
    heap.push_back(vehicle);
    heapifyUp(heap.size() - 1);
}

// Heapify Up - Time: O(log n), Space: O(1)
void Heap::heapifyUp(int index) {
    while (index > 0 && heap[parent(index)] > heap[index]) {
        // Manual swap
        VehiclePriority temp = heap[parent(index)];
        heap[parent(index)] = heap[index];
        heap[index] = temp;
        index = parent(index);
    }
}

// Extract Min - Time: O(log n), Space: O(1)
VehiclePriority Heap::extractMin() {
    if (isEmpty()) {
        return VehiclePriority(-1, 0.0, 0, "");
    }
    
    VehiclePriority min = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    
    if (!isEmpty()) {
        heapifyDown(0);
    }
    
    return min;
}

// Heapify Down - Time: O(log n), Space: O(1)
void Heap::heapifyDown(int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (left < static_cast<int>(heap.size()) && heap[left] < heap[smallest]) {
        smallest = left;
    }
    
    if (right < static_cast<int>(heap.size()) && heap[right] < heap[smallest]) {
        smallest = right;
    }
    
    if (smallest != index) {
        // Manual swap
        VehiclePriority temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        heapifyDown(smallest);
    }
}

VehiclePriority Heap::peek() const {
    if (isEmpty()) {
        return VehiclePriority(-1, 0.0, 0, "");
    }
    return heap[0];
}

bool Heap::isEmpty() const {
    return heap.empty();
}

int Heap::getSize() const {
    return heap.size();
}

// Display - Time: O(n), Space: O(1)
void Heap::display() const {
    if (isEmpty()) {
        cout << "Heap is empty!" << endl;
        return;
    }
    
    cout << "\n=== Vehicle Priority Queue (Min-Heap) ===" << endl;
    vector<VehiclePriority> temp = heap;
    int position = 1;
    
    while (!temp.empty()) {
        Heap tempHeap;
        for (const auto& v : temp) {
            tempHeap.insert(v);
        }
        VehiclePriority min = tempHeap.extractMin();
        cout << position << ". Vehicle ID: " << min.vehicleId
             << " | Type: " << min.type
             << " | Speed: " << min.speed << " km/h"
             << " | Capacity: " << min.capacity << endl;
        
        // Manual removal (no remove_if)
        for (auto it = temp.begin(); it != temp.end(); ) {
            if (it->vehicleId == min.vehicleId) {
                it = temp.erase(it);
            } else {
                ++it;
            }
        }
        position++;
    }
}

void Heap::clear() {
    heap.clear();
}

// Heap Sort - Time: O(n log n), Space: O(1)
void Heap::heapSort(vector<VehiclePriority>& arr) {
    int n = arr.size();
    
    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        int parent = i;
        while (true) {
            int smallest = parent;
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            
            if (left < n && arr[left] < arr[smallest]) {
                smallest = left;
            }
            if (right < n && arr[right] < arr[smallest]) {
                smallest = right;
            }
            
            if (smallest == parent) break;
            
            // Manual swap
            VehiclePriority temp = arr[parent];
            arr[parent] = arr[smallest];
            arr[smallest] = temp;
            parent = smallest;
        }
    }
    
    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        // Manual swap
        VehiclePriority temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        int parent = 0;
        while (true) {
            int smallest = parent;
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            
            if (left < i && arr[left] < arr[smallest]) {
                smallest = left;
            }
            if (right < i && arr[right] < arr[smallest]) {
                smallest = right;
            }
            
            if (smallest == parent) break;
            
            // Manual swap
            VehiclePriority temp = arr[parent];
            arr[parent] = arr[smallest];
            arr[smallest] = temp;
            parent = smallest;
        }
    }
}


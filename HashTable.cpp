#include "HashTable.h"
#include <iostream>

HashTable::HashTable() : numVehicles(0) {
    // VehicleList objects are default constructed (head = nullptr)
}

// Insert - Average Time: O(1), Worst: O(n), Space: O(1)
void HashTable::insert(Vehicle vehicle) {
    int index = hashFunction(vehicle.id);
    
    // Check if vehicle already exists
    Vehicle* existing = table[index].find(vehicle.id);
    if (existing != nullptr) {
        cout << "Vehicle with ID " << vehicle.id << " already exists! Updating..." << endl;
        existing->type = vehicle.type;
        existing->model = vehicle.model;
        existing->capacity = vehicle.capacity;
        existing->speed = vehicle.speed;
        return;
    }
    
    // Create new vehicle node
    Vehicle* newVehicle = new Vehicle(vehicle.id, vehicle.type, vehicle.model, 
                                      vehicle.capacity, vehicle.speed);
    table[index].push_back(newVehicle);
    numVehicles++;
    cout << "Vehicle " << vehicle.id << " (" << vehicle.type << " - " 
         << vehicle.model << ") inserted successfully!" << endl;
}

// Search - Average Time: O(1), Worst: O(n), Space: O(1)
Vehicle* HashTable::search(int id) {
    int index = hashFunction(id);
    return table[index].find(id);
}

// Remove - Average Time: O(1), Worst: O(n), Space: O(1)
bool HashTable::remove(int id) {
    int index = hashFunction(id);
    
    if (table[index].remove(id)) {
        numVehicles--;
        cout << "Vehicle " << id << " removed successfully!" << endl;
        return true;
    }
    
    cout << "Vehicle " << id << " not found!" << endl;
    return false;
}

// Display - Time: O(n), Space: O(1)
void HashTable::display() const {
    cout << "\n=== Vehicle Database ===" << endl;
    if (numVehicles == 0) {
        cout << "No vehicles in database." << endl;
        return;
    }
    
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Vehicle* current = table[i].begin();
        while (current != nullptr) {
            count++;
            cout << count << ". ID: " << current->id 
                 << " | Type: " << current->type
                 << " | Model: " << current->model
                 << " | Capacity: " << current->capacity
                 << " | Speed: " << current->speed << " km/h" << endl;
            current = current->next;
        }
    }
    cout << "\nTotal vehicles: " << numVehicles << endl;
    cout << "Load factor: " << getLoadFactor() << endl;
}

void HashTable::displayVehicle(int id) const {
    int index = hashFunction(id);
    Vehicle* vehicle = table[index].find(id);
    
    if (vehicle != nullptr) {
        cout << "\n=== Vehicle Details ===" << endl;
        cout << "ID: " << vehicle->id << endl;
        cout << "Type: " << vehicle->type << endl;
        cout << "Model: " << vehicle->model << endl;
        cout << "Capacity: " << vehicle->capacity << " passengers" << endl;
        cout << "Speed: " << vehicle->speed << " km/h" << endl;
    } else {
        cout << "Vehicle " << id << " not found!" << endl;
    }
}

double HashTable::getLoadFactor() const {
    return (double)numVehicles / TABLE_SIZE;
}

int HashTable::getLongestChain() const {
    int maxChain = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        int chainSize = table[i].size();
        if (chainSize > maxChain) {
            maxChain = chainSize;
        }
    }
    return maxChain;
}


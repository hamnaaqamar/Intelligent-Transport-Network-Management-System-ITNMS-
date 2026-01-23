#ifndef ANALYTICS_H
#define ANALYTICS_H

#include "Graph.h"
#include "HashTable.h"
#include "BST.h"
#include "Heap.h"
#include <iostream>
#include <vector>
using namespace std;

// Manual hash map implementation for station frequency tracking
struct FrequencyNode {
    int stationId;
    int count;
    FrequencyNode* next;
    FrequencyNode(int id, int c) : stationId(id), count(c), next(nullptr) {}
};

class ManualHashMap {
private:
    static const int MAP_SIZE = 101;
    FrequencyNode* buckets[MAP_SIZE];
    
    int hashFunction(int key) const {
        return key % MAP_SIZE;
    }
    
public:
    ManualHashMap() {
        for (int i = 0; i < MAP_SIZE; i++) {
            buckets[i] = nullptr;
        }
    }
    
    ~ManualHashMap() {
        for (int i = 0; i < MAP_SIZE; i++) {
            FrequencyNode* current = buckets[i];
            while (current != nullptr) {
                FrequencyNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
    
    void increment(int key) {
        int index = hashFunction(key);
        FrequencyNode* current = buckets[index];
        
        while (current != nullptr) {
            if (current->stationId == key) {
                current->count++;
                return;
            }
            current = current->next;
        }
        
        // Not found, insert new
        FrequencyNode* newNode = new FrequencyNode(key, 1);
        newNode->next = buckets[index];
        buckets[index] = newNode;
    }
    
    int get(int key) const {
        int index = hashFunction(key);
        FrequencyNode* current = buckets[index];
        
        while (current != nullptr) {
            if (current->stationId == key) {
                return current->count;
            }
            current = current->next;
        }
        return 0;
    }
    
    bool empty() const {
        for (int i = 0; i < MAP_SIZE; i++) {
            if (buckets[i] != nullptr) return false;
        }
        return true;
    }
    
    void clear() {
        for (int i = 0; i < MAP_SIZE; i++) {
            FrequencyNode* current = buckets[i];
            while (current != nullptr) {
                FrequencyNode* temp = current;
                current = current->next;
                delete temp;
            }
            buckets[i] = nullptr;
        }
    }
    
    // Get all pairs for iteration
    vector<pair<int, int>> getAllPairs() const {
        vector<pair<int, int>> result;
        for (int i = 0; i < MAP_SIZE; i++) {
            FrequencyNode* current = buckets[i];
            while (current != nullptr) {
                result.push_back({current->stationId, current->count});
                current = current->next;
            }
        }
        return result;
    }
};

class Analytics {
private:
    Graph* transportGraph;
    HashTable* vehicleDB;
    BST* routeMetadata;
    Heap* vehiclePriority;
    
    // Station frequency tracking - Manual hash map implementation
    ManualHashMap stationFrequency;
    
    // Manual sorting functions
    void sortPairsDescending(vector<pair<int, int>>& pairs);
    void sortRoutesByPassengers(vector<RouteMetadata>& routes);
    void sortDensityData(vector<pair<int, int>>& data);
    
public:
    Analytics(Graph* g, HashTable* h, BST* b, Heap* hp);
    
    // Analytics functions
    void mostCrowdedStation();
    void busiestRoute();
    void fastestVehicleAssignment();
    void trafficDensityPrediction();
    void dailyUsageTrends();
    void generateReport();
    
    // Helper functions
    void updateStationFrequency(int stationId);
    void resetStatistics();
};

#endif


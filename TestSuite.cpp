/**
 * Test Suite for Intelligent Transport Network Management System (ITNMS)
 * 
 * This file contains comprehensive tests for all modules and algorithms.
 * Run this file to verify correctness and measure performance.
 * 
 * Compilation: g++ -std=c++11 -o test_suite TestSuite.cpp Graph.cpp Queue.cpp 
 *              Stack.cpp HashTable.cpp BST.cpp Heap.cpp SearchSort.cpp Analytics.cpp
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cassert>
#include "Graph.h"
#include "Queue.h"
#include "Stack.h"
#include "HashTable.h"
#include "BST.h"
#include "Heap.h"
#include "SearchSort.h"
#include "Analytics.h"

using namespace std;
using namespace std::chrono;

// Test result structure
struct TestResult {
    string testName;
    bool passed;
    double executionTime; // in milliseconds
    string message;
};

vector<TestResult> testResults;

// Helper function to record test results
void recordTest(const string& name, bool passed, double time, const string& msg = "") {
    TestResult result;
    result.testName = name;
    result.passed = passed;
    result.executionTime = time;
    result.message = msg;
    testResults.push_back(result);
    
    cout << (passed ? "[PASS]" : "[FAIL]") << " " << name;
    if (!msg.empty()) cout << " - " << msg;
    cout << " (" << fixed << setprecision(3) << time << " ms)" << endl;
}

// ==================== GRAPH TESTS ====================

void testGraphOperations() {
    cout << "\n=== Testing Graph Operations ===" << endl;
    
    Graph graph(10);
    auto start = high_resolution_clock::now();
    
    // Test 1: Add Stations
    graph.addStation(0, "Downtown");
    graph.addStation(1, "Airport");
    graph.addStation(2, "University");
    graph.addStation(3, "Mall");
    graph.addStation(4, "Hospital");
    
    auto end = high_resolution_clock::now();
    double time = duration<double, milli>(end - start).count();
    recordTest("Add Stations", graph.stationExists(0) && graph.stationExists(4), time);
    
    // Test 2: Add Routes
    start = high_resolution_clock::now();
    graph.addRoute(0, 1, 10);
    graph.addRoute(1, 2, 15);
    graph.addRoute(0, 2, 20);
    graph.addRoute(2, 3, 8);
    graph.addRoute(3, 4, 12);
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Add Routes", true, time);
    
    // Test 3: BFS
    start = high_resolution_clock::now();
    vector<int> bfsResult = graph.BFS(0);
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("BFS Traversal", bfsResult.size() > 0, time, 
               "Visited " + to_string(bfsResult.size()) + " stations");
    
    // Test 4: DFS
    start = high_resolution_clock::now();
    vector<int> dfsResult = graph.DFS(0);
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("DFS Traversal", dfsResult.size() > 0, time,
               "Visited " + to_string(dfsResult.size()) + " stations");
    
    // Test 5: Shortest Path (Dijkstra)
    start = high_resolution_clock::now();
    vector<int> path = graph.shortestPath(0, 4);
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Shortest Path (Dijkstra)", !path.empty(), time,
               "Path length: " + to_string(path.size()));
    
    // Test 6: MST
    start = high_resolution_clock::now();
    vector<pair<pair<int, int>, int>> mst = graph.minimumSpanningTree();
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Minimum Spanning Tree", !mst.empty(), time,
               "MST edges: " + to_string(mst.size()));
    
    // Test 7: Cycle Detection
    start = high_resolution_clock::now();
    bool hasCycle = graph.detectCycle();
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Cycle Detection", true, time, 
               hasCycle ? "Cycle found" : "No cycle");
}

// ==================== QUEUE TESTS ====================

void testQueueOperations() {
    cout << "\n=== Testing Queue Operations ===" << endl;
    
    Queue queue;
    auto start = high_resolution_clock::now();
    
    // Test 1: Enqueue
    queue.enqueue(Passenger(1, "Alice", 0, 2));
    queue.enqueue(Passenger(2, "Bob", 1, 3));
    queue.enqueue(Passenger(3, "Charlie", 0, 4));
    
    auto end = high_resolution_clock::now();
    double time = duration<double, milli>(end - start).count();
    recordTest("Enqueue Operations", queue.getSize() == 3, time);
    
    // Test 2: Peek
    start = high_resolution_clock::now();
    Passenger p = queue.peek();
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Peek Operation", p.id == 1, time, "First passenger: " + p.name);
    
    // Test 3: Dequeue (FIFO)
    start = high_resolution_clock::now();
    Passenger p1 = queue.dequeue();
    Passenger p2 = queue.dequeue();
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Dequeue Operations (FIFO)", p1.id == 1 && p2.id == 2, time);
    
    // Test 4: Empty Queue
    Queue emptyQueue;
    recordTest("Empty Queue Check", emptyQueue.isEmpty(), 0.0);
}

// ==================== STACK TESTS ====================

void testStackOperations() {
    cout << "\n=== Testing Stack Operations ===" << endl;
    
    Stack stack;
    auto start = high_resolution_clock::now();
    
    // Test 1: Push
    stack.push(Action("ADD_STATION", 0, "Downtown"));
    stack.push(Action("ADD_ROUTE", -1, "", 0, 1, 10));
    stack.push(Action("DELETE_STATION", 2, "Old Station"));
    
    auto end = high_resolution_clock::now();
    double time = duration<double, milli>(end - start).count();
    recordTest("Push Operations", stack.getSize() == 3, time);
    
    // Test 2: Peek
    start = high_resolution_clock::now();
    Action top = stack.peek();
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Peek Operation", top.type == "DELETE_STATION", time);
    
    // Test 3: Pop (LIFO)
    start = high_resolution_clock::now();
    Action a1 = stack.pop();
    Action a2 = stack.pop();
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Pop Operations (LIFO)", 
               a1.type == "DELETE_STATION" && a2.type == "ADD_ROUTE", time);
}

// ==================== HASH TABLE TESTS ====================

void testHashTableOperations() {
    cout << "\n=== Testing Hash Table Operations ===" << endl;
    
    HashTable hashTable;
    auto start = high_resolution_clock::now();
    
    // Test 1: Insert
    hashTable.insert(Vehicle(100, "Bus", "CityBus", 50, 60.0));
    hashTable.insert(Vehicle(101, "Metro", "FastTrain", 200, 80.0));
    hashTable.insert(Vehicle(102, "Bus", "ExpressBus", 60, 70.0));
    
    auto end = high_resolution_clock::now();
    double time = duration<double, milli>(end - start).count();
    recordTest("Hash Table Insert", hashTable.getNumVehicles() == 3, time);
    
    // Test 2: Search
    start = high_resolution_clock::now();
    Vehicle* v = hashTable.search(101);
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Hash Table Search", v != nullptr && v->type == "Metro", time);
    
    // Test 3: Remove
    start = high_resolution_clock::now();
    bool removed = hashTable.remove(102);
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Hash Table Remove", removed && hashTable.getNumVehicles() == 2, time);
    
    // Test 4: Load Factor
    double loadFactor = hashTable.getLoadFactor();
    recordTest("Load Factor Calculation", loadFactor > 0, 0.0,
               "Load factor: " + to_string(loadFactor));
}

// ==================== BST TESTS ====================

void testBSTOperations() {
    cout << "\n=== Testing BST Operations ===" << endl;
    
    BST bst;
    auto start = high_resolution_clock::now();
    
    // Test 1: Insert
    bst.insert(RouteMetadata(5, "Route A", 100, 15.5));
    bst.insert(RouteMetadata(3, "Route B", 150, 20.0));
    bst.insert(RouteMetadata(7, "Route C", 80, 12.0));
    bst.insert(RouteMetadata(1, "Route D", 200, 25.0));
    bst.insert(RouteMetadata(9, "Route E", 90, 18.0));
    
    auto end = high_resolution_clock::now();
    double time = duration<double, milli>(end - start).count();
    recordTest("BST Insert", bst.getSize() == 5, time);
    
    // Test 2: Search
    start = high_resolution_clock::now();
    RouteMetadata* route = bst.search(7);
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("BST Search", route != nullptr && route->routeName == "Route C", time);
    
    // Test 3: Traversal
    start = high_resolution_clock::now();
    vector<RouteMetadata> routes = bst.getAllRoutes();
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("BST Inorder Traversal", routes.size() == 5, time);
    
    // Test 4: Delete
    start = high_resolution_clock::now();
    bool deleted = bst.remove(3);
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("BST Delete", deleted && bst.getSize() == 4, time);
}

// ==================== HEAP TESTS ====================

void testHeapOperations() {
    cout << "\n=== Testing Heap Operations ===" << endl;
    
    Heap heap;
    auto start = high_resolution_clock::now();
    
    // Test 1: Insert
    heap.insert(VehiclePriority(100, 60.0, 50, "Bus"));
    heap.insert(VehiclePriority(101, 80.0, 200, "Metro"));
    heap.insert(VehiclePriority(102, 70.0, 60, "Bus"));
    heap.insert(VehiclePriority(103, 90.0, 150, "Train"));
    
    auto end = high_resolution_clock::now();
    double time = duration<double, milli>(end - start).count();
    recordTest("Heap Insert", heap.getSize() == 4, time);
    
    // Test 2: Peek (Min-Heap - fastest vehicle)
    start = high_resolution_clock::now();
    VehiclePriority fastest = heap.peek();
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Heap Peek (Fastest)", fastest.vehicleId == 103 && fastest.speed == 90.0, time);
    
    // Test 3: Extract Min
    start = high_resolution_clock::now();
    VehiclePriority v1 = heap.extractMin();
    VehiclePriority v2 = heap.extractMin();
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Heap Extract Min", v1.speed == 90.0 && v2.speed == 80.0, time);
}

// ==================== SEARCHING TESTS ====================

void testSearchingAlgorithms() {
    cout << "\n=== Testing Searching Algorithms ===" << endl;
    
    vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    int key = 7;
    
    // Test 1: Linear Search
    auto start = high_resolution_clock::now();
    int linearIndex = SearchSort::linearSearch(data, key);
    auto end = high_resolution_clock::now();
    double time = duration<double, milli>(end - start).count();
    recordTest("Linear Search", linearIndex == 6, time, 
               "Found at index " + to_string(linearIndex));
    
    // Test 2: Binary Search (requires sorted array)
    vector<int> sortedData = data;
    SearchSort::bubbleSort(sortedData);
    start = high_resolution_clock::now();
    int binaryIndex = SearchSort::binarySearch(sortedData, key);
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Binary Search", binaryIndex >= 0 && sortedData[binaryIndex] == key, time,
               "Found at index " + to_string(binaryIndex));
}

// ==================== SORTING TESTS ====================

void testSortingAlgorithms() {
    cout << "\n=== Testing Sorting Algorithms ===" << endl;
    
    vector<int> original = {64, 34, 25, 12, 22, 11, 90, 5};
    vector<int> sorted = {5, 11, 12, 22, 25, 34, 64, 90};
    
    // Test each sorting algorithm
    vector<pair<string, void(*)(vector<int>&)>> algorithms = {
        {"Bubble Sort", SearchSort::bubbleSort},
        {"Selection Sort", SearchSort::selectionSort},
        {"Insertion Sort", SearchSort::insertionSort},
        {"Merge Sort", SearchSort::mergeSort},
        {"Quick Sort", SearchSort::quickSort},
        {"Heap Sort", SearchSort::heapSort},
        {"Counting Sort", SearchSort::countingSort},
        {"Radix Sort", SearchSort::radixSort}
    };
    
    for (auto& algo : algorithms) {
        vector<int> testData = original;
        auto start = high_resolution_clock::now();
        algo.second(testData);
        auto end = high_resolution_clock::now();
        double time = duration<double, milli>(end - start).count();
        
        bool correct = (testData == sorted);
        recordTest(algo.first, correct, time);
        
        if (!correct) {
            cout << "  Expected: ";
            for (int x : sorted) cout << x << " ";
            cout << "\n  Got: ";
            for (int x : testData) cout << x << " ";
            cout << endl;
        }
    }
}

// ==================== PERFORMANCE TESTS ====================

void performanceTest() {
    cout << "\n=== Performance Tests ===" << endl;
    
    // Test sorting algorithms with different sizes
    vector<int> sizes = {100, 500, 1000, 5000};
    
    for (int size : sizes) {
        cout << "\nTesting with " << size << " elements:" << endl;
        
        // Generate random data
        vector<int> data(size);
        for (int i = 0; i < size; i++) {
            data[i] = rand() % 1000;
        }
        
        // Test Quick Sort
        vector<int> qsData = data;
        auto start = high_resolution_clock::now();
        SearchSort::quickSort(qsData);
        auto end = high_resolution_clock::now();
        double qsTime = duration<double, milli>(end - start).count();
        
        // Test Merge Sort
        vector<int> msData = data;
        start = high_resolution_clock::now();
        SearchSort::mergeSort(msData);
        end = high_resolution_clock::now();
        double msTime = duration<double, milli>(end - start).count();
        
        // Test Heap Sort
        vector<int> hsData = data;
        start = high_resolution_clock::now();
        SearchSort::heapSort(hsData);
        end = high_resolution_clock::now();
        double hsTime = duration<double, milli>(end - start).count();
        
        cout << "  Quick Sort: " << fixed << setprecision(3) << qsTime << " ms" << endl;
        cout << "  Merge Sort: " << msTime << " ms" << endl;
        cout << "  Heap Sort: " << hsTime << " ms" << endl;
    }
}

// ==================== ANALYTICS TESTS ====================

void testAnalytics() {
    cout << "\n=== Testing Analytics Module ===" << endl;
    
    // Setup test data
    Graph graph(10);
    HashTable vehicleDB;
    BST routeMetadata;
    Heap vehicleHeap;
    
    // Add stations
    graph.addStation(0, "Downtown");
    graph.addStation(1, "Airport");
    graph.addStation(2, "University");
    
    // Add routes
    graph.addRoute(0, 1, 10);
    graph.addRoute(1, 2, 15);
    
    // Add vehicles
    vehicleDB.insert(Vehicle(100, "Bus", "CityBus", 50, 60.0));
    vehicleDB.insert(Vehicle(101, "Metro", "FastTrain", 200, 80.0));
    vehicleHeap.insert(VehiclePriority(100, 60.0, 50, "Bus"));
    vehicleHeap.insert(VehiclePriority(101, 80.0, 200, "Metro"));
    
    // Add route metadata
    routeMetadata.insert(RouteMetadata(1, "Route A", 100, 15.5));
    routeMetadata.insert(RouteMetadata(2, "Route B", 150, 20.0));
    
    Analytics analytics(&graph, &vehicleDB, &routeMetadata, &vehicleHeap);
    
    // Update station frequency
    analytics.updateStationFrequency(0);
    analytics.updateStationFrequency(0);
    analytics.updateStationFrequency(1);
    
    // Test analytics functions
    auto start = high_resolution_clock::now();
    analytics.mostCrowdedStation();
    auto end = high_resolution_clock::now();
    double time = duration<double, milli>(end - start).count();
    recordTest("Most Crowded Station", true, time);
    
    start = high_resolution_clock::now();
    analytics.busiestRoute();
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Busiest Route", true, time);
    
    start = high_resolution_clock::now();
    analytics.fastestVehicleAssignment();
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Fastest Vehicle Assignment", true, time);
    
    start = high_resolution_clock::now();
    analytics.trafficDensityPrediction();
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Traffic Density Prediction", true, time);
    
    start = high_resolution_clock::now();
    analytics.dailyUsageTrends();
    end = high_resolution_clock::now();
    time = duration<double, milli>(end - start).count();
    recordTest("Daily Usage Trends", true, time);
}

// ==================== MAIN TEST RUNNER ====================

void printSummary() {
    cout << "\n" << string(70, '=') << endl;
    cout << "                      TEST SUMMARY" << endl;
    cout << string(70, '=') << endl;
    
    int passed = 0;
    int failed = 0;
    double totalTime = 0.0;
    
    for (const auto& result : testResults) {
        if (result.passed) passed++;
        else failed++;
        totalTime += result.executionTime;
    }
    
    cout << "Total Tests: " << testResults.size() << endl;
    cout << "Passed: " << passed << endl;
    cout << "Failed: " << failed << endl;
    cout << "Total Execution Time: " << fixed << setprecision(3) << totalTime << " ms" << endl;
    cout << "Average Time per Test: " << (totalTime / testResults.size()) << " ms" << endl;
    
    if (failed > 0) {
        cout << "\nFailed Tests:" << endl;
        for (const auto& result : testResults) {
            if (!result.passed) {
                cout << "  - " << result.testName;
                if (!result.message.empty()) cout << ": " << result.message;
                cout << endl;
            }
        }
    }
    
    cout << string(70, '=') << endl;
}

int main() {
    cout << "\n" << string(70, '=') << endl;
    cout << "     INTELLIGENT TRANSPORT NETWORK MANAGEMENT SYSTEM" << endl;
    cout << "                    TEST SUITE" << endl;
    cout << string(70, '=') << endl;
    
    // Run all tests
    testGraphOperations();
    testQueueOperations();
    testStackOperations();
    testHashTableOperations();
    testBSTOperations();
    testHeapOperations();
    testSearchingAlgorithms();
    testSortingAlgorithms();
    testAnalytics();
    
    // Performance tests
    performanceTest();
    
    // Print summary
    printSummary();
    
    return 0;
}


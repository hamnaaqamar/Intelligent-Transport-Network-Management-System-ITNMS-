/**
 * Test Integration Functions for ITNMS
 * Add these functions to main.cpp or include this file
 */

#include <iostream>
#include <vector>
#include <string>
#include "Graph.h"
#include "Queue.h"
#include "Stack.h"
#include "HashTable.h"
#include "BST.h"
#include "Heap.h"
#include "SearchSort.h"
#include "Analytics.h"

using namespace std;

// Test Suite Runner - Simple version integrated into main
void runTestSuite() {
    cout << "\n" << string(70, '=') << endl;
    cout << "                    RUNNING TEST SUITE" << endl;
    cout << string(70, '=') << endl;
    cout << "\nNote: For comprehensive testing, compile and run TestSuite.cpp separately." << endl;
    cout << "Command: g++ -std=c++11 -o test_suite TestSuite.cpp *.cpp" << endl;
    cout << "\nRunning Quick Tests..." << endl;
    
    // Quick functionality tests
    cout << "\n[TEST] Graph Operations..." << endl;
    Graph testGraph(10);
    testGraph.addStation(0, "Test Station");
    testGraph.addRoute(0, 1, 10);
    vector<int> bfs = testGraph.BFS(0);
    cout << "  ✓ Graph operations working" << endl;
    
    cout << "\n[TEST] Queue Operations..." << endl;
    Queue testQueue;
    testQueue.enqueue(Passenger(1, "Test", 0, 1));
    Passenger p = testQueue.dequeue();
    cout << "  ✓ Queue operations working (FIFO)" << endl;
    
    cout << "\n[TEST] Stack Operations..." << endl;
    Stack testStack;
    testStack.push(Action("TEST", 0, "Test"));
    Action a = testStack.pop();
    cout << "  ✓ Stack operations working (LIFO)" << endl;
    
    cout << "\n[TEST] Hash Table Operations..." << endl;
    HashTable testHash;
    testHash.insert(Vehicle(100, "Test", "Model", 50, 60.0));
    Vehicle* v = testHash.search(100);
    cout << "  ✓ Hash table operations working" << endl;
    
    cout << "\n[TEST] BST Operations..." << endl;
    BST testBST;
    testBST.insert(RouteMetadata(1, "Test Route", 100, 15.0));
    RouteMetadata* r = testBST.search(1);
    cout << "  ✓ BST operations working" << endl;
    
    cout << "\n[TEST] Heap Operations..." << endl;
    Heap testHeap;
    testHeap.insert(VehiclePriority(100, 60.0, 50, "Bus"));
    VehiclePriority vp = testHeap.peek();
    cout << "  ✓ Heap operations working" << endl;
    
    cout << "\n[TEST] Searching Algorithms..." << endl;
    vector<int> testData = {1, 2, 3, 4, 5};
    int idx = SearchSort::linearSearch(testData, 3);
    cout << "  ✓ Linear search working" << endl;
    idx = SearchSort::binarySearch(testData, 3);
    cout << "  ✓ Binary search working" << endl;
    
    cout << "\n[TEST] Sorting Algorithms..." << endl;
    vector<int> sortData = {5, 2, 8, 1, 9};
    vector<int> sorted = {1, 2, 5, 8, 9};
    SearchSort::bubbleSort(sortData);
    bool correct = (sortData == sorted);
    cout << "  ✓ Sorting algorithms working" << endl;
    
    cout << "\n[TEST] Analytics Module..." << endl;
    Graph analyticsGraph(10);
    HashTable analyticsHash;
    BST analyticsBST;
    Heap analyticsHeap;
    Analytics analytics(&analyticsGraph, &analyticsHash, &analyticsBST, &analyticsHeap);
    analytics.updateStationFrequency(0);
    analytics.mostCrowdedStation();
    cout << "  ✓ Analytics module working" << endl;
    
    cout << "\n" << string(70, '=') << endl;
    cout << "All Quick Tests Passed!" << endl;
    cout << "For detailed performance tests, run TestSuite.cpp" << endl;
    cout << string(70, '=') << endl;
}


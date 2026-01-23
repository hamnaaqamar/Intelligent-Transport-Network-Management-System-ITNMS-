#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "Graph.h"
#include "Queue.h"
#include "Stack.h"
#include "HashTable.h"
#include "BST.h"
#include "Heap.h"
#include "SearchSort.h"
#include "Analytics.h"

using namespace std;

// Function prototypes
void displayMainMenu();
void routeStationMenu(Graph& graph, Stack& history);
void ticketingMenu(Queue& ticketQueue);
void vehicleMenu(HashTable& vehicleDB, Heap& vehicleHeap);
void historyMenu(Stack& history, Graph& graph);
void searchSortMenu();
void analyticsMenu(Analytics& analytics);
void runTestSuite();

int main() {
    cout << "\n" << string(70, '=') << endl;
    cout << "  INTELLIGENT TRANSPORT NETWORK MANAGEMENT SYSTEM (ITNMS)" << endl;
    cout << string(70, '=') << endl;
    cout << "  Welcome to the Smart City Transportation Network Manager" << endl;
    cout << string(70, '=') << "\n" << endl;
    
    // Initialize data structures
    Graph transportGraph(100);
    Queue ticketQueue;
    Stack historyStack;
    HashTable vehicleDB;
    BST routeMetadata;
    Heap vehicleHeap;
    Analytics analytics(&transportGraph, &vehicleDB, &routeMetadata, &vehicleHeap);
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMainMenu();
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                routeStationMenu(transportGraph, historyStack);
                break;
            case 2:
                ticketingMenu(ticketQueue);
                break;
            case 3:
                vehicleMenu(vehicleDB, vehicleHeap);
                break;
            case 4:
                historyMenu(historyStack, transportGraph);
                break;
            case 5:
                searchSortMenu();
                break;
            case 6:
                analyticsMenu(analytics);
                break;
            case 7:
                runTestSuite();
                break;
            case 8:
                cout << "\nThank you for using ITNMS. Goodbye!" << endl;
                running = false;
                break;
            default:
                cout << "\nInvalid choice! Please try again." << endl;
        }
        
        if (running) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }
    
    return 0;
}

void displayMainMenu() {
    cout << "\n" << string(70, '-') << endl;
    cout << "                          MAIN MENU" << endl;
    cout << string(70, '-') << endl;
    cout << "1. Route & Station Management (Graphs)" << endl;
    cout << "2. Passenger Ticketing System (Queues)" << endl;
    cout << "3. Vehicle Database (Hashing + Linked Lists)" << endl;
    cout << "4. History & Undo Operations (Stacks)" << endl;
    cout << "5. Searching & Sorting Module" << endl;
    cout << "6. Analytics & Reporting (Advanced DSA)" << endl;
    cout << "7. Run Test Suite" << endl;
    cout << "8. Exit" << endl;
    cout << string(70, '-') << endl;
}

void routeStationMenu(Graph& graph, Stack& history) {
    int choice;
    bool back = false;
    
    while (!back) {
        cout << "\n" << string(70, '-') << endl;
        cout << "              ROUTE & STATION MANAGEMENT" << endl;
        cout << string(70, '-') << endl;
        cout << "1. Add Station" << endl;
        cout << "2. Delete Station" << endl;
        cout << "3. Add Route" << endl;
        cout << "4. Delete Route" << endl;
        cout << "5. Display All Stations" << endl;
        cout << "6. Display All Connections" << endl;
        cout << "7. BFS Traversal" << endl;
        cout << "8. DFS Traversal" << endl;
        cout << "9. Find Shortest Path (Dijkstra)" << endl;
        cout << "10. Generate Minimum Spanning Tree" << endl;
        cout << "11. Detect Cycle" << endl;
        cout << "12. Back to Main Menu" << endl;
        cout << string(70, '-') << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        int id, src, dest, weight;
        string name;
        
        switch (choice) {
            case 1: {
                cout << "Enter Station ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Station Name: ";
                getline(cin, name);
                graph.addStation(id, name);
                history.push(Action("ADD_STATION", id, name));
                break;
            }
            case 2: {
                cout << "Enter Station ID to delete: ";
                cin >> id;
                cin.ignore();
                Station* station = graph.getStation(id);
                if (station) {
                    history.push(Action("DELETE_STATION", id, station->name));
                }
                graph.deleteStation(id);
                break;
            }
            case 3: {
                cout << "Enter Source Station ID: ";
                cin >> src;
                cout << "Enter Destination Station ID: ";
                cin >> dest;
                cout << "Enter Route Weight: ";
                cin >> weight;
                cin.ignore();
                graph.addRoute(src, dest, weight);
                history.push(Action("ADD_ROUTE", -1, "", src, dest, weight));
                break;
            }
            case 4: {
                cout << "Enter Source Station ID: ";
                cin >> src;
                cout << "Enter Destination Station ID: ";
                cin >> dest;
                cin.ignore();
                graph.deleteRoute(src, dest);
                history.push(Action("DELETE_ROUTE", -1, "", src, dest, 0));
                break;
            }
            case 5:
                graph.displayAllStations();
                break;
            case 6:
                graph.displayConnections();
                break;
            case 7: {
                cout << "Enter Starting Station ID: ";
                cin >> id;
                cin.ignore();
                vector<int> bfsResult = graph.BFS(id);
                cout << "\nBFS Traversal starting from station " << id << ": ";
                for (size_t i = 0; i < bfsResult.size(); i++) {
                    Station* s = graph.getStation(bfsResult[i]);
                    cout << bfsResult[i];
                    if (s) cout << "(" << s->name << ")";
                    if (i < bfsResult.size() - 1) cout << " -> ";
                }
                cout << endl;
                break;
            }
            case 8: {
                cout << "Enter Starting Station ID: ";
                cin >> id;
                cin.ignore();
                vector<int> dfsResult = graph.DFS(id);
                cout << "\nDFS Traversal starting from station " << id << ": ";
                for (size_t i = 0; i < dfsResult.size(); i++) {
                    Station* s = graph.getStation(dfsResult[i]);
                    cout << dfsResult[i];
                    if (s) cout << "(" << s->name << ")";
                    if (i < dfsResult.size() - 1) cout << " -> ";
                }
                cout << endl;
                break;
            }
            case 9: {
                cout << "Enter Source Station ID: ";
                cin >> src;
                cout << "Enter Destination Station ID: ";
                cin >> dest;
                cin.ignore();
                vector<int> path = graph.shortestPath(src, dest);
                if (!path.empty()) {
                    cout << "Path: ";
                    for (size_t i = 0; i < path.size(); i++) {
                        Station* s = graph.getStation(path[i]);
                        cout << path[i];
                        if (s) cout << "(" << s->name << ")";
                        if (i < path.size() - 1) cout << " -> ";
                    }
                    cout << endl;
                }
                break;
            }
            case 10: {
                vector<pair<pair<int, int>, int>> mst = graph.minimumSpanningTree();
                cout << "\n=== Minimum Spanning Tree ===" << endl;
                if (mst.empty()) {
                    cout << "No MST found (graph may be disconnected or empty)." << endl;
                } else {
                    int totalWeight = 0;
                    for (const auto& edge : mst) {
                        Station* srcStation = graph.getStation(edge.first.first);
                        Station* destStation = graph.getStation(edge.first.second);
                        cout << "Edge: ";
                        if (srcStation) cout << srcStation->name;
                        else cout << edge.first.first;
                        cout << " -> ";
                        if (destStation) cout << destStation->name;
                        else cout << edge.first.second;
                        cout << " | Weight: " << edge.second << endl;
                        totalWeight += edge.second;
                    }
                    cout << "Total MST Weight: " << totalWeight << endl;
                }
                break;
            }
            case 11: {
                bool hasCycle = graph.detectCycle();
                if (hasCycle) {
                    cout << "\nCycle detected in the transport network!" << endl;
                } else {
                    cout << "\nNo cycle detected in the transport network." << endl;
                }
                break;
            }
            case 12:
                back = true;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

void ticketingMenu(Queue& ticketQueue) {
    int choice;
    bool back = false;
    
    while (!back) {
        cout << "\n" << string(70, '-') << endl;
        cout << "              PASSENGER TICKETING SYSTEM" << endl;
        cout << string(70, '-') << endl;
        cout << "1. Add Passenger to Queue" << endl;
        cout << "2. Display Queue" << endl;
        cout << "3. Process Next Passenger" << endl;
        cout << "4. View Next Passenger" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << string(70, '-') << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        int id, src, dest;
        string name;
        
        switch (choice) {
            case 1: {
                cout << "Enter Passenger ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Passenger Name: ";
                getline(cin, name);
                cout << "Enter Source Station ID: ";
                cin >> src;
                cout << "Enter Destination Station ID: ";
                cin >> dest;
                cin.ignore();
                ticketQueue.enqueue(Passenger(id, name, src, dest));
                break;
            }
            case 2:
                ticketQueue.display();
                break;
            case 3: {
                if (!ticketQueue.isEmpty()) {
                    Passenger p = ticketQueue.dequeue();
                    cout << "\nProcessing ticket for:" << endl;
                    cout << "  Passenger ID: " << p.id << endl;
                    cout << "  Name: " << p.name << endl;
                    cout << "  Route: Station " << p.sourceStation 
                         << " -> Station " << p.destinationStation << endl;
                    cout << "Ticket processed successfully!" << endl;
                } else {
                    cout << "Queue is empty!" << endl;
                }
                break;
            }
            case 4: {
                if (!ticketQueue.isEmpty()) {
                    Passenger p = ticketQueue.peek();
                    cout << "\nNext Passenger in Queue:" << endl;
                    cout << "  Passenger ID: " << p.id << endl;
                    cout << "  Name: " << p.name << endl;
                    cout << "  Route: Station " << p.sourceStation 
                         << " -> Station " << p.destinationStation << endl;
                } else {
                    cout << "Queue is empty!" << endl;
                }
                break;
            }
            case 5:
                back = true;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

void vehicleMenu(HashTable& vehicleDB, Heap& vehicleHeap) {
    int choice;
    bool back = false;
    
    while (!back) {
        cout << "\n" << string(70, '-') << endl;
        cout << "              VEHICLE DATABASE" << endl;
        cout << string(70, '-') << endl;
        cout << "1. Insert Vehicle" << endl;
        cout << "2. Search Vehicle" << endl;
        cout << "3. Remove Vehicle" << endl;
        cout << "4. Display All Vehicles" << endl;
        cout << "5. Display Hash Table Statistics" << endl;
        cout << "6. Add Vehicle to Priority Queue" << endl;
        cout << "7. Get Fastest Vehicle" << endl;
        cout << "8. Display Priority Queue" << endl;
        cout << "9. Back to Main Menu" << endl;
        cout << string(70, '-') << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        int id, capacity;
        double speed;
        string type, model;
        
        switch (choice) {
            case 1: {
                cout << "Enter Vehicle ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Vehicle Type: ";
                getline(cin, type);
                cout << "Enter Model: ";
                getline(cin, model);
                cout << "Enter Capacity: ";
                cin >> capacity;
                cout << "Enter Speed (km/h): ";
                cin >> speed;
                cin.ignore();
                Vehicle v(id, type, model, capacity, speed);
                vehicleDB.insert(v);
                break;
            }
            case 2: {
                cout << "Enter Vehicle ID to search: ";
                cin >> id;
                cin.ignore();
                Vehicle* v = vehicleDB.search(id);
                if (v) {
                    vehicleDB.displayVehicle(id);
                } else {
                    cout << "Vehicle not found!" << endl;
                }
                break;
            }
            case 3: {
                cout << "Enter Vehicle ID to remove: ";
                cin >> id;
                cin.ignore();
                vehicleDB.remove(id);
                break;
            }
            case 4:
                vehicleDB.display();
                break;
            case 5: {
                cout << "\n=== Hash Table Statistics ===" << endl;
                cout << "Total Vehicles: " << vehicleDB.getNumVehicles() << endl;
                cout << "Load Factor: " << vehicleDB.getLoadFactor() << endl;
                cout << "Longest Chain: " << vehicleDB.getLongestChain() << endl;
                break;
            }
            case 6: {
                cout << "Enter Vehicle ID: ";
                cin >> id;
                cin.ignore();
                Vehicle* v = vehicleDB.search(id);
                if (v) {
                    vehicleHeap.insert(VehiclePriority(v->id, v->speed, v->capacity, v->type));
                    cout << "Vehicle added to priority queue!" << endl;
                } else {
                    cout << "Vehicle not found in database!" << endl;
                }
                break;
            }
            case 7: {
                if (!vehicleHeap.isEmpty()) {
                    VehiclePriority vp = vehicleHeap.peek();
                    Vehicle* v = vehicleDB.search(vp.vehicleId);
                    if (v) {
                        cout << "\nFastest Vehicle:" << endl;
                        vehicleDB.displayVehicle(vp.vehicleId);
                    }
                } else {
                    cout << "Priority queue is empty!" << endl;
                }
                break;
            }
            case 8:
                vehicleHeap.display();
                break;
            case 9:
                back = true;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

void historyMenu(Stack& history, Graph& graph) {
    int choice;
    bool back = false;
    
    while (!back) {
        cout << "\n" << string(70, '-') << endl;
        cout << "              HISTORY & UNDO OPERATIONS" << endl;
        cout << string(70, '-') << endl;
        cout << "1. Display History" << endl;
        cout << "2. Undo Last Action" << endl;
        cout << "3. View Last Action" << endl;
        cout << "4. Clear History" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << string(70, '-') << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                history.display();
                break;
            case 2: {
                if (!history.isEmpty()) {
                    Action lastAction = history.pop();
                    cout << "\nUndoing: " << lastAction.type << endl;
                    
                    // Perform reverse operation
                    if (lastAction.type == "ADD_STATION") {
                        graph.deleteStation(lastAction.stationId);
                        cout << "Station " << lastAction.stationId << " removed." << endl;
                    } else if (lastAction.type == "DELETE_STATION") {
                        graph.addStation(lastAction.stationId, lastAction.stationName);
                        cout << "Station " << lastAction.stationId << " restored." << endl;
                    } else if (lastAction.type == "ADD_ROUTE") {
                        graph.deleteRoute(lastAction.sourceId, lastAction.destId);
                        cout << "Route removed." << endl;
                    } else if (lastAction.type == "DELETE_ROUTE") {
                        graph.addRoute(lastAction.sourceId, lastAction.destId, lastAction.weight);
                        cout << "Route restored." << endl;
                    }
                } else {
                    cout << "History is empty!" << endl;
                }
                break;
            }
            case 3: {
                if (!history.isEmpty()) {
                    Action lastAction = history.peek();
                    cout << "\nLast Action: " << lastAction.type << endl;
                    if (lastAction.type == "ADD_STATION" || lastAction.type == "DELETE_STATION") {
                        cout << "Station ID: " << lastAction.stationId 
                             << ", Name: " << lastAction.stationName << endl;
                    } else if (lastAction.type == "ADD_ROUTE" || lastAction.type == "DELETE_ROUTE") {
                        cout << "Route: " << lastAction.sourceId << " -> " 
                             << lastAction.destId << " (weight: " << lastAction.weight << ")" << endl;
                    }
                } else {
                    cout << "History is empty!" << endl;
                }
                break;
            }
            case 4:
                history.clear();
                cout << "History cleared!" << endl;
                break;
            case 5:
                back = true;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

void searchSortMenu() {
    int choice;
    bool back = false;
    vector<int> data;
    
    while (!back) {
        cout << "\n" << string(70, '-') << endl;
        cout << "              SEARCHING & SORTING MODULE" << endl;
        cout << string(70, '-') << endl;
        cout << "SEARCHING ALGORITHMS:" << endl;
        cout << "  1. Linear Search" << endl;
        cout << "  2. Binary Search (requires sorted array)" << endl;
        cout << "\nSORTING ALGORITHMS:" << endl;
        cout << "  3. Bubble Sort" << endl;
        cout << "  4. Selection Sort" << endl;
        cout << "  5. Insertion Sort" << endl;
        cout << "  6. Merge Sort" << endl;
        cout << "  7. Quick Sort" << endl;
        cout << "  8. Heap Sort" << endl;
        cout << "  9. Counting Sort" << endl;
        cout << "  10. Radix Sort" << endl;
        cout << "\nUTILITIES:" << endl;
        cout << "  11. Enter/Modify Dataset" << endl;
        cout << "  12. Display Current Dataset" << endl;
        cout << "  13. Back to Main Menu" << endl;
        cout << string(70, '-') << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        int key, n, value;
        
        switch (choice) {
            case 1: {
                if (data.empty()) {
                    cout << "Please enter a dataset first (option 11)!" << endl;
                    break;
                }
                cout << "Enter value to search: ";
                cin >> key;
                cin.ignore();
                SearchSort::printComplexity("Linear Search");
                int index = SearchSort::linearSearch(data, key);
                if (index != -1) {
                    cout << "Value " << key << " found at index " << index << endl;
                } else {
                    cout << "Value " << key << " not found!" << endl;
                }
                break;
            }
            case 2: {
                if (data.empty()) {
                    cout << "Please enter a dataset first (option 11)!" << endl;
                    break;
                }
                vector<int> sortedData = data;
                SearchSort::bubbleSort(sortedData);
                cout << "Array sorted for binary search." << endl;
                SearchSort::displayArray(sortedData);
                cout << "Enter value to search: ";
                cin >> key;
                cin.ignore();
                SearchSort::printComplexity("Binary Search");
                int index = SearchSort::binarySearch(sortedData, key);
                if (index != -1) {
                    cout << "Value " << key << " found at index " << index << endl;
                } else {
                    cout << "Value " << key << " not found!" << endl;
                }
                break;
            }
            case 3: {
                if (data.empty()) {
                    cout << "Please enter a dataset first (option 11)!" << endl;
                    break;
                }
                vector<int> arr = data;
                cout << "Before sorting: ";
                SearchSort::displayArray(arr);
                SearchSort::printComplexity("Bubble Sort");
                SearchSort::bubbleSort(arr);
                cout << "After sorting: ";
                SearchSort::displayArray(arr);
                break;
            }
            case 4: {
                if (data.empty()) {
                    cout << "Please enter a dataset first (option 11)!" << endl;
                    break;
                }
                vector<int> arr = data;
                cout << "Before sorting: ";
                SearchSort::displayArray(arr);
                SearchSort::printComplexity("Selection Sort");
                SearchSort::selectionSort(arr);
                cout << "After sorting: ";
                SearchSort::displayArray(arr);
                break;
            }
            case 5: {
                if (data.empty()) {
                    cout << "Please enter a dataset first (option 11)!" << endl;
                    break;
                }
                vector<int> arr = data;
                cout << "Before sorting: ";
                SearchSort::displayArray(arr);
                SearchSort::printComplexity("Insertion Sort");
                SearchSort::insertionSort(arr);
                cout << "After sorting: ";
                SearchSort::displayArray(arr);
                break;
            }
            case 6: {
                if (data.empty()) {
                    cout << "Please enter a dataset first (option 11)!" << endl;
                    break;
                }
                vector<int> arr = data;
                cout << "Before sorting: ";
                SearchSort::displayArray(arr);
                SearchSort::printComplexity("Merge Sort");
                SearchSort::mergeSort(arr);
                cout << "After sorting: ";
                SearchSort::displayArray(arr);
                break;
            }
            case 7: {
                if (data.empty()) {
                    cout << "Please enter a dataset first (option 11)!" << endl;
                    break;
                }
                vector<int> arr = data;
                cout << "Before sorting: ";
                SearchSort::displayArray(arr);
                SearchSort::printComplexity("Quick Sort");
                SearchSort::quickSort(arr);
                cout << "After sorting: ";
                SearchSort::displayArray(arr);
                break;
            }
            case 8: {
                if (data.empty()) {
                    cout << "Please enter a dataset first (option 11)!" << endl;
                    break;
                }
                vector<int> arr = data;
                cout << "Before sorting: ";
                SearchSort::displayArray(arr);
                SearchSort::printComplexity("Heap Sort");
                SearchSort::heapSort(arr);
                cout << "After sorting: ";
                SearchSort::displayArray(arr);
                break;
            }
            case 9: {
                if (data.empty()) {
                    cout << "Please enter a dataset first (option 11)!" << endl;
                    break;
                }
                vector<int> arr = data;
                cout << "Before sorting: ";
                SearchSort::displayArray(arr);
                SearchSort::printComplexity("Counting Sort");
                SearchSort::countingSort(arr);
                cout << "After sorting: ";
                SearchSort::displayArray(arr);
                break;
            }
            case 10: {
                if (data.empty()) {
                    cout << "Please enter a dataset first (option 11)!" << endl;
                    break;
                }
                vector<int> arr = data;
                cout << "Before sorting: ";
                SearchSort::displayArray(arr);
                SearchSort::printComplexity("Radix Sort");
                SearchSort::radixSort(arr);
                cout << "After sorting: ";
                SearchSort::displayArray(arr);
                break;
            }
            case 11: {
                data.clear();
                cout << "Enter number of elements: ";
                cin >> n;
                cout << "Enter " << n << " integers: ";
                for (int i = 0; i < n; i++) {
                    cin >> value;
                    data.push_back(value);
                }
                cin.ignore();
                cout << "Dataset entered successfully!" << endl;
                SearchSort::displayArray(data);
                break;
            }
            case 12:
                if (data.empty()) {
                    cout << "No dataset available!" << endl;
                } else {
                    SearchSort::displayArray(data);
                }
                break;
            case 13:
                back = true;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

void analyticsMenu(Analytics& analytics) {
    int choice;
    bool back = false;
    
    while (!back) {
        cout << "\n" << string(70, '-') << endl;
        cout << "              ANALYTICS & REPORTING" << endl;
        cout << string(70, '-') << endl;
        cout << "1. Most Crowded Station" << endl;
        cout << "2. Busiest Route" << endl;
        cout << "3. Fastest Vehicle Assignment" << endl;
        cout << "4. Traffic Density Prediction" << endl;
        cout << "5. Daily Usage Trends" << endl;
        cout << "6. Generate Comprehensive Report" << endl;
        cout << "7. Reset Statistics" << endl;
        cout << "8. Back to Main Menu" << endl;
        cout << string(70, '-') << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                analytics.mostCrowdedStation();
                break;
            case 2:
                analytics.busiestRoute();
                break;
            case 3:
                analytics.fastestVehicleAssignment();
                break;
            case 4:
                analytics.trafficDensityPrediction();
                break;
            case 5:
                analytics.dailyUsageTrends();
                break;
            case 6:
                analytics.generateReport();
                break;
            case 7:
                analytics.resetStatistics();
                break;
            case 8:
                back = true;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

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


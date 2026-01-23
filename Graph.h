#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <climits>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int destination;
    int weight;
    Edge* next;  // For manual linked list
    Edge(int dest, int w) : destination(dest), weight(w), next(nullptr) {}
};

// Manual linked list for edges (adjacency list)
class EdgeList {
private:
    Edge* head;
    
public:
    EdgeList() : head(nullptr) {}
    
    ~EdgeList() {
        clear();
    }
    
    void push_back(int dest, int weight) {
        Edge* newNode = new Edge(dest, weight);
        if (head == nullptr) {
            head = newNode;
        } else {
            Edge* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    
    void clear() {
        while (head != nullptr) {
            Edge* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    bool empty() const {
        return head == nullptr;
    }
    
    // Iterator-like functionality
    Edge* begin() const { return head; }
    Edge* end() const { return nullptr; }
    
    // Remove edge with specific destination
    void remove(int dest) {
        if (head == nullptr) return;
        
        // If head needs to be removed
        if (head->destination == dest) {
            Edge* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        
        // Find and remove
        Edge* current = head;
        while (current->next != nullptr) {
            if (current->next->destination == dest) {
                Edge* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }
    }
    
    // Get size
    int size() const {
        int count = 0;
        Edge* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
};

// Structure to represent a station
struct Station {
    int id;
    string name;
    Station(int i, string n) : id(i), name(n) {}
};

// Graph class using adjacency list representation
class Graph {
private:
    int numVertices;
    vector<EdgeList> adjList;  // Manual linked list instead of std::list
    vector<Station> stations;
    vector<vector<int>> adjMatrix; // For MST and some algorithms
    
    // Helper function for DFS
    void DFSUtil(int v, vector<bool>& visited, vector<int>& result);
    
    // Helper function for cycle detection
    bool hasCycleUtil(int v, vector<bool>& visited, vector<bool>& recStack);
    
    // Helper function for MST (Kruskal's algorithm)
    int findParent(vector<int>& parent, int i);
    void unionSets(vector<int>& parent, vector<int>& rank, int x, int y);
    
    // Manual queue implementation for BFS (no external libraries)
    struct QueueNode {
        int data;
        QueueNode* next;
        QueueNode(int d) : data(d), next(nullptr) {}
    };
    
    class ManualQueue {
    private:
        QueueNode* front;
        QueueNode* rear;
    public:
        ManualQueue() : front(nullptr), rear(nullptr) {}
        ~ManualQueue() {
            while (!isEmpty()) {
                dequeue();
            }
        }
        void enqueue(int data) {
            QueueNode* newNode = new QueueNode(data);
            if (rear == nullptr) {
                front = rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
        }
        int dequeue() {
            if (front == nullptr) return -1;
            QueueNode* temp = front;
            int data = front->data;
            front = front->next;
            if (front == nullptr) rear = nullptr;
            delete temp;
            return data;
        }
        bool isEmpty() const { return front == nullptr; }
    };
    
    // Manual sorting for MST (bubble sort - simple and manual)
    void sortEdges(vector<pair<int, pair<int, int>>>& edges);

public:
    Graph(int V = 0);
    
    // Station management
    void addStation(int id, const string& name);
    void deleteStation(int id);
    Station* getStation(int id);
    vector<Station> getAllStations() const;
    
    // Route management
    void addRoute(int src, int dest, int weight);
    void deleteRoute(int src, int dest);
    
    // Graph operations
    void displayAllStations();
    void displayConnections();
    
    // Graph algorithms
    vector<int> BFS(int startVertex);
    vector<int> DFS(int startVertex);
    vector<int> shortestPath(int src, int dest); // Dijkstra's algorithm
    vector<pair<pair<int, int>, int>> minimumSpanningTree(); // Kruskal's algorithm
    bool detectCycle();
    
    // Utility
    int getNumVertices() const { return numVertices; }
    bool stationExists(int id) const;
};

#endif


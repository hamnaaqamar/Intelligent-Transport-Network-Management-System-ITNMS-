#include "Graph.h"
#include <iostream>

Graph::Graph(int V) : numVertices(V) {
    adjList.resize(V);
    adjMatrix.resize(V, vector<int>(V, 0));
    // EdgeList objects are default constructed (head = nullptr)
}

void Graph::addStation(int id, const string& name) {
    // Check if station already exists
    for (const auto& station : stations) {
        if (station.id == id) {
            cout << "Station with ID " << id << " already exists!" << endl;
            return;
        }
    }
    
    stations.push_back(Station(id, name));
    
    // Expand graph if needed
    if (id >= numVertices) {
        numVertices = id + 1;
        adjList.resize(numVertices);
        adjMatrix.resize(numVertices);
        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i].resize(numVertices, 0);
        }
    }
    
    cout << "Station '" << name << "' (ID: " << id << ") added successfully!" << endl;
}

void Graph::deleteStation(int id) {
    // Remove station from list manually (no std::remove_if)
    for (auto it = stations.begin(); it != stations.end(); ) {
        if (it->id == id) {
            it = stations.erase(it);
        } else {
            ++it;
        }
    }
    
    if (id < numVertices) {
        // Remove all edges connected to this station manually
        adjList[id].clear();
        for (int i = 0; i < numVertices; i++) {
        // Manual removal from list
        adjList[i].remove(id);
            adjMatrix[i][id] = 0;
            adjMatrix[id][i] = 0;
        }
    }
    
    cout << "Station with ID " << id << " deleted successfully!" << endl;
}

Station* Graph::getStation(int id) {
    for (auto& station : stations) {
        if (station.id == id) {
            return &station;
        }
    }
    return nullptr;
}

vector<Station> Graph::getAllStations() const {
    return stations;
}

void Graph::addRoute(int src, int dest, int weight) {
    if (src >= numVertices || dest >= numVertices) {
        cout << "Invalid station IDs!" << endl;
        return;
    }
    
    // Check if route already exists
    Edge* current = adjList[src].begin();
    while (current != nullptr) {
        if (current->destination == dest) {
            cout << "Route already exists! Updating weight..." << endl;
            current->weight = weight;
            adjMatrix[src][dest] = weight;
            return;
        }
        current = current->next;
    }
    
    adjList[src].push_back(dest, weight);
    adjMatrix[src][dest] = weight;
    cout << "Route added from station " << src << " to " << dest << " with weight " << weight << endl;
}

void Graph::deleteRoute(int src, int dest) {
    if (src >= numVertices || dest >= numVertices) {
        cout << "Invalid station IDs!" << endl;
        return;
    }
    
    // Manual removal from list
    adjList[src].remove(dest);
    adjMatrix[src][dest] = 0;
    cout << "Route from station " << src << " to " << dest << " deleted!" << endl;
}

void Graph::displayAllStations() {
    cout << "\n=== All Stations ===" << endl;
    if (stations.empty()) {
        cout << "No stations available." << endl;
        return;
    }
    
    for (const auto& station : stations) {
        cout << "ID: " << station.id << " | Name: " << station.name << endl;
    }
}

void Graph::displayConnections() {
    cout << "\n=== Station Connections ===" << endl;
    for (int i = 0; i < numVertices; i++) {
        if (!adjList[i].empty()) {
            Station* station = getStation(i);
            if (station) {
                cout << "Station " << i << " (" << station->name << ") -> ";
                Edge* current = adjList[i].begin();
                while (current != nullptr) {
                    Station* destStation = getStation(current->destination);
                    cout << current->destination << " (" << (destStation ? destStation->name : "Unknown") 
                         << ", weight: " << current->weight << ") ";
                    current = current->next;
                }
                cout << endl;
            }
        }
    }
}

// Manual sorting for MST edges - Bubble Sort implementation
// Time: O(E²), Space: O(1)
void Graph::sortEdges(vector<pair<int, pair<int, int>>>& edges) {
    int n = edges.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (edges[j].first > edges[j + 1].first) {
                // Swap edges
                pair<int, pair<int, int>> temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

// BFS Implementation - Time: O(V+E), Space: O(V)
// Uses manual queue implementation (no external libraries)
vector<int> Graph::BFS(int startVertex) {
    vector<int> result;
    if (startVertex >= numVertices) return result;
    
    vector<bool> visited(numVertices, false);
    ManualQueue q; // Manual queue implementation
    
    visited[startVertex] = true;
    q.enqueue(startVertex);
    
    while (!q.isEmpty()) {
        int v = q.dequeue();
        result.push_back(v);
        
        Edge* current = adjList[v].begin();
        while (current != nullptr) {
            if (!visited[current->destination]) {
                visited[current->destination] = true;
                q.enqueue(current->destination);
            }
            current = current->next;
        }
    }
    
    return result;
}

// DFS Implementation - Time: O(V+E), Space: O(V)
void Graph::DFSUtil(int v, vector<bool>& visited, vector<int>& result) {
    visited[v] = true;
    result.push_back(v);
    
    Edge* current = adjList[v].begin();
    while (current != nullptr) {
        if (!visited[current->destination]) {
            DFSUtil(current->destination, visited, result);
        }
        current = current->next;
    }
}

vector<int> Graph::DFS(int startVertex) {
    vector<int> result;
    if (startVertex >= numVertices) return result;
    
    vector<bool> visited(numVertices, false);
    DFSUtil(startVertex, visited, result);
    
    return result;
}

// Dijkstra's Algorithm - Time: O(V^2) with adjacency matrix, Space: O(V)
vector<int> Graph::shortestPath(int src, int dest) {
    vector<int> path;
    if (src >= numVertices || dest >= numVertices) return path;
    
    vector<int> dist(numVertices, INT_MAX);
    vector<int> parent(numVertices, -1);
    vector<bool> visited(numVertices, false);
    
    dist[src] = 0;
    
    for (int count = 0; count < numVertices - 1; count++) {
        int u = -1;
        int minDist = INT_MAX;
        
        // Find unvisited vertex with minimum distance
        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }
        
        if (u == -1) break;
        visited[u] = true;
        
        // Update distances
        Edge* current = adjList[u].begin();
        while (current != nullptr) {
            int v = current->destination;
            int weight = current->weight;
            
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
            current = current->next;
        }
    }
    
    // Reconstruct path
    if (dist[dest] == INT_MAX) {
        cout << "No path exists from station " << src << " to " << dest << endl;
        return path;
    }
    
    // Reconstruct path manually (no std::reverse)
    int current = dest;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    // Manual reverse
    int n = path.size();
    for (int i = 0; i < n / 2; i++) {
        int temp = path[i];
        path[i] = path[n - 1 - i];
        path[n - 1 - i] = temp;
    }
    
    cout << "Shortest distance from station " << src << " to " << dest << ": " << dist[dest] << endl;
    return path;
}

// Union-Find helper functions for Kruskal's algorithm
int Graph::findParent(vector<int>& parent, int i) {
    if (parent[i] == i) return i;
    return parent[i] = findParent(parent, parent[i]);
}

void Graph::unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
    int xRoot = findParent(parent, x);
    int yRoot = findParent(parent, y);
    
    if (rank[xRoot] < rank[yRoot]) {
        parent[xRoot] = yRoot;
    } else if (rank[xRoot] > rank[yRoot]) {
        parent[yRoot] = xRoot;
    } else {
        parent[yRoot] = xRoot;
        rank[xRoot]++;
    }
}

// Kruskal's Algorithm for MST - Time: O(E log E), Space: O(V)
vector<pair<pair<int, int>, int>> Graph::minimumSpanningTree() {
    vector<pair<pair<int, int>, int>> mst;
    
    // Collect all edges
    vector<pair<int, pair<int, int>>> edges;
    for (int u = 0; u < numVertices; u++) {
        Edge* current = adjList[u].begin();
        while (current != nullptr) {
            if (u < current->destination) { // Avoid duplicates
                edges.push_back({current->weight, {u, current->destination}});
            }
            current = current->next;
        }
    }
    
    // Sort edges by weight using manual sorting (no external libraries)
    sortEdges(edges);
    
    // Union-Find data structure
    vector<int> parent(numVertices);
    vector<int> rank(numVertices, 0);
    for (int i = 0; i < numVertices; i++) {
        parent[i] = i;
    }
    
    // Kruskal's algorithm
    for (const auto& edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        
        int uRoot = findParent(parent, u);
        int vRoot = findParent(parent, v);
        
        if (uRoot != vRoot) {
            mst.push_back({{u, v}, edge.first});
            unionSets(parent, rank, uRoot, vRoot);
        }
    }
    
    return mst;
}

// Cycle Detection using DFS - Time: O(V+E), Space: O(V)
bool Graph::hasCycleUtil(int v, vector<bool>& visited, vector<bool>& recStack) {
    visited[v] = true;
    recStack[v] = true;
    
    Edge* current = adjList[v].begin();
    while (current != nullptr) {
        if (!visited[current->destination]) {
            if (hasCycleUtil(current->destination, visited, recStack)) {
                return true;
            }
        } else if (recStack[current->destination]) {
            return true;
        }
        current = current->next;
    }
    
    recStack[v] = false;
    return false;
}

bool Graph::detectCycle() {
    vector<bool> visited(numVertices, false);
    vector<bool> recStack(numVertices, false);
    
    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            if (hasCycleUtil(i, visited, recStack)) {
                return true;
            }
        }
    }
    
    return false;
}

bool Graph::stationExists(int id) const {
    for (const auto& station : stations) {
        if (station.id == id) return true;
    }
    return false;
}


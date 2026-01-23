#include "Analytics.h"
#include <iostream>
#include <iomanip>

Analytics::Analytics(Graph* g, HashTable* h, BST* b, Heap* hp)
    : transportGraph(g), vehicleDB(h), routeMetadata(b), vehiclePriority(hp) {
    stationFrequency.clear();
}

void Analytics::updateStationFrequency(int stationId) {
    stationFrequency.increment(stationId);
}

// Manual sorting - Selection Sort (descending order)
void Analytics::sortPairsDescending(vector<pair<int, int>>& pairs) {
    int n = pairs.size();
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (pairs[j].first > pairs[maxIdx].first) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            pair<int, int> temp = pairs[i];
            pairs[i] = pairs[maxIdx];
            pairs[maxIdx] = temp;
        }
    }
}

// Manual sorting - Selection Sort for routes by passenger count
void Analytics::sortRoutesByPassengers(vector<RouteMetadata>& routes) {
    int n = routes.size();
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (routes[j].passengerCount > routes[maxIdx].passengerCount) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            RouteMetadata temp = routes[i];
            routes[i] = routes[maxIdx];
            routes[maxIdx] = temp;
        }
    }
}

// Manual sorting - Selection Sort for density data
void Analytics::sortDensityData(vector<pair<int, int>>& data) {
    int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (data[j].first > data[maxIdx].first) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            pair<int, int> temp = data[i];
            data[i] = data[maxIdx];
            data[maxIdx] = temp;
        }
    }
}

void Analytics::resetStatistics() {
    stationFrequency.clear();
    cout << "Statistics reset successfully!" << endl;
}

// Most Crowded Station - Uses hash frequency count
// Time: O(n), Space: O(n)
void Analytics::mostCrowdedStation() {
    cout << "\n=== Most Crowded Station Analysis ===" << endl;
    
    if (stationFrequency.empty()) {
        cout << "No station usage data available." << endl;
        return;
    }
    
    int maxCount = 0;
    int crowdedStationId = -1;
    
    vector<pair<int, int>> allPairs = stationFrequency.getAllPairs();
    for (size_t i = 0; i < allPairs.size(); i++) {
        if (allPairs[i].second > maxCount) {
            maxCount = allPairs[i].second;
            crowdedStationId = allPairs[i].first;
        }
    }
    
    if (crowdedStationId != -1) {
        Station* station = transportGraph->getStation(crowdedStationId);
        cout << "Most Crowded Station:" << endl;
        cout << "  ID: " << crowdedStationId << endl;
        if (station) {
            cout << "  Name: " << station->name << endl;
        }
        cout << "  Passenger Count: " << maxCount << endl;
    }
    
    // Display top 5 stations - Manual sorting
    vector<pair<int, int>> sortedStations;
    // Reuse allPairs from above
    for (size_t i = 0; i < allPairs.size(); i++) {
        sortedStations.push_back(pair<int, int>(allPairs[i].second, allPairs[i].first)); // {count, stationId}
    }
    sortPairsDescending(sortedStations);
    
    cout << "\nTop 5 Busiest Stations:" << endl;
    int count = 0;
    for (size_t i = 0; i < sortedStations.size() && count < 5; i++) {
        Station* station = transportGraph->getStation(sortedStations[i].second);
        cout << (count + 1) << ". Station " << sortedStations[i].second;
        if (station) {
            cout << " (" << station->name << ")";
        }
        cout << " - " << sortedStations[i].first << " passengers" << endl;
        count++;
    }
}

// Busiest Route - Graph edge weight statistics
// Time: O(V+E), Space: O(E)
void Analytics::busiestRoute() {
    cout << "\n=== Busiest Route Analysis ===" << endl;
    
    vector<pair<pair<int, int>, int>> routes;
    
    // Collect all routes with their weights
    for (int i = 0; i < transportGraph->getNumVertices(); i++) {
        vector<Station> stations = transportGraph->getAllStations();
        for (const auto& station : stations) {
            if (station.id == i) {
                // Get connections for this station
                // Note: This requires access to adjacency list, simplified here
                break;
            }
        }
    }
    
    // Get routes from MST (represents all active routes)
    vector<pair<pair<int, int>, int>> mst = transportGraph->minimumSpanningTree();
    
    if (mst.empty()) {
        cout << "No routes available for analysis." << endl;
        return;
    }
    
    // Sort by weight (higher weight = busier route) - Manual sorting
    int n = mst.size();
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (mst[j].second > mst[maxIdx].second) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            pair<pair<int, int>, int> temp = mst[i];
            mst[i] = mst[maxIdx];
            mst[maxIdx] = temp;
        }
    }
    
    cout << "Top 5 Busiest Routes:" << endl;
    int count = 0;
    for (const auto& route : mst) {
        if (count >= 5) break;
        Station* srcStation = transportGraph->getStation(route.first.first);
        Station* destStation = transportGraph->getStation(route.first.second);
        
        cout << (count + 1) << ". Route: ";
        if (srcStation) {
            cout << srcStation->name;
        } else {
            cout << "Station " << route.first.first;
        }
        cout << " -> ";
        if (destStation) {
            cout << destStation->name;
        } else {
            cout << "Station " << route.first.second;
        }
        cout << " | Weight/Traffic: " << route.second << endl;
        count++;
    }
}

// Fastest Vehicle Assignment - Min-heap
// Time: O(log n), Space: O(1)
void Analytics::fastestVehicleAssignment() {
    cout << "\n=== Fastest Vehicle Assignment ===" << endl;
    
    if (vehiclePriority->isEmpty()) {
        cout << "No vehicles available in priority queue." << endl;
        return;
    }
    
    VehiclePriority fastest = vehiclePriority->peek();
    Vehicle* vehicle = vehicleDB->search(fastest.vehicleId);
    
    if (vehicle) {
        cout << "Fastest Available Vehicle:" << endl;
        cout << "  ID: " << vehicle->id << endl;
        cout << "  Type: " << vehicle->type << endl;
        cout << "  Model: " << vehicle->model << endl;
        cout << "  Speed: " << vehicle->speed << " km/h" << endl;
        cout << "  Capacity: " << vehicle->capacity << " passengers" << endl;
    }
    
    cout << "\nNote: Use 'Display Priority Queue' in Vehicle Menu to see all vehicles." << endl;
}

// Traffic Density Prediction - Heap sorting
// Time: O(n log n), Space: O(n)
void Analytics::trafficDensityPrediction() {
    cout << "\n=== Traffic Density Prediction ===" << endl;
    
    // Simulate traffic density based on station frequency
    vector<pair<int, int>> densityData;
    
    vector<pair<int, int>> allPairs = stationFrequency.getAllPairs();
    for (size_t i = 0; i < allPairs.size(); i++) {
        densityData.push_back(pair<int, int>(allPairs[i].second, allPairs[i].first));
    }
    
    if (densityData.empty()) {
        cout << "Insufficient data for traffic density prediction." << endl;
        return;
    }
    
    // Sort by density (using manual sorting)
    sortDensityData(densityData);
    
    cout << "Traffic Density Prediction (High to Low):" << endl;
    int count = 0;
    for (const auto& data : densityData) {
        if (count >= 10) break;
        Station* station = transportGraph->getStation(data.second);
        string densityLevel;
        if (data.first > 50) densityLevel = "Very High";
        else if (data.first > 30) densityLevel = "High";
        else if (data.first > 15) densityLevel = "Medium";
        else densityLevel = "Low";
        
        cout << (count + 1) << ". Station " << data.second;
        if (station) {
            cout << " (" << station->name << ")";
        }
        cout << " - Density: " << densityLevel 
             << " (" << data.first << " passengers)" << endl;
        count++;
    }
}

// Daily Usage Trends - BST traversal
// Time: O(n), Space: O(n)
void Analytics::dailyUsageTrends() {
    cout << "\n=== Daily Usage Trends ===" << endl;
    
    if (routeMetadata->isEmpty()) {
        cout << "No route metadata available." << endl;
        return;
    }
    
    vector<RouteMetadata> routes = routeMetadata->getAllRoutes();
    
    if (routes.empty()) {
        cout << "No routes available." << endl;
        return;
    }
    
    // Sort by passenger count - Manual sorting
    sortRoutesByPassengers(routes);
    
    cout << "Daily Usage Trends (by Passenger Count):" << endl;
    int totalPassengers = 0;
    for (const auto& route : routes) {
        totalPassengers += route.passengerCount;
    }
    
    for (size_t i = 0; i < routes.size() && i < 10; i++) {
        double percentage = totalPassengers > 0 ? 
            (routes[i].passengerCount * 100.0 / totalPassengers) : 0;
        
        cout << (i + 1) << ". Route " << routes[i].routeId 
             << " (" << routes[i].routeName << ")" << endl;
        cout << "   Passengers: " << routes[i].passengerCount 
             << " (" << fixed << setprecision(2) << percentage << "%)" << endl;
        cout << "   Average Time: " << routes[i].averageTime << " minutes" << endl;
    }
    
    cout << "\nTotal Passengers Across All Routes: " << totalPassengers << endl;
}

// Generate Comprehensive Report
void Analytics::generateReport() {
    cout << "\n" << string(60, '=') << endl;
    cout << "     INTELLIGENT TRANSPORT NETWORK MANAGEMENT SYSTEM" << endl;
    cout << "                    ANALYTICS REPORT" << endl;
    cout << string(60, '=') << endl;
    
    mostCrowdedStation();
    cout << endl;
    
    busiestRoute();
    cout << endl;
    
    fastestVehicleAssignment();
    cout << endl;
    
    trafficDensityPrediction();
    cout << endl;
    
    dailyUsageTrends();
    cout << endl;
    
    cout << string(60, '=') << endl;
    cout << "                    END OF REPORT" << endl;
    cout << string(60, '=') << endl;
}


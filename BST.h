#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Structure to store route metadata
struct RouteMetadata {
    int routeId;
    string routeName;
    int passengerCount;
    double averageTime;
    
    RouteMetadata(int id, string name, int count = 0, double time = 0.0)
        : routeId(id), routeName(name), passengerCount(count), averageTime(time) {}
    
    bool operator<(const RouteMetadata& other) const {
        return routeId < other.routeId;
    }
    
    bool operator>(const RouteMetadata& other) const {
        return routeId > other.routeId;
    }
    
    bool operator==(const RouteMetadata& other) const {
        return routeId == other.routeId;
    }
};

// BST Node
struct BSTNode {
    RouteMetadata data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(RouteMetadata d) : data(d), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class BST {
private:
    BSTNode* root;
    int size;
    
    // Helper functions
    BSTNode* insertHelper(BSTNode* node, RouteMetadata data);
    BSTNode* searchHelper(BSTNode* node, int routeId);
    BSTNode* deleteHelper(BSTNode* node, int routeId);
    BSTNode* findMin(BSTNode* node);
    void inorderHelper(BSTNode* node, vector<RouteMetadata>& result);
    void preorderHelper(BSTNode* node, vector<RouteMetadata>& result);
    void postorderHelper(BSTNode* node, vector<RouteMetadata>& result);
    void clearHelper(BSTNode* node);
    
public:
    BST();
    ~BST();
    
    // BST operations
    void insert(RouteMetadata data);
    RouteMetadata* search(int routeId);
    bool remove(int routeId);
    void displayInorder();
    void displayPreorder();
    void displayPostorder();
    vector<RouteMetadata> getAllRoutes();
    int getSize() const { return size; }
    bool isEmpty() const { return root == nullptr; }
    void clear();
};

#endif


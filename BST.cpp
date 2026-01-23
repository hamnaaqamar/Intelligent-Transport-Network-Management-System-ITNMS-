#include "BST.h"
#include <iostream>

BST::BST() : root(nullptr), size(0) {}

BST::~BST() {
    clear();
}

// Insert - Average Time: O(log n), Worst: O(n), Space: O(log n)
BSTNode* BST::insertHelper(BSTNode* node, RouteMetadata data) {
    if (node == nullptr) {
        size++;
        return new BSTNode(data);
    }
    
    if (data < node->data) {
        node->left = insertHelper(node->left, data);
    } else if (data > node->data) {
        node->right = insertHelper(node->right, data);
    } else {
        // Update existing route
        node->data = data;
    }
    
    return node;
}

void BST::insert(RouteMetadata data) {
    root = insertHelper(root, data);
    cout << "Route metadata inserted: " << data.routeName << " (ID: " << data.routeId << ")" << endl;
}

// Search - Average Time: O(log n), Worst: O(n), Space: O(log n)
BSTNode* BST::searchHelper(BSTNode* node, int routeId) {
    if (node == nullptr || node->data.routeId == routeId) {
        return node;
    }
    
    if (routeId < node->data.routeId) {
        return searchHelper(node->left, routeId);
    } else {
        return searchHelper(node->right, routeId);
    }
}

RouteMetadata* BST::search(int routeId) {
    BSTNode* node = searchHelper(root, routeId);
    if (node) {
        return &(node->data);
    }
    return nullptr;
}

// Find minimum node
BSTNode* BST::findMin(BSTNode* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Delete - Average Time: O(log n), Worst: O(n), Space: O(log n)
BSTNode* BST::deleteHelper(BSTNode* node, int routeId) {
    if (node == nullptr) return node;
    
    if (routeId < node->data.routeId) {
        node->left = deleteHelper(node->left, routeId);
    } else if (routeId > node->data.routeId) {
        node->right = deleteHelper(node->right, routeId);
    } else {
        // Node to be deleted found
        if (node->left == nullptr) {
            BSTNode* temp = node->right;
            delete node;
            size--;
            return temp;
        } else if (node->right == nullptr) {
            BSTNode* temp = node->left;
            delete node;
            size--;
            return temp;
        }
        
        // Node with two children
        BSTNode* temp = findMin(node->right);
        node->data = temp->data;
        node->right = deleteHelper(node->right, temp->data.routeId);
    }
    
    return node;
}

bool BST::remove(int routeId) {
    int oldSize = size;
    root = deleteHelper(root, routeId);
    if (size < oldSize) {
        cout << "Route " << routeId << " deleted successfully!" << endl;
        return true;
    }
    cout << "Route " << routeId << " not found!" << endl;
    return false;
}

// Inorder traversal - Time: O(n), Space: O(n)
void BST::inorderHelper(BSTNode* node, vector<RouteMetadata>& result) {
    if (node == nullptr) return;
    inorderHelper(node->left, result);
    result.push_back(node->data);
    inorderHelper(node->right, result);
}

void BST::displayInorder() {
    vector<RouteMetadata> result;
    inorderHelper(root, result);
    
    cout << "\n=== Routes (Inorder Traversal) ===" << endl;
    if (result.empty()) {
        cout << "No routes available." << endl;
        return;
    }
    
    for (const auto& route : result) {
        cout << "Route ID: " << route.routeId 
             << " | Name: " << route.routeName
             << " | Passengers: " << route.passengerCount
             << " | Avg Time: " << route.averageTime << " min" << endl;
    }
}

// Preorder traversal - Time: O(n), Space: O(n)
void BST::preorderHelper(BSTNode* node, vector<RouteMetadata>& result) {
    if (node == nullptr) return;
    result.push_back(node->data);
    preorderHelper(node->left, result);
    preorderHelper(node->right, result);
}

void BST::displayPreorder() {
    vector<RouteMetadata> result;
    preorderHelper(root, result);
    
    cout << "\n=== Routes (Preorder Traversal) ===" << endl;
    if (result.empty()) {
        cout << "No routes available." << endl;
        return;
    }
    
    for (const auto& route : result) {
        cout << "Route ID: " << route.routeId 
             << " | Name: " << route.routeName << endl;
    }
}

// Postorder traversal - Time: O(n), Space: O(n)
void BST::postorderHelper(BSTNode* node, vector<RouteMetadata>& result) {
    if (node == nullptr) return;
    postorderHelper(node->left, result);
    postorderHelper(node->right, result);
    result.push_back(node->data);
}

void BST::displayPostorder() {
    vector<RouteMetadata> result;
    postorderHelper(root, result);
    
    cout << "\n=== Routes (Postorder Traversal) ===" << endl;
    if (result.empty()) {
        cout << "No routes available." << endl;
        return;
    }
    
    for (const auto& route : result) {
        cout << "Route ID: " << route.routeId 
             << " | Name: " << route.routeName << endl;
    }
}

vector<RouteMetadata> BST::getAllRoutes() {
    vector<RouteMetadata> result;
    inorderHelper(root, result);
    return result;
}

void BST::clearHelper(BSTNode* node) {
    if (node == nullptr) return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}

void BST::clear() {
    clearHelper(root);
    root = nullptr;
    size = 0;
}


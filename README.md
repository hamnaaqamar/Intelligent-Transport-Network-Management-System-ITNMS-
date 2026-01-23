# Intelligent Transport Network Management System (ITNMS)

## Project Overview

The Intelligent Transport Network Management System (ITNMS) is a comprehensive C++ application that simulates a smart city transportation network. This project demonstrates the practical application of core Data Structures and Algorithms (DSA) concepts including arrays, linked lists, queues, stacks, trees, graphs, hashing, and various searching and sorting algorithms.

## Features

### 1. Route & Station Management (Graphs)
- Add/Delete Stations
- Add/Delete Routes (edges)
- Display all connected stations
- BFS (Breadth-First Search) traversal
- DFS (Depth-First Search) traversal
- Shortest Path computation using Dijkstra's algorithm
- Minimum Spanning Tree (MST) generation using Kruskal's algorithm
- Cycle detection in the network

**Complexity Analysis:**
- BFS: Time O(V+E), Space O(V)
- DFS: Time O(V+E), Space O(V)
- Dijkstra: Time O(V²), Space O(V)
- MST (Kruskal): Time O(E log E), Space O(V)
- Cycle Detection: Time O(V+E), Space O(V)

### 2. Passenger Ticketing System (Queues)
- FIFO queue implementation using linked lists
- Add passengers to queue
- Display queue status
- Process next passenger
- View next passenger without removing

**Complexity Analysis:**
- Enqueue: Time O(1), Space O(1)
- Dequeue: Time O(1), Space O(1)
- Display: Time O(n), Space O(1)

### 3. Vehicle Database (Hashing + Linked Lists)
- Hash table with chaining collision resolution
- Insert, search, and remove vehicles
- Display all vehicles
- Hash table statistics (load factor, longest chain)

**Complexity Analysis:**
- Insert: Average O(1), Worst O(n), Space O(1)
- Search: Average O(1), Worst O(n), Space O(1)
- Remove: Average O(1), Worst O(n), Space O(1)

### 4. History & Undo Operations (Stacks)
- LIFO stack implementation using linked lists
- Store operation history
- Undo last action
- View operation history
- Clear history

**Complexity Analysis:**
- Push: Time O(1), Space O(1)
- Pop: Time O(1), Space O(1)
- Display: Time O(n), Space O(1)

### 5. Route Metadata (Binary Search Tree)
- BST implementation for route metadata storage
- Insert, search, and delete routes
- Inorder, Preorder, and Postorder traversals
- Efficient searching and sorting of routes

**Complexity Analysis:**
- Insert: Average O(log n), Worst O(n), Space O(log n)
- Search: Average O(log n), Worst O(n), Space O(log n)
- Delete: Average O(log n), Worst O(n), Space O(log n)
- Traversal: Time O(n), Space O(n)

### 6. Vehicle Priority Queue (Heap)
- Min-heap implementation for fastest vehicle assignment
- Insert vehicles with priority based on speed
- Extract fastest vehicle
- Heap sort implementation

**Complexity Analysis:**
- Insert: Time O(log n), Space O(1)
- Extract Min: Time O(log n), Space O(1)
- Heap Sort: Time O(n log n), Space O(1)

### 7. Searching & Sorting Module

#### Searching Algorithms:
- **Linear Search**: Time O(n), Space O(1)
  - Best: O(1), Average: O(n), Worst: O(n)
- **Binary Search**: Time O(log n), Space O(1)
  - Best: O(1), Average: O(log n), Worst: O(log n)
  - Requires sorted array

#### Sorting Algorithms:
- **Bubble Sort**: Time O(n²), Space O(1)
  - Best: O(n), Average: O(n²), Worst: O(n²)
- **Selection Sort**: Time O(n²), Space O(1)
  - Best: O(n²), Average: O(n²), Worst: O(n²)
- **Insertion Sort**: Time O(n²), Space O(1)
  - Best: O(n), Average: O(n²), Worst: O(n²)
- **Merge Sort**: Time O(n log n), Space O(n)
  - Best: O(n log n), Average: O(n log n), Worst: O(n log n)
- **Quick Sort**: Time O(n log n) avg, O(n²) worst, Space O(log n)
  - Best: O(n log n), Average: O(n log n), Worst: O(n²)
- **Heap Sort**: Time O(n log n), Space O(1)
  - Best: O(n log n), Average: O(n log n), Worst: O(n log n)
- **Counting Sort**: Time O(n+k), Space O(k)
  - Best: O(n+k), Average: O(n+k), Worst: O(n+k)
- **Radix Sort**: Time O(d*(n+k)), Space O(n+k)
  - Best: O(d*(n+k)), Average: O(d*(n+k)), Worst: O(d*(n+k))

### 8. Analytics & Reporting (Advanced DSA)
- Most crowded station (hash frequency count)
- Busiest route (graph edge weight statistics)
- Fastest vehicle assignment (min-heap)
- Traffic density prediction (heap sorting)
- Daily usage trends (BST traversal)
- Comprehensive report generation

## Project Structure

```
ITNMS/
├── main.cpp           # Main driver program with menu system
├── Graph.h/cpp        # Graph implementation with algorithms
├── Queue.h/cpp        # Queue (FIFO) implementation
├── Stack.h/cpp        # Stack (LIFO) implementation
├── HashTable.h/cpp    # Hash table with chaining
├── BST.h/cpp          # Binary Search Tree implementation
├── Heap.h/cpp         # Min-heap/Priority Queue implementation
├── SearchSort.h/cpp   # Searching and sorting algorithms
├── Analytics.h/cpp    # Analytics and reporting module
├── Makefile           # Build configuration
└── README.md          # This file
```

## Compilation and Execution

### Prerequisites
- C++ compiler supporting C++11 standard (g++, clang++, etc.)
- Make utility (optional, for using Makefile)

### Compilation

**Using Makefile (Recommended):**
```bash
make
```

**Manual Compilation:**
```bash
g++ -std=c++11 -Wall -Wextra -O2 -o itnms main.cpp Graph.cpp Queue.cpp Stack.cpp HashTable.cpp BST.cpp Heap.cpp SearchSort.cpp Analytics.cpp
```

### Execution

**Using Makefile:**
```bash
make run
```

**Direct Execution:**
```bash
./itnms
```

**On Windows:**
```bash
itnms.exe
```

## Usage Guide

### Main Menu Options

1. **Route & Station Management**: Manage transport network topology
2. **Passenger Ticketing System**: Handle passenger queues
3. **Vehicle Database**: Manage vehicle information
4. **History & Undo Operations**: View and undo operations
5. **Searching & Sorting Module**: Test various algorithms
6. **Analytics & Reporting**: View system analytics
7. **Exit**: Close the program

### Example Workflow

1. **Setup Network**:
   - Add stations (e.g., Station 0: "Downtown", Station 1: "Airport")
   - Add routes between stations with weights
   - Display connections

2. **Add Vehicles**:
   - Insert vehicles into database
   - Add vehicles to priority queue

3. **Process Passengers**:
   - Add passengers to ticket queue
   - Process tickets in FIFO order

4. **Analyze Network**:
   - Find shortest paths
   - Generate MST
   - View analytics

5. **Test Algorithms**:
   - Enter dataset
   - Test sorting algorithms
   - Compare complexities

## Data Structures Used

| Data Structure | Implementation | Usage |
|---------------|----------------|-------|
| Arrays | `vector<int>` | Static data storage, station lists |
| Linked Lists | Custom nodes | Queue, Stack, Hash table chaining |
| Queues | Linked list FIFO | Passenger ticketing |
| Stacks | Linked list LIFO | Operation history, undo |
| Trees (BST) | Binary Search Tree | Route metadata storage |
| Heaps | Min-heap array | Vehicle priority queue |
| Graphs | Adjacency list/matrix | Transport network |
| Hash Tables | Chaining collision | Vehicle database |

## Algorithm Complexity Summary

| Algorithm | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| BFS | O(V+E) | O(V) |
| DFS | O(V+E) | O(V) |
| Dijkstra | O(V²) | O(V) |
| MST (Kruskal) | O(E log E) | O(V) |
| Linear Search | O(n) | O(1) |
| Binary Search | O(log n) | O(1) |
| Bubble Sort | O(n²) | O(1) |
| Selection Sort | O(n²) | O(1) |
| Insertion Sort | O(n²) | O(1) |
| Merge Sort | O(n log n) | O(n) |
| Quick Sort | O(n log n) avg | O(log n) |
| Heap Sort | O(n log n) | O(1) |
| Counting Sort | O(n+k) | O(k) |
| Radix Sort | O(d*(n+k)) | O(n+k) |

## Key Features

- ✅ Object-oriented design with separate classes for each module
- ✅ Modular, readable, and well-documented code
- ✅ Complete complexity analysis for all algorithms
- ✅ Meaningful variable and class names
- ✅ Comprehensive menu-driven interface
- ✅ Error handling and input validation
- ✅ All required DSA concepts implemented

## Testing Recommendations

1. **Graph Operations**: Test with various network topologies
2. **Queue Operations**: Verify FIFO behavior
3. **Stack Operations**: Test undo functionality
4. **Hash Table**: Test collision handling
5. **BST**: Test all traversal methods
6. **Sorting**: Compare results across algorithms
7. **Searching**: Test on sorted and unsorted data

## Future Enhancements

- AVL tree implementation for self-balancing
- Graph visualization
- File I/O for data persistence
- Multi-threading for concurrent operations
- GUI implementation
- Database integration

## Author

CS221 Semester Project
Intelligent Transport Network Management System

## License

This project is created for educational purposes as part of CS221 Data Structures and Algorithms course.

## Notes

- All algorithms include detailed complexity analysis
- Code follows C++11 standard
- Memory management handled properly (no memory leaks)
- Input validation included for user safety
- Modular design allows easy extension

---

**For questions or issues, please refer to the code comments or contact the development team.**

# Intelligent-Transport-Network-Management-System-ITNMS-

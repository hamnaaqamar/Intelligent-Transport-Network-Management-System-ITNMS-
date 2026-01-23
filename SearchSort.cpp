#include "SearchSort.h"
#include <iostream>
#include <climits>
#include <cmath>

// Linear Search - Time: O(n), Space: O(1)
// Best: O(1), Average: O(n), Worst: O(n)
int SearchSort::linearSearch(const vector<int>& arr, int key) {
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

// Binary Search - Time: O(log n), Space: O(1)
// Best: O(1), Average: O(log n), Worst: O(log n)
// Requires sorted array
int SearchSort::binarySearch(const vector<int>& arr, int key) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// Bubble Sort - Time: O(n²), Space: O(1)
// Best: O(n), Average: O(n²), Worst: O(n²)
void SearchSort::bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Manual swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break; // Optimized: stops if no swaps
    }
}

// Selection Sort - Time: O(n²), Space: O(1)
// Best: O(n²), Average: O(n²), Worst: O(n²)
void SearchSort::selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            // Manual swap
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

// Insertion Sort - Time: O(n²), Space: O(1)
// Best: O(n), Average: O(n²), Worst: O(n²)
void SearchSort::insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort Helper Functions
void SearchSort::merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> leftArr(n1);
    vector<int> rightArr(n2);
    
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void SearchSort::mergeSortHelper(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Merge Sort - Time: O(n log n), Space: O(n)
// Best: O(n log n), Average: O(n log n), Worst: O(n log n)
void SearchSort::mergeSort(vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}

// Quick Sort Helper Functions
int SearchSort::partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            // Manual swap
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Manual swap
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void SearchSort::quickSortHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

// Quick Sort - Time: O(n log n) avg, O(n²) worst, Space: O(log n)
// Best: O(n log n), Average: O(n log n), Worst: O(n²)
void SearchSort::quickSort(vector<int>& arr) {
    quickSortHelper(arr, 0, arr.size() - 1);
}

// Heap Sort Helper
void SearchSort::heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        // Manual swap
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

// Heap Sort - Time: O(n log n), Space: O(1)
// Best: O(n log n), Average: O(n log n), Worst: O(n log n)
void SearchSort::heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        // Manual swap
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// Counting Sort - Time: O(n+k), Space: O(k)
// Best: O(n+k), Average: O(n+k), Worst: O(n+k)
void SearchSort::countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    
    // Manual max and min finding (no std::max_element or std::min_element)
    int max = arr[0];
    int min = arr[0];
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    int range = max - min + 1;
    
    vector<int> count(range, 0);
    vector<int> output(arr.size());
    
    // Count occurrences
    for (size_t i = 0; i < arr.size(); i++) {
        count[arr[i] - min]++;
    }
    
    // Modify count array
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    
    // Build output array
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
    
    // Copy to original array
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}

// Radix Sort Helper Functions
int SearchSort::getMax(const vector<int>& arr) {
    int max = arr[0];
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void SearchSort::countingSortForRadix(vector<int>& arr, int exp) {
    vector<int> output(arr.size());
    vector<int> count(10, 0);
    
    // Count occurrences
    for (size_t i = 0; i < arr.size(); i++) {
        count[(arr[i] / exp) % 10]++;
    }
    
    // Modify count array
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    // Build output array
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    // Copy to original array
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}

// Radix Sort - Time: O(d*(n+k)), Space: O(n+k)
// Best: O(d*(n+k)), Average: O(d*(n+k)), Worst: O(d*(n+k))
void SearchSort::radixSort(vector<int>& arr) {
    if (arr.empty()) return;
    
    int max = getMax(arr);
    
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSortForRadix(arr, exp);
    }
}

// Utility Functions
void SearchSort::displayArray(const vector<int>& arr) {
    cout << "Array: ";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << endl;
}

void SearchSort::printComplexity(const string& algorithm) {
    cout << "\n=== Complexity Analysis: " << algorithm << " ===" << endl;
    
    if (algorithm == "Linear Search") {
        cout << "Time Complexity - Best: O(1), Average: O(n), Worst: O(n)" << endl;
        cout << "Space Complexity: O(1)" << endl;
    } else if (algorithm == "Binary Search") {
        cout << "Time Complexity - Best: O(1), Average: O(log n), Worst: O(log n)" << endl;
        cout << "Space Complexity: O(1)" << endl;
    } else if (algorithm == "Bubble Sort") {
        cout << "Time Complexity - Best: O(n), Average: O(n²), Worst: O(n²)" << endl;
        cout << "Space Complexity: O(1)" << endl;
    } else if (algorithm == "Selection Sort") {
        cout << "Time Complexity - Best: O(n²), Average: O(n²), Worst: O(n²)" << endl;
        cout << "Space Complexity: O(1)" << endl;
    } else if (algorithm == "Insertion Sort") {
        cout << "Time Complexity - Best: O(n), Average: O(n²), Worst: O(n²)" << endl;
        cout << "Space Complexity: O(1)" << endl;
    } else if (algorithm == "Merge Sort") {
        cout << "Time Complexity - Best: O(n log n), Average: O(n log n), Worst: O(n log n)" << endl;
        cout << "Space Complexity: O(n)" << endl;
    } else if (algorithm == "Quick Sort") {
        cout << "Time Complexity - Best: O(n log n), Average: O(n log n), Worst: O(n²)" << endl;
        cout << "Space Complexity: O(log n)" << endl;
    } else if (algorithm == "Heap Sort") {
        cout << "Time Complexity - Best: O(n log n), Average: O(n log n), Worst: O(n log n)" << endl;
        cout << "Space Complexity: O(1)" << endl;
    } else if (algorithm == "Counting Sort") {
        cout << "Time Complexity - Best: O(n+k), Average: O(n+k), Worst: O(n+k)" << endl;
        cout << "Space Complexity: O(k)" << endl;
    } else if (algorithm == "Radix Sort") {
        cout << "Time Complexity - Best: O(d*(n+k)), Average: O(d*(n+k)), Worst: O(d*(n+k))" << endl;
        cout << "Space Complexity: O(n+k)" << endl;
    }
}


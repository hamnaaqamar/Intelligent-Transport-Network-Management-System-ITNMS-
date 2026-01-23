#ifndef SEARCHSORT_H
#define SEARCHSORT_H

#include <iostream>
#include <vector>
using namespace std;

class SearchSort {
public:
    // Searching Algorithms
    
    // Linear Search - Time: O(n), Space: O(1)
    static int linearSearch(const vector<int>& arr, int key);
    
    // Binary Search - Time: O(log n), Space: O(1) [requires sorted array]
    static int binarySearch(const vector<int>& arr, int key);
    
    // Sorting Algorithms
    
    // Bubble Sort - Time: O(n²), Space: O(1)
    static void bubbleSort(vector<int>& arr);
    
    // Selection Sort - Time: O(n²), Space: O(1)
    static void selectionSort(vector<int>& arr);
    
    // Insertion Sort - Time: O(n²), Space: O(1)
    static void insertionSort(vector<int>& arr);
    
    // Merge Sort - Time: O(n log n), Space: O(n)
    static void mergeSort(vector<int>& arr);
    
    // Quick Sort - Time: O(n log n) avg, O(n²) worst, Space: O(log n)
    static void quickSort(vector<int>& arr);
    
    // Heap Sort - Time: O(n log n), Space: O(1)
    static void heapSort(vector<int>& arr);
    
    // Counting Sort - Time: O(n+k), Space: O(k) where k is range
    static void countingSort(vector<int>& arr);
    
    // Radix Sort - Time: O(d*(n+k)), Space: O(n+k) where d is digits
    static void radixSort(vector<int>& arr);
    
    // Utility functions
    static void displayArray(const vector<int>& arr);
    static void printComplexity(const string& algorithm);
    
private:
    // Helper functions for merge sort
    static void merge(vector<int>& arr, int left, int mid, int right);
    static void mergeSortHelper(vector<int>& arr, int left, int right);
    
    // Helper functions for quick sort
    static int partition(vector<int>& arr, int low, int high);
    static void quickSortHelper(vector<int>& arr, int low, int high);
    
    // Helper functions for heap sort
    static void heapify(vector<int>& arr, int n, int i);
    
    // Helper for radix sort
    static void countingSortForRadix(vector<int>& arr, int exp);
    static int getMax(const vector<int>& arr);
};

#endif


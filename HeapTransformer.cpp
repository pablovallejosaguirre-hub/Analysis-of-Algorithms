#include <iostream>
#include <vector>
#include <algorithm>

// Helper function to maintain the max-heap property for a subtree rooted at index i
void maxHeapify(std::vector<int>& arr, int n, int i) {
    int largest = i;          // Initialize root as largest
    int left = 2 * i + 1;     // Left child index
    int right = 2 * i + 2;    // Right child index

    // If left child exists and is greater than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child exists and is greater than the largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If the largest is not the root, swap and recursively heapify the affected subtree
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

// Function to build a Max-Heap from a random array
void buildMaxHeap(std::vector<int>& arr) {
    int n = arr.size();

    // Find the index of the last non-leaf node
    // Leaf nodes are located from index (n / 2) to n - 1, so we start at (n / 2) - 1
    int startIdx = (n / 2) - 1;

    // Traverse backwards from the last non-leaf node up to the root
    for (int i = startIdx; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

int main() {
    std::vector<int> randomArr = {3, 9, 2, 1, 4, 5};

    std::cout << "Original random array:\n";
    for (int val : randomArr) std::cout << val << " ";
    std::cout << "\n";

    buildMaxHeap(randomArr);

    std::cout << "Transformed into a Max-Heap:\n";
    for (int val : randomArr) std::cout << val << " ";
    std::cout << "\n";

    return 0;
}

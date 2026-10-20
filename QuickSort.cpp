#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

// Partition function (Lomuto)
int Partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Pivot element
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Quick Sort recursive function
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = Partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Helper function to generate a random list of given size
std::vector<int> generateRandomVector(size_t size, int minVal = 1, int maxVal = 100000) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minVal, maxVal);

    for (size_t i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
    return arr;
}

int main() {
    // Testing with a small random list
    std::vector<int> testList = generateRandomVector(10, 1, 100);

    std::cout << "Original random list:\n";
    for (int val : testList) std::cout << val << " ";
    std::cout << "\n";

    quickSort(testList, 0, testList.size() - 1);

    std::cout << "Sorted list:\n";
    for (int val : testList) std::cout << val << " ";
    std::cout << "\n\n";

    return 0;
}

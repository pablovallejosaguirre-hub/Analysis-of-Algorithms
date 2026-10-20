#include <iostream>
#include <vector>

using namespace std;

// Function to merge two sorted sub-arrays into a single sorted array
void Merge(std::vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary vectors
    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    // Copy data to temporary vectors
    for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++) rightArr[j] = arr[mid + 1 + j];

    int i = 0;     // Initial index of first sub-vector
    int j = 0;     // Initial index of second sub-vector
    int k = left;  // Initial index of merged sub-vector

    // Merge the temporary vectors back into arr[left..right]
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

    // Copy the remaining elements of rightArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
}

// Function to implement Merge Sort
void mergeSort(std::vector<int> &arr, int left, int right) {
    if (left >= right)
        return; // Base case: 1 or 0 elements

    int mid = left + (right - left) / 2; // Find the middle point

    // Sort first and second halves
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // Merge the sorted halves
    Merge(arr, left, mid, right);
}

int main() {

    std::vector<int> arr = {12, 11, 13, 5, 6, 7, 5};

    std::cout << "Original:\n";
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    mergeSort(arr, 0, arr.size() - 1);

    std::cout << "\nSorted:\n";
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    return 0;
}

#include <iostream>

void distributionCountingSort(int *A, int n)
{
    if (n <= 1) return;

    // Phase 1: Determine the range of the input to size the distribution array
    int min_val = A[0];
    int max_val = A[0];
    for (int i = 1; i < n; i++)
    {
        if (A[i] < min_val) min_val = A[i];
        if (A[i] > max_val) max_val = A[i];
    }

    int range = max_val - min_val + 1;

    // Dynamically allocate the frequency/distribution array D and sorted output S
    int* D = new int[range];
    int* S = new int[n];

    // Initialize frequencies to zero
    for (int j = 0; j < range; j++)
    {
        D[j] = 0;
    }

    // Phase 2: Count the frequencies of each element
    for (int i = 0; i < n; i++)
    {
        D[A[i] - min_val]++;
    }

    // Phase 3: Accumulate frequencies to establish exact upper-bound indices
    for (int j = 1; j < range; j++)
    {
        D[j] = D[j] + D[j - 1];
    }

    // Phase 4: Distribute elements into S (iterating backwards guarantees stability)
    for (int i = n - 1; i >= 0; i--)
    {
        int pos = A[i] - min_val;
        S[D[pos] - 1] = A[i];
        D[pos]--;
    }

    // Overwrite the original array with the sorted elements
    for (int i = 0; i < n; i++) A[i] = S[i];

    // Deallocate memory to prevent leaks
    delete[] D;
    delete[] S;
}

void printArray(const int* A, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << A[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    // Array includes duplicate values to test algorithmic stability
    int arr[] = {62, 31, 84, 96, 19, 47};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Unsorted array: ";
    printArray(arr, n);

    distributionCountingSort(arr, n);

    std::cout << "Sorted array:   ";
    printArray(arr, n);

    return 0;
}

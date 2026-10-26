#include <iostream>

void comparisonCountingSort(int* A, int n)
{
    // Dynamically allocate arrays for counts and the final sorted output
    int *count = new int[n];
    int *S = new int[n];

    // Initialize all counts to zero
    for (int i = 0; i < n; i++)
    {
        count[i] = 0;
    }

    // Traverse all unique pairs to populate the count array
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (A[i] < A[j])
            {
                count[j]++;
            } else {
                count[i]++;
            }
        }
    }

    // Map each element to its calculated position in the sorted array
    for (int i = 0; i < n; i++)
    {
        S[count[i]] = A[i];
    }

    // Overwrite the original array with the sorted elements
    for (int i = 0; i < n; i++)
    {
        A[i] = S[i];
    }

    // Free the dynamically allocated memory to prevent memory leaks
    delete[] count;
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

int main()
{
    // Initialize an unsorted array for testing
    int arr[] = {62, 31, 84, 96, 19, 47};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Unsorted array: ";
    printArray(arr, n);

    comparisonCountingSort(arr, n);

    std::cout << "Sorted array:   ";
    printArray(arr, n);

    return 0;
}

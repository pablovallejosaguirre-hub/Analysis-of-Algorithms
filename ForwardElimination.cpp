#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// Function to perform forward elimination on an augmented matrix [A | b]
void forwardElimination(std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();

    for (int k = 0; k < n; ++k) {
        // 1. Partial Pivoting: Find the row with the largest absolute value in column k
        int maxRow = k;
        for (int i = k + 1; i < n; ++i) {
            if (std::abs(matrix[i][k]) > std::abs(matrix[maxRow][k])) {
                maxRow = i;
            }
        }

        // Swap the current row with the row containing the maximum pivot element
        if (maxRow != k) {
            std::swap(matrix[k], matrix[maxRow]);
        }

        // 2. Elimination Process: Make all entries below the pivot zero
        for (int i = k + 1; i < n; ++i) {
            double factor = matrix[i][k] / matrix[k][k];

            // Subtract scaled pivot row from the current row
            for (int j = k; j < matrix[0].size(); ++j) {
                matrix[i][j] -= factor * matrix[k][j];
            }
        }
    }
}

// Helper function to print the matrix
void printMatrix(const std::vector<std::vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double val : row) {
            std::cout << std::setw(8) << std::fixed << std::setprecision(2) << val << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    // Example augmented matrix [A | b] for a 3x3 system:
    // 2x + 1y + 1z = 4
    // 1x + 3y + 2z = 6
    // 1x + 0y + 0z = 1
    std::vector<std::vector<double>> augmentedMatrix = {
        {2.0, 1.0, 1.0, 4.0},
        {1.0, 3.0, 2.0, 6.0},
        {1.0, 0.0, 0.0, 1.0}
    };

    std::cout << "Original Augmented Matrix:\n";
    printMatrix(augmentedMatrix);

    forwardElimination(augmentedMatrix);

    std::cout << "\nMatrix after Forward Elimination (Upper Triangular):\n";
    printMatrix(augmentedMatrix);

    return 0;
}

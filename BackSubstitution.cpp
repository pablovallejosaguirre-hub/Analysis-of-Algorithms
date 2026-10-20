#include <iostream>
#include <vector>
#include <iomanip>

// Function to perform back-substitution on an upper-triangular matrix
std::vector<double> backSubstitution(const std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();
    std::vector<double> x(n); // Vector to store the solution

    for (int i = n - 1; i >= 0; --i) {
        double sum = matrix[i][n]; // Start with the right-hand side value (b_i)

        // Subtract known terms of already-solved variables
        for (int j = i + 1; j < n; ++j) {
            sum -= matrix[i][j] * x[j];
        }

        // Divide by the pivot coefficient to find x[i]
        x[i] = sum / matrix[i][i];
    }

    return x;
}


int main() {
    // Augmented upper-triangular matrix [A | b] for the system:
    //   2x +  1y -  1z =  8
    //        3y +  1z = 13
    //             4z = 12
    std::vector<std::vector<double>> matrix = {
        {2, 1, -1,  8},
        {0, 3,  1, 13},
        {0, 0,  4, 12}
    };

    int n = matrix.size();

    // Print the augmented matrix
    std::cout << "Augmented matrix [A | b]:\n";
    for (const auto& row : matrix) {
        for (int j = 0; j < n; ++j) {
            std::cout << std::setw(6) << row[j] << " ";
        }
        std::cout << "|" << std::setw(6) << row[n] << "\n";
    }

    // Solve the system
    std::vector<double> x = backSubstitution(matrix);

    // Print the solution
    std::cout << "\nSolution:\n";
    const char names[] = {'x', 'y', 'z'};
    for (int i = 0; i < n; ++i) {
        std::cout << names[i] << " = " << x[i] << "\n";
    }

    return 0;
}

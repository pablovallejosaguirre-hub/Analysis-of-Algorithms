#include <iostream>
#include <vector>
#include <iomanip>

// 1. LU Decomposition based on Gaussian Elimination
void luDecomposition(const std::vector<std::vector<double>>& A,
                     std::vector<std::vector<double>>& L,
                     std::vector<std::vector<double>>& U) {
    int n = A.size();
    L = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
    U = A; // U starts as a copy of A

    for (int i = 0; i < n; ++i) {
        L[i][i] = 1.0; // Lower triangular matrix has 1s on the diagonal
    }

    for (int k = 0; k < n; ++k) {
        for (int i = k + 1; i < n; ++i) {
            // The multiplier factor from Gaussian Elimination
            double factor = U[i][k] / U[k][k];

            // Store the multiplier in the L matrix
            L[i][k] = factor;

            // Apply elimination on U (same as forward elimination step)
            for (int j = k; j < n; ++j) {
                U[i][j] -= factor * U[k][j];
            }
        }
    }
}

// 2. Forward Substitution to solve Ly = b
std::vector<double> forwardSubstitution(const std::vector<std::vector<double>>& L, const std::vector<double>& b) {
    int n = L.size();
    std::vector<double> y(n);

    for (int i = 0; i < n; ++i) {
        double sum = b[i];
        for (int j = 0; j < i; ++j) {
            sum -= L[i][j] * y[j];
        }
        y[i] = sum / L[i][i]; // L[i][i] is 1.0
    }
    return y;
}

// 3. Back Substitution to solve Ux = y
std::vector<double> backSubstitution(const std::vector<std::vector<double>>& U, const std::vector<double>& y) {
    int n = U.size();
    std::vector<double> x(n);

    for (int i = n - 1; i >= 0; --i) {
        double sum = y[i];
        for (int j = i + 1; j < n; ++j) {
            sum -= U[i][j] * x[j];
        }
        x[i] = sum / U[i][i];
    }
    return x;
}

// Main function to solve Ax = b
std::vector<double> solveLU(const std::vector<std::vector<double>>& A, const std::vector<double>& b) {
    std::vector<std::vector<double>> L, U;
    luDecomposition(A, L, U);

    std::vector<double> y = forwardSubstitution(L, b);
    std::vector<double> x = backSubstitution(U, y);

    return x;
}

int main() {
    // Coefficient matrix A
    std::vector<std::vector<double>> A = {
        {2.0, -1.0, -2.0},
        {-4.0, 6.0, 3.0},
        {-4.0, -2.0, 8.0}
    };

    // Right-hand side vector b
    std::vector<double> b = {-1.0, 9.0, -5.0};

    std::vector<double> x = solveLU(A, b);

    std::cout << "Solution vector x:\n";
    for (int i = 0; i < x.size(); ++i) {
        std::cout << "x[" << i << "] = " << std::fixed << std::setprecision(2) << x[i] << "\n";
    }

    return 0;
}

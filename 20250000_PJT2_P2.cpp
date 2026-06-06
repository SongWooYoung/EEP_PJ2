#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_N = 4;

struct RowView {
    double* row;
    int width;

    // Watch only row array

    // Hadamard subtraction
    RowView& operator-=(const RowView& right) {
        for (int i = 0; i < width; i++) {
            row[i] -= right.row[i];
        }
        return *this;
    }

    // scalar division
    RowView& operator/=(const double& value) {
        for (int i = 0; i < width; i++) {
            row[i] /= value;
        }
        return *this;
    }

    //Row_i = Row_i - (factor * Row_pivot)
    void subtractScaledRow(const RowView& pivotRow, double factor) {
        for (int i = 0; i < width; i++) {
            row[i] -= factor * pivotRow.row[i];
        }
    }

};


struct MatrixView {
    int n;
    double (*matrix)[MAX_N + 1];

    // Focus on row array
    RowView operator[](int index) {
        return RowView{matrix[index], n + 1};
    }

    friend ostream& operator<<(ostream& os, const MatrixView& view) {
        for (int i = 0; i < view.n; i++) {
            for (int j = 0; j < view.n + 1; j++) {
                os << view.matrix[i][j] << " ";
            }
            os << '\n';
        }
        return os;
    }
};

void readAugmentedMatrix(ifstream& inputFile, int& n, double matrix[MAX_N][MAX_N + 1]) {
    // TODO: Fill this function
    // In main function this must work as follows:
    // 1. Read the size of the Matrix size N
    inputFile >> n;
    // 2. Copy the value to the input argument
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            inputFile >> matrix[i][j];
        }
    }

    // for debugging
    // MatrixView view{n, matrix};
    // cout << view;

}

void normalizePivotRow(int n, double matrix[MAX_N][MAX_N + 1], int pivot) {

    // Hust follows the instructure...
    MatrixView view{n, matrix};
    view[pivot] /= view[pivot].row[pivot];

}

void eliminateColumn(int n, double matrix[MAX_N][MAX_N + 1], int pivot) {
    // TODO: Fill this function
    // 1. Eliminate the pivot-th column, except the pivot row.
    MatrixView view{n, matrix};
    for (int i = pivot+1; i < n; i++) {
        if (i == pivot) continue; // Skip the pivot row
        
        // Subtract (factor * pivot row) from the current row 
        view[i].subtractScaledRow(view[pivot], matrix[i][pivot]);
    }

}

void reduceToIdentity(int n, double matrix[MAX_N][MAX_N + 1]) {
    // TODO: Fill this function
    for (int pivot = 0; pivot < n; pivot++) {
        normalizePivotRow(n, matrix, pivot);

        cout << "Debug: After normalizing pivot " << pivot << ":\n";
        MatrixView view{n, matrix};
        cout << view << endl;

        eliminateColumn(n, matrix, pivot);

        cout << "After pivot " << pivot << ":\n";
        // MatrixView view{n, matrix};
        cout << view << endl;
    }
}


void printSolution(int n, double matrix[MAX_N][MAX_N + 1]) {
    // TODO: Fill this function

    // 0. Reversely get the value 

    // 1. Print Last column values as solution

    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << (int) matrix[i][n] << endl;
    }

}

// -----------------------------------------------------------------------
// Main Function — Do not modify
// -----------------------------------------------------------------------
int main() {
    ifstream inputFile;
    string filename;

    int n;
    double matrix[MAX_N][MAX_N + 1];

    cout << "Enter the filename: ";
    cin >> filename;

    inputFile.open(filename);

    if (!inputFile) {
        cout << "Error opening the file." << endl;
        return 0;
    }

    readAugmentedMatrix(inputFile, n, matrix);
    reduceToIdentity(n, matrix);
    printSolution(n, matrix);

    inputFile.close();

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_N = 4;

void PrintMatrix(int n, double matrix[MAX_N][MAX_N + 1]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

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
    PrintMatrix(n, matrix);

}

void normalizePivotRow(int n, double matrix[MAX_N][MAX_N + 1], int pivot) {
    // TODO: Fill this function
}

void eliminateColumn(int n, double matrix[MAX_N][MAX_N + 1], int pivot) {
    // TODO: Fill this function
}

void reduceToIdentity(int n, double matrix[MAX_N][MAX_N + 1]) {
    // TODO: Fill this function
}

void printSolution(int n, double matrix[MAX_N][MAX_N + 1]) {
    // TODO: Fill this function
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
    // reduceToIdentity(n, matrix);
    // printSolution(n, matrix);

    inputFile.close();

    return 0;
}
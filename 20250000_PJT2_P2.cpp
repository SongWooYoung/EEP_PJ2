#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_N = 4;

void readAugmentedMatrix(ifstream& inputFile, int& n, double matrix[MAX_N][MAX_N + 1]) {
    // TODO: Fill this function
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
    reduceToIdentity(n, matrix);
    printSolution(n, matrix);

    inputFile.close();

    return 0;
}
/****************************************************************************
 * 🏭 Smart Factory — EEE22301 Project 2, Problem 1
 *
 * Part 1: Count the minimum adjacent swaps to sort parts → K
 * Part 2: Schedule machine jobs starting from time K
 *
 * Allowed libraries: <iostream>, <fstream>, <random>, <string>
 * Prohibited: std::sort, std::shuffle, std::random_shuffle
 ****************************************************************************/
#include <iostream>
#include <fstream>
#include <random>
#include <string>
using namespace std;

struct Job {
    int id;
    int start;
    int end;
};


/*
    print Function for Debugging
*/
void print(int N, int* weights) {
    cout << "N: " << N << "\nweights: ";
    for (int i = 0; i < N; i++) {
        cout << weights[i] << " ";
    }
    cout << "\n\n";
}

// -----------------------------------------------------------------------
// TODO 1: Implement generateWeights
// -----------------------------------------------------------------------
void generateWeights(int& N, int weights[], mt19937& rng) {
    // 0. Init : random seed, weights :  array and already initialized to 30, rng -> random valuge generator
    
    // initalize the random length (from 10 to 30) of array with random seed
    std::uniform_int_distribution<int> range(10, 30); 
    N = range(rng);
    for (int i = 0; i < N; i++) {
        std::uniform_int_distribution<int> weightRange(1, 100);
        weights[i] = weightRange(rng);
    }
    for (int i = N; i < 30; i++) {
        weights[i] = -1; // Fill remaining with -1 for clarity
    }
}

// -----------------------------------------------------------------------
// TODO 2: Implement mergeSortCount
// -----------------------------------------------------------------------
// Mege Sort Logic 
// 1. Divide : Split list until the length of list is 1 or 2 
// 2. Conquer : Combine left list and right list

// Basic concept is Recurrence
// 9, 7, 10, 15, 18, 2, 1, 4 -> left = 0, right = 7 => id = 3
// Divide   : 9, 7, 10, 15 -> left = 0, right = 3 
//          : 18, 2, 1, 4 left = 4, right = 7
// Divide   : 9, 7  -> left = 0, right = 1 
//          : 10, 15 -> left = 2, right = 3
//          : 18, 2 -> left = 4, right = 5 
//          : 1, 4 -> left = 6, right = 7
// Conqure  : 7, 9 -> left = 0, right = 1
//          : 10, 15 -> left = 2, right = 3 ...

// Merge two sorted halves and count inversions
void merge(int* arr, int left, int mid, int right) {
    // Merge Logic : 
    // Conqure  : 7, 9 -> left = 0, right = 1
    //          : 10, 15 -> left = 2, right = 3 ...
    // compare left of left list and left of right list (Here we can figure out the left and right list each have already been sorted)
    // put smaller value at the list and update the next index and the index of index of list which had smaller value

    // this is because the merge sort are not "in-place"
    int container[right - left + 1]; 
    int leftIndex = left;
    int rightIndex = mid + 1;
    int containerIndex = 0;

    // Merge two sorted halves and count inversions
    while (leftIndex <= mid && rightIndex <= right) {
        if (arr[leftIndex] <= arr[rightIndex]) {
            container[containerIndex++] = arr[leftIndex++];
        } else {
            container[containerIndex++] = arr[rightIndex++];
        }
    }

    // For remains of left list or right list, put them in container
    while (leftIndex <= mid) {
        container[containerIndex++] = arr[leftIndex++];
    }
    while (rightIndex <= right) {
        container[containerIndex++] = arr[rightIndex++];
    }

    // copy the sorted container back to original array
    for (int i = 0; i < containerIndex; i++) {
        arr[left + i] = container[i];
    }
}

void mergeSort(int* arr, int left, int right) {

    // 0. Base case: single element has no inversions
    if (left >= right) {
        return;
    }

    // 1. Divide the array -> setting the mid index
    int mid = (left + right) / 2 ;
    mergeSort(arr, left, mid); // left list
    mergeSort(arr, mid + 1, right); // right list

    // merge : The left and right lists are already sorted, so we can merge them and count inversions at the same time
    merge(arr, left, mid, right); // merge two sorted halves and count inversions
    
}


long long mergeSortCount(int arr[], int left, int right) {

    // 0. Base case: single element has no inversions
    if (left >= right) {
        return 0; 
    }

    // 1. Divide the array -> setting the mid index
    int mid = (left + right) / 2 ;
    mergeSortCount(arr, left, mid); // left list
    mergeSortCount(arr, mid + 1, right); // right list

    // merge : The left and right lists are already sorted, so we can merge them and count inversions at the same time
    merge(arr, left, mid, right); // merge two sorted halves and count inversions
    
    return 0;
}


// -----------------------------------------------------------------------
// TODO 3: Implement countInversions
// -----------------------------------------------------------------------
long long countInversions(int weights[], int N) {
    return 0;
}


// -----------------------------------------------------------------------
// TODO 4: Implement saveToFile
// -----------------------------------------------------------------------
void saveToFile(int seed, const string& content) {
    ofstream fout;  // TODO: open "problem.txt" in append mode
    if (!fout.is_open()) {
        cout << "Failed to open problem.txt" << endl;
        return;
    }
    fout << "== seed: " << seed << " ==" << endl;
    // TODO: write content to file
    fout << string(40, '=') << "\n\n";
    fout.close();
}


// -----------------------------------------------------------------------
// TODO 5: Implement generateJobs
// -----------------------------------------------------------------------
void generateJobs(long long K, int& M, int& R, Job jobs[], mt19937& rng) {

}


// -----------------------------------------------------------------------
// TODO 6: Implement maxNonOverlappingJobs
// -----------------------------------------------------------------------
int maxNonOverlappingJobs(long long K, int R, Job jobs[], int M) {
    return 0;
}


// -----------------------------------------------------------------------
// Main Function — Do not modify
// -----------------------------------------------------------------------
int main() {
    int seed;
    // The program reads one seed value from the console.
    // In Visual Studio, run the program and type the seed in the console window.
    cin >> seed;
    mt19937 rng(seed);

    // Part 1
    int N;
    int weights[30];
    generateWeights(N, weights, rng);

    mergeSort(weights,0, N-1);
    print(N, weights);
    

    // string p1 = "Q. The following is a sequence of " + to_string(N) +
    //             " parts arriving in shuffled order.\n"
    //             "   What is the minimum number of adjacent swaps to sort"
    //             " the sequence in ascending order?\n   ";
    // for (int i = 0; i < N; i++) p1 += to_string(weights[i]) + " ";
    // p1 += "\n";

    // long long K = countInversions(weights, N);
    // cout << p1 << "A. " << K << "\n" << endl;


    // // Part 2
    // int M, R;
    // Job jobs[15];
    // generateJobs(K, M, R, jobs, rng);

    // string p2 = "[Machine available from time K=" + to_string(K) +
    //             ", rest time R=" + to_string(R) + "]\n";
    // p2 += "Q. What is the maximum number of non-overlapping jobs with start_time >= K?\n";
    // p2 += "   Job   Start   End\n";
    // p2 += "   ---   -----   ---\n";
    // for (int i = 0; i < M; i++) {
    //     string idStr = to_string(jobs[i].id);
    //     string startStr = to_string(jobs[i].start);
    //     string endStr = to_string(jobs[i].end);
    //     p2 += "   " + idStr + string(6 - idStr.length(), ' ')
    //           + startStr + string(8 - startStr.length(), ' ')
    //           + endStr + "\n";
    // }

    // int ans2 = maxNonOverlappingJobs(K, R, jobs, M);
    // cout << p2 << "A. " << ans2 << endl;

    // string fullContent = p1 + "A. " + to_string(K) + "\n\n" + p2 + "A. " + to_string(ans2) + "\n";
    // saveToFile(seed, fullContent);

    return 0;
}

/****************************************************************************
 * 🏭 Smart Factory — EEE22301 Project 2, Problem 1
 *
 * Part 1: Count the minimum adjacent swaps to sort parts → K
 * Part 2: Schedule machine jobs starting from time K
 *
 * Allowed libraries: <iostream>, <fstream>, <random>, <string>
 * Prohibited: sort, shuffle, random_shuffle
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

    // For debugging: print Job details
    friend ostream& operator<<(ostream& os, const Job& job) {
    os << "{id: " << job.id
       << ", start: " << job.start
       << ", end: " << job.end << "},\n";
    return os;
    }
};


/*
    print Function for Debugging
    slightly modigfied for console ouput
*/
template<typename T>
void print(int N, T* weights) {
    // cout << "N: " << N << "\nweights: ";
    for (int i = 0; i < N; i++) {
        cout << weights[i] << " ";
    }
    cout << endl;
}

// -----------------------------------------------------------------------
// TODO 1: Implement generateWeights
// -----------------------------------------------------------------------

/*
 * For each shuffle pass:
 *    For i from N−1 down to 1:
 *      Generate a random index j in [0, i]
 *      Swap weights[i] and weights[j]
 */

int drawInt(mt19937& rng, int low, int high) {
    return low + (int)(rng() % (unsigned int)(high - low + 1));
}


void FY_shuffle(int weights[], int N, int K, mt19937& rng, bool DEBUG = false) {
    
    // This is for console output which is mentioned but I forgot to implements
    cout << "[Initial array]: ";
    print(N, weights);

    for (int i = 0; i < K; i++) {
        for (int j = N-1; j > 0; j--) {
            // This declaration has continously regenerate the Object of dist.... -> not consistent
            // uniform_int_distribution<int> dist(0, j);
            // int k = dist(rng);
            //int k = uniform_int_distribution<int>(0, j)(rng);
            int k = drawInt(rng, 0, j); // This is because the uniform_int_distribution can cause different result for different implementations. So I implement my own function to draw random int with uniform distribution.
            swap(weights[j], weights[k]);
        }
        if (DEBUG) {
            cout << "[After shuffle #" << i + 1 << "]: ";
            print(N, weights);
        }
    }
}

// https://stackoverflow.com/questions/70841470/c-pseudo-random-number-generator-not-dependent-on-kernel-version
/*
std::mt19937 is specified to produce the same sequence of numbers for the same seed for all implementations. 
std::uniform_int_distribution is specified to produce a uniform distribution, but the details are not specified, and the result can differ for different implementations.
*/


void generateWeights(int& N, int weights[], mt19937& rng) {
    // 0. Init : random generator, weights :  array and already initialized to 30, rng -> random valuge generator
    
    // initalize the random length (from 10 to 30) of array with random seed
    // uniform_int_distribution<int> range(10, 30); 
    // N = range(rng);
    N = drawInt(rng, 10, 30); // This is because the uniform_int_distribution can cause different result for different implementations. So I implement my own function to draw random int with uniform distribution.

    // This must be the second one.
    // uniform_int_distribution<int> shuffleRange(1, 10);
    // int K_shuffle = shuffleRange(rng);

    int K_shuffle = drawInt(rng, 1, 10); // This is because the uniform_int_distribution can cause different result for different implementations. So I implement my own function to draw random int with uniform distribution.

    // This must be out of the loop.....?
    //uniform_int_distribution<int> weightRange(1, 100);
    for (int i = 0; i < N; i++) {
        //weights[i] = weightRange(rng);
        weights[i] = drawInt(rng, 1, 100); // This is because the uniform_int_distribution can cause different result for different implementations. So I implement my own function to draw random int with uniform distribution.
    }
    for (int i = N; i < 30; i++) {
        weights[i] = -1; // Fill remaining with -1 for clarity
    }

    FY_shuffle(weights, N, K_shuffle, rng, true);
}

// -----------------------------------------------------------------------
// TODO 2: Implement mergeSortCount
// -----------------------------------------------------------------------
// Mege Sort Logic 
// 1. Divide : Split list until the length of list is 1 or 2 
// 2. Conquer : Combine left list and right list

// // Basic concept is Recurrence
// // 9, 7, 10, 15, 18, 2, 1, 4 -> left = 0, right = 7 => id = 3
// // Divide   : 9, 7, 10, 15 -> left = 0, right = 3 
// //          : 18, 2, 1, 4 left = 4, right = 7
// // Divide   : 9, 7  -> left = 0, right = 1 
// //          : 10, 15 -> left = 2, right = 3
// //          : 18, 2 -> left = 4, right = 5 
// //          : 1, 4 -> left = 6, right = 7
// // Conqure  : 7, 9 -> left = 0, right = 1
// //          : 10, 15 -> left = 2, right = 3 ...

// // Merge two sorted halves and count inversions
// void merge(int* arr, int left, int mid, int right) {
//     // Merge Logic : 
//     // Conqure  : 7, 9 -> left = 0, right = 1
//     //          : 10, 15 -> left = 2, right = 3 ...
//     // compare left of left list and left of right list (Here we can figure out the left and right list each have already been sorted)
//     // put smaller value at the list and update the next index and the index of index of list which had smaller value

//     // this is because the merge sort are not "in-place"
//     int container[right - left + 1]; 
//     int leftIndex = left;
//     int rightIndex = mid + 1;
//     int containerIndex = 0;

//     // Merge two sorted halves and count inversions
//     while (leftIndex <= mid && rightIndex <= right) {
//         if (arr[leftIndex] <= arr[rightIndex]) {
//             container[containerIndex++] = arr[leftIndex++];
//         } else {
//             container[containerIndex++] = arr[rightIndex++];
//         }
//     }

//     // For remains of left list or right list, put them in container
//     while (leftIndex <= mid) {
//         container[containerIndex++] = arr[leftIndex++];
//     }
//     while (rightIndex <= right) {
//         container[containerIndex++] = arr[rightIndex++];
//     }

//     // copy the sorted container back to original array
//     for (int i = 0; i < containerIndex; i++) {
//         arr[left + i] = container[i];
//     }
// }

// void mergeSort(int* arr, int left, int right) {

//     // 0. Base case: single element has no inversions
//     if (left >= right) {
//         return;
//     }

//     // 1. Divide the array -> setting the mid index
//     int mid = (left + right) / 2 ;
//     mergeSort(arr, left, mid); // left list
//     mergeSort(arr, mid + 1, right); // right list

//     // merge : The left and right lists are already sorted, so we can merge them and count inversions at the same time
//     merge(arr, left, mid, right); // merge two sorted halves and count inversions
    
// }

long long mergeCount(int* arr, int left, int mid, int right) {

    //clang++ -std=c++17 -Wall -Wextra -O2 -o P1 20250000_PJT2_P1.cpp 20250000_PJT2_P1.cpp:172:19: warning: variable length arrays in C++ are a Clang extension [-Wvla-cxx-extension]
    int container[right - left + 1]; 
    int leftIndex = left;
    int rightIndex = mid + 1;
    int containerIndex = 0;
    long long inv_num = 0;

    // Merge two sorted halves and count inversions
    while (leftIndex <= mid && rightIndex <= right) {
        if (arr[leftIndex] <= arr[rightIndex]) {
            container[containerIndex++] = arr[leftIndex++];
        } else {
            container[containerIndex++] = arr[rightIndex++];
            // Lets suppose 1 7 9 10 ,  2 3 4 5 
            // left index will be fixed to 1 unitl right index goes to the end for right index
            // then 2 will pass 7 9 10 -> (mid - leftIndex + 1)
            inv_num += (mid - leftIndex + 1); // Count inversions: all remaining elements in left half are greater than arr[rightIndex]
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

    return inv_num;
}

long long mergeSortCount(int arr[], int left, int right) {
    if (left >= right) {
        return 0;
    }

    int mid = (left + right) / 2;
    long long inv_count = 0;
    inv_count += mergeSortCount(arr, left, mid);
    inv_count += mergeSortCount(arr, mid + 1, right);
    inv_count += mergeCount(arr, left, mid, right);

    return inv_count;
}


// -----------------------------------------------------------------------
// TODO 3: Implement countInversions
// -----------------------------------------------------------------------
long long countInversions(int weights[], int N) {
    // 1. Because we must not modify the original weights array, we must duplicate the array to the dumps
    long long result = 0;
    int dumps[30];
    for (int i = 0; i < N; i++) {
        dumps[i] = weights[i];
    }

    result = mergeSortCount(dumps, 0, N - 1);

    // this is for console output
    cout << "[Sorted (ascending)]: ";
    print(N, dumps);
    cout << endl;

    return result;
}


// -----------------------------------------------------------------------
// TODO 4: Implement saveToFile
// -----------------------------------------------------------------------
void saveToFile(int seed, const string& content) {
    ofstream fout;  // TODO: open "problem.txt" in append mode
    fout.open("problem1.txt", ios::app); // append mode and open
    if (!fout.is_open()) {
        cout << "Failed to open problem1.txt" << endl;
        return;
    }
    fout << "== seed: " << seed << " ==" << endl;
    // TODO: write content to file
    fout << content << endl;
    fout << string(40, '=') << "\n\n";
    fout.close();
}


// -----------------------------------------------------------------------
// TODO 5: Implement generateJobs
// -----------------------------------------------------------------------
long long Max(long long a, long long b) {
    return (a > b) ? a : b;
}


void generateJobs(long long K, int& M, int& R, Job jobs[], mt19937& rng) {
    // K : time consumed for sorting Parts
    // M : number of jobs (from 8 to 15)
    // R : rest time between jobs
    // jobs : array of Job struct with id, start time and end time

    R = (int) (K % 5) + 1;
    //M = uniform_int_distribution<int>(8, 15)(rng);
    M = drawInt(rng, 8, 15); // This is because the uniform_int_distribution can cause different result for different implementations. So I implement my own function to draw random int with uniform distribution.

    for (int i = 0; i < M; i++) {
        jobs[i].id = i + 1; // Job IDs start from 1
        //jobs[i].start = uniform_int_distribution<int>(Max(0,K-8), K + 25)(rng); // Start time >= K
        jobs[i].start = drawInt(rng, Max(0, (int)K - 8), (int)K + 25); // This is because the uniform_int_distribution can cause different result for different implementations. So I implement my own function to draw random int with uniform distribution.
        //int duration = uniform_int_distribution<int>(2, 10)(rng); // Duration between 1 and 10
        int duration = drawInt(rng, 2, 10); // This is because the uniform_int_distribution can cause different result for different implementations. So I implement my own function to draw random int with uniform distribution.
        jobs[i].end = jobs[i].start + duration;
    }

    //print(M, jobs); // Debugging: print generated jobs
}


// -----------------------------------------------------------------------
// TODO 6: Implement maxNonOverlappingJobs
// -----------------------------------------------------------------------
int maxNonOverlappingJobs(long long K, int R, Job jobs[], int M) {
    
    // 1. Sort jobs by end time (Greedy approach for interval scheduling)
    // bubble sort (under 20 -> it shows greater performance than other algorithms)
    for (int i = 0; i < M; i++) {
        for (int j = i + 1; j < M; j++) {
            if (jobs[i].end > jobs[j].end) {
                swap(jobs[i], jobs[j]);
            }
            else if (jobs[i].end == jobs[j].end) {
                if (jobs[i].start > jobs[j].start) {
                            swap(jobs[i], jobs[j]);
                }
            }
        }
    }

    // seed = 666
    // (132 -> 138) => 141 => (149 -> 151) => 154 => (157 -> 166)
    int count = 0;
    int last_end_time = K;
    for (int i = 0; i < M; i++) {
        if (jobs[i].start >= last_end_time) {
            count++;
            last_end_time = jobs[i].end + R;
        }
    }

    return count;
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

    // mergeSort(weights,0, N-1);
    // print(N, weights);
    

    string p1 = "Q. The following is a sequence of " + to_string(N) +
                " parts arriving in shuffled order.\n"
                "   What is the minimum number of adjacent swaps to sort"
                " the sequence in ascending order?\n   ";
    for (int i = 0; i < N; i++) p1 += to_string(weights[i]) + " ";
    p1 += "\n";

    long long K = countInversions(weights, N);
    cout << p1 << "A. " << K << "\n" << endl;


    // Part 2
    int M, R;
    Job jobs[15];
    generateJobs(K, M, R, jobs, rng);

    string p2 = "[Machine available from time K=" + to_string(K) +
                ", rest time R=" + to_string(R) + "]\n";
    p2 += "Q. What is the maximum number of non-overlapping jobs with start_time >= K?\n";
    p2 += "   Job   Start   End\n";
    p2 += "   ---   -----   ---\n";
    for (int i = 0; i < M; i++) {
        string idStr = to_string(jobs[i].id);
        string startStr = to_string(jobs[i].start);
        string endStr = to_string(jobs[i].end);
        p2 += "   " + idStr + string(6 - idStr.length(), ' ')
              + startStr + string(8 - startStr.length(), ' ')
              + endStr + "\n";
    }

    int ans2 = maxNonOverlappingJobs(K, R, jobs, M);
    cout << p2 << "A. " << ans2 << endl;

    string fullContent = p1 + "A. " + to_string(K) + "\n\n" + p2 + "A. " + to_string(ans2) + "\n";
    saveToFile(seed, fullContent);

    return 0;
}

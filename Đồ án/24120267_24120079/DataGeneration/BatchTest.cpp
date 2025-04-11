#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include "sort.h"
using namespace std;

extern void GenerateData(int a[], int n, int dataType);

const vector<int> dataSizes = { 1000, 2000, 5000, 10000, 20000};
const vector<string> algorithms = {
    "selection-sort", "insertion-sort", "bubble-sort", "shaker-sort",
    "shell-sort", "heap-sort", "merge-sort", "quick-sort",
    "counting-sort", "radix-sort", "flash-sort"
};
const vector<string> dataTypeNames = { "Random", "Sorted", "Reversed", "NearlySorted" };

void runSort(const string& algorithm, vector<int> a, int dataType, int size, ofstream& fout) {
    int comparisons = 0;
    auto start = chrono::high_resolution_clock::now();

    if (algorithm == "selection-sort") selectionSort(a, comparisons);
    else if (algorithm == "insertion-sort") insertionSort(a, comparisons);
    else if (algorithm == "bubble-sort") bubbleSort(a, comparisons);
    else if (algorithm == "shaker-sort") shakerSort(a, comparisons);
    else if (algorithm == "shell-sort") shellSort(a, comparisons);
    else if (algorithm == "heap-sort") heapSort(a, comparisons);
    else if (algorithm == "merge-sort") mergeSort(a, 0, a.size() - 1, comparisons);
    else if (algorithm == "quick-sort") quickSort(a, 0, a.size() - 1, comparisons);
    else if (algorithm == "counting-sort") countingSort(a, comparisons);
    else if (algorithm == "radix-sort") radixSort(a, comparisons);
    else if (algorithm == "flash-sort") flashSort(a, comparisons);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    double timeInSeconds = duration.count() / 1e6;

    fout << dataTypeNames[dataType] << "," << size << "," << algorithm << ","
        << comparisons << "," << fixed << setprecision(19) << timeInSeconds << "\n";
}

int main() {
    ofstream fout("report.csv");
    fout << "DataType,DataSize,Algorithm,Comparisons,Time(s)\n";
    
	cout << "Starting batch testing..." << endl;

    for (int dataType = 0; dataType < 4; ++dataType) {
        for (int size : dataSizes) {
            vector<int> a(size);
            GenerateData(a.data(), size, dataType);

            for (const string& algo : algorithms) {
                vector<int> aCopy = a; // copy để mỗi thuật toán chạy trên cùng input
                cout << "Running " << algo << " on " << dataTypeNames[dataType] << " - Size " << size << endl;
                runSort(algo, aCopy, dataType, size, fout);
            }
        }
    }

    fout.close();
    cout << "Batch testing completed. Results saved to report.csv" << endl;
    return 0;
}

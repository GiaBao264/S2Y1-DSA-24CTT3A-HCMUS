#include "sort.h"

string formatTime(double timeInSeconds) {
    stringstream ss;
    ss << fixed << setprecision(19) << timeInSeconds;

    string result = ss.str();

    result.erase(result.find_last_not_of('0') + 1, string::npos);

    if (!result.empty() && result.back() == '.') {
        result.pop_back();
    }

    return result;
}

bool readFile(const string& filename, vector<int>& a) {
    ifstream fin(filename);
    if (!fin.is_open()) return false;

    int n, x;
    a.clear();
	fin >> n;
    for (int i = 0; i < n && fin >> x; i++) {
        a.push_back(x);
    }

    fin.close();
    return true;
}

bool writeFile(const string& filename, const vector<int>& a, int comparisons, double timeInSeconds) {
    ofstream fout(filename);
    if (!fout.is_open()) return false;

    fout << "Sorted array:\n";
    for (int x : a) {
        fout << x << " ";
    }
    fout << "\nComparisons: " << comparisons;
    fout << "\nTime (s): " << formatTime(timeInSeconds);

    fout.close();
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 7) {
        cout << "Usage: ./source.exe -a <algorithm> -i <input_file> -o <output_file>\n";
        return 1;
    }

    string algorithm = argv[2];
    string inputFile = argv[4];
    string outputFile = argv[6];

    vector<int> a;
    int comparisons = 0;

    if (!readFile(inputFile, a)) {
        cout << "Cannot read input file.\n";
        return 1;
    }

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
    else {
        cout << "Unknown algorithm: " << algorithm << "\n";
        return 1;
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    double timeInSeconds = duration.count() / 1e6;

    if (!writeFile(outputFile, a, comparisons, timeInSeconds)) {
        cout << "Cannot write to output file.\n";
        return 1;
    }

    cout << "Output written to " << outputFile << "\n";
    return 0;
}
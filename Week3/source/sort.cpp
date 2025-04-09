#include "sort.h"

void insertionSort(vector<int>& a, int& comparisons) {
    for (int i = 1; i < a.size(); i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && (++comparisons, a[j] > key)) {
            a[j + 1] = a[j];
            j--;
        }
        if (j >= 0) comparisons++;
        a[j + 1] = key;
    }
}

void shakerSort(vector<int>& a, int& comparisons) {
    int left = 0;
    int right = a.size() - 1;
    while (left < right) {
        for (int i = left; i < right; i++) {
            comparisons++;
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
            }
        }
        right--;
        for (int i = right; i > left; i--) {
            comparisons++;
            if (a[i] < a[i - 1]) {
                swap(a[i], a[i - 1]);
            }
        }
        left++;
    }
}

void heapify(vector<int>& a, int n, int i, int& comparisons) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        comparisons++;
        if (a[left] > a[largest]) {
            largest = left;
        }
    }

    if (right < n) {
        comparisons++;
        if (a[right] > a[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest, comparisons);
    }
}

void heapSort(vector<int>& a, int& comparisons) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i, comparisons);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0, comparisons);
    }
}

int partition(vector<int>& a, int low, int high, int& comparisons) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(vector<int>& a, int low, int high, int& comparisons) {
    if (low < high) {
        int pi = partition(a, low, high, comparisons);
        quickSort(a, low, pi - 1, comparisons);
        quickSort(a, pi + 1, high, comparisons);
    }
}

void countSortByDigit(vector<int>& a, int exp, int& comparisons) {
    int n = a.size();
    vector<int> output(n);
    int count[10] = { 0 };

    for (int i = 0; i < n; i++) {
        int digit = (a[i] / exp) % 10;
        comparisons++;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        comparisons++;
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = (a[i] / exp) % 10;
        comparisons++;
        output[count[digit] - 1] = a[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++) {
        comparisons++;
        a[i] = output[i];
    }
}

void radixSort(vector<int>& a, int& comparisons) {
    if (a.empty()) return;

    int maxVal = a[0];
    for (int i = 1; i < a.size(); i++) {
        comparisons++;
        if (a[i] > maxVal)
            maxVal = a[i];
    }

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        comparisons++;
        countSortByDigit(a, exp, comparisons);
    }
}
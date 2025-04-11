#include "sort.h"

void insertionSort(vector<int>& a, int& comparisons) {
    for (int i = 1; i < a.size(); i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && (COUNT(comparisons), a[j] > key)) {
            a[j + 1] = a[j];
            j--;
        }
        if (j >= 0) COUNT(comparisons); // Đếm lần so sánh cuối khi thoát vòng lặp
        a[j + 1] = key;
    }
}

void shakerSort(vector<int>& a, int& comparisons) {
    int left = 0, right = a.size() - 1;
    while (left < right) {
        for (int i = left; i < right; i++) {
            if (COUNT(comparisons), a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
            }
        }
        right--;
        for (int i = right; i > left; i--) {
            if (COUNT(comparisons), a[i] < a[i - 1]) {
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

    if (left < n && (COUNT(comparisons), a[left] > a[largest])) {
        largest = left;
    }
    if (right < n && (COUNT(comparisons), a[right] > a[largest])) {
        largest = right;
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
    int pivot = a[(low + high) / 2];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (COUNT(comparisons), a[j] < pivot) {
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
        COUNT(comparisons);
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        COUNT(comparisons);
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = (a[i] / exp) % 10;
        COUNT(comparisons);
        output[count[digit] - 1] = a[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++) {
        COUNT(comparisons);
        a[i] = output[i];
    }
}

void radixSort(vector<int>& a, int& comparisons) {
    if (a.empty()) return;

    int maxVal = a[0];
    for (int i = 1; i < a.size(); i++) {
        if (COUNT(comparisons), a[i] > maxVal)
            maxVal = a[i];
    }

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        COUNT(comparisons);
        countSortByDigit(a, exp, comparisons);
    }
}

void selectionSort(vector<int>& a, int& comparisons) {
    for (int i = 0; i < a.size() - 1; i++) {
        int min = i;
        for (int j = i + 1; j < a.size(); j++) {
            if (COUNT(comparisons), a[j] < a[min]) {
                min = j;
            }
        }
        swap(a[i], a[min]);
    }
}

void bubbleSort(vector<int>& a, int& comparisons) {
    for (int i = 0; i < a.size() - 1; i++) {
        for (int j = 0; j < a.size() - i - 1; j++) {
            if (COUNT(comparisons), a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void shellSort(vector<int>& a, int& comparisons) {
    int n = a.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = a[i];
            int j;
            for (j = i; j >= gap && (COUNT(comparisons), a[j - gap] > temp); j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = temp;
        }
    }
}

void merge(vector<int>& a, int left, int mid, int right, int& comparisons) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (COUNT(comparisons), a[i] <= a[j]) {
            temp[k++] = a[i++];
        }
        else {
            temp[k++] = a[j++];
        }
    }
    while (i <= mid) temp[k++] = a[i++];
    while (j <= right) temp[k++] = a[j++];
    for (int x = 0; x < k; x++) a[left + x] = temp[x];
}

void mergeSort(vector<int>& a, int left, int right, int& comparisons) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid, comparisons);
        mergeSort(a, mid + 1, right, comparisons);
        merge(a, left, mid, right, comparisons);
    }
}

void countingSort(vector<int>& a, int& comparisons) {
    int n = a.size();
    int max = *max_element(a.begin(), a.end());

    vector<int> count(max + 1, 0);
    for (int i = 0; i < n; i++) {
        count[a[i]]++;
    }

    int index = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i] > 0) {
            COUNT(comparisons);
            a[index++] = i;
            count[i]--;
        }
    }
}

void flashSort(vector<int>& a, int& comparisons) {
    int n = a.size();
    int max = *max_element(a.begin(), a.end());
    int min = *min_element(a.begin(), a.end());

    int m = 0.43 * n;
    vector<int> l(m, 0);
    double c1 = double(m - 1) / (max - min);

    for (int i = 0; i < n; i++) {
        int j = floor(c1 * (a[i] - min));
        l[j]++;
    }

    for (int i = 1; i < m; i++) {
        l[i] += l[i - 1];
    }

    vector<int> b(n);
    for (int i = n - 1; i >= 0; i--) {
        COUNT(comparisons);
        int j = floor(c1 * (a[i] - min));
        b[l[j] - 1] = a[i];
        l[j]--;
    }

    for (int i = 0; i < n; i++) {
        a[i] = b[i];
    }
}
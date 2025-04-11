#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

// Bật/tắt đếm comparisons bằng cách comment/uncomment dòng dưới
//#define ENABLE_COMPARISONS

#ifdef ENABLE_COMPARISONS
#define COUNT(comparisons) ++comparisons
#else
#define COUNT(comparisons) ((void)0)
#endif

// Khai báo các hàm sắp xếp
void insertionSort(std::vector<int>& a, int& comparisons);
void bubbleSort(std::vector<int>& a, int& comparisons);
void selectionSort(std::vector<int>& a, int& comparisons);
void shakerSort(std::vector<int>& a, int& comparisons);
void shellSort(std::vector<int>& a, int& comparisons);
void heapSort(std::vector<int>& a, int& comparisons);
void mergeSort(std::vector<int>& a, int left, int right, int& comparisons);
void quickSort(std::vector<int>& a, int low, int high, int& comparisons);
void countingSort(std::vector<int>& a, int& comparisons);
void radixSort(std::vector<int>& a, int& comparisons);
void flashSort(std::vector<int>& a, int& comparisons);
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

void insertionSort(vector<int>& a, int& comparisons);
void shakerSort(vector<int>& a, int& comparisons);
void heapSort(vector<int>& a, int& comparisons);
void quickSort(vector<int>& a, int low, int high, int& comparisons);
void radixSort(vector<int>& a, int& comparisons);
void countingSort(vector<int>& a, int& comparisons);
void selectionSort(vector<int>& a, int& comparisons);
void mergeSort(vector<int>& a, int left, int right, int& comparisons);
void bubbleSort(vector<int>& a, int& comparisons);
void shellSort(vector<int>& a, int& comparisons);
void flashSort(vector<int>& a, int& comparisons);
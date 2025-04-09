#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void insertionSort(vector<int>& a, int& comparisons);
void shakerSort(vector<int>& a, int& comparisons);
void heapSort(vector<int>& a, int& comparisons);
void quickSort(vector<int>& a, int low, int high, int& comparisons);
void radixSort(vector<int>& a, int& comparisons);
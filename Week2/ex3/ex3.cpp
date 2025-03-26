#include <iostream>
using namespace std;
#define N 100

int binarySearch(int arr[], int low, int high) {
	while (low < high) {
		int mid = low + (high - low) / 2;
		if (arr[mid] > arr[high]) {
			low = mid + 1;
		}
		else {
			high = mid;
		}
	}
	return arr[low];
}

int main() {
	cout << "Enter the size of array: ";
	int n;
	cin >> n;
	int a[N];
	for (int i = 0; i < n; ++i) {
		cout << "Enter element " << i + 1 << ": ";
		cin >> a[i];
	}
	int result = binarySearch(a, 0, n - 1);
	cout << "Minimum element is: " << result << endl;
	return 0;
}
#include <iostream>
using namespace std;
#define N 100

int shipMinimumCapacity(int weights[], int n, int d) {
	int low = 0, high = 0;
	for (int i = 0; i < n; ++i) {
		low = max(low, weights[i]);
		high += weights[i];
	}
	while (low < high) {
		int mid = low + (high - low) / 2;
		int days = 1; int sum = 0;
		for (int i = 0; i < n; ++i) {
			if (sum + weights[i] > mid) {
				++days;
				sum = 0;
			}
			sum += weights[i];
		}
		if (days > d) {
			low = mid + 1;
		}
		else {
			high = mid;
		}
	}
	return low;
}

int main() {
	cout << "Enter the size of array: ";
	int n;
	cin >> n;
	int weights[N];
	for (int i = 0; i < n; ++i) {
		cout << "Enter weight " << i + 1 << ": ";
		cin >> weights[i];
	}
	cout << "Enter the number of days: ";
	int d;
	cin >> d;
	int result = shipMinimumCapacity(weights, n, d);
	cout << "Minimum capacity is: " << result << endl;
	return 0;
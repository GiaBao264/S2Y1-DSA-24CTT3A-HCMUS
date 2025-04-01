#include <iostream>
#include <algorithm>
using namespace std;
#define N 100

int threeSum(int a[], int n) {
	sort(a, a + n);
	for (int i = 0; i < n - 2; ++i) {
		if (i == 0 || a[i] != a[i - 1]) {
			int low = i + 1, high = n - 1;
			while (low < high) {
				int sum = a[i] + a[low] + a[high];
				if (sum == 0) {
					cout << a[i] << " " << a[low] << " " << a[high] << endl;
					while (low < high && a[low] == a[low + 1]) {
						++low;
					}
					while (low < high && a[high] == a[high - 1]) {
						--high;
					}
					++low;
					--high;
				}
				else if (sum < 0) {
					++low;
				}
				else {
					--high;
				}
			}
		}
	}
	return 0;
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
	threeSum(a, n);
	return 0;
}
#include <iostream>
using namespace std;
#define N 100

int sumTwoNumbers(int a[], int n, int x) {
	int low = 0, high = n - 1;
	while (low < high) {
		if (a[low] + a[high] == x) {
			return 1;
		}
		else if (a[low] + a[high] < x) {
			++low;
		}
		else {
			--high;
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
	cout << "Enter the sum: ";
	int x;
	cin >> x;
	int result = sumTwoNumbers(a, n, x);
	if (result) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
	return 0;
}
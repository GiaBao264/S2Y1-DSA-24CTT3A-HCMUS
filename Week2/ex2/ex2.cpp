#include <iostream>
using namespace std;
#define N 100

int linerSearchwithSentinel(int a[], int n, int x) {
	int last = a[n - 1];
	a[n - 1] = x;
	int i = 0;
	while (a[i] != x) {
		++i;
	}
	a[n - 1] = last;
	if (i < n - 1 || a[n - 1] == x) {
		return i;
	}
	return -1;
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
	cout << "Enter the element to search: ";
	int x;
	cin >> x;
	int result = linerSearchwithSentinel(a, n, x);
	if (result == -1) {
		cout << "Element is not present in array" << endl;
	}
	else {
		cout << "Element is present at index " << result << endl;
	}
	return 0;
}
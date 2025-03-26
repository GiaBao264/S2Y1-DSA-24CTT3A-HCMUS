#include <iostream>
using namespace std;
#define N 100

int linerSearch(int a[], int n, int x) {
	for (int i = 0; i < n; ++i) {
		if (a[i] == x) {
			return i;
		}
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
	int result = linerSearch(a, n, x);
	if (result == -1) {
		cout << "Element is not present in array" << endl;
	}
	else {
		cout << "Element is present at index " << result << endl;
	}
	return 0;
}
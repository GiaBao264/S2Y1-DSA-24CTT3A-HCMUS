#include <iostream>
using namespace std;

#define N 100

bool isAsorted(int a[], int n) {
    if (n == 0 || n == 1)
        return true;

    if (a[n - 2] > a[n - 1])
        return false;

    return isAsorted(a, n - 1);
}

int main() {
    int a[N];
    int size = sizeof(a) / sizeof(a[0]);

    if (isAsorted(a, size))
        cout << "The array is sorted." << endl;
    else
        cout << "The array is not sorted." << endl;

    return 0;
}
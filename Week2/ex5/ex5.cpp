#include <iostream>
using namespace std;
#define N 100

int subArraySum(int a[], int n, int x) {
    int low = 0, high = 0;
    int sum = 0;
    int minLen = n + 1;
    while (high < n) {
        sum += a[high++];
        while (sum >= x) {
            if (high - low < minLen) {
                minLen = high - low;
            }
            sum -= a[low++];
        }
    }
    return (minLen == n + 1) ? 0 : minLen;
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
    int result = subArraySum(a, n, x);
    cout << "Minimum length of subarray is: " << result << endl;
    return 0;
}
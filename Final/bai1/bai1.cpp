#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cout << "Enter n: ";
	cin >> n;

	vector<int> sum1;
	vector<int> sum2;
	int total = 0;

	for (int i = 1; i <= n; ++i) total += i;

	if (total % 2 != 0) {
		cout << "NO";
		return 0;
	}
	else {
		cout << "YES" << endl;
		total /= 2;
		int current = 0;
		for (int i = n; i >= 1; --i) {
			if (current + i <= total) {
				sum1.push_back(i);
				current += i;
			}
			else {
				sum2.push_back(i);
			}
		}
	}
	
	sort(sum1.begin(), sum1.end());
	sort(sum2.begin(), sum2.end());

	cout << sum2.size() << endl;
	for (int i = 0; i < sum2.size(); ++i) {
		cout << sum2[i] << " ";
	}
	cout << endl;
	cout << sum1.size() << endl;
	for (int i = 0; i < sum1.size(); ++i) {
		cout << sum1[i] << " ";
	}

	cout << endl;
	return 0;
}
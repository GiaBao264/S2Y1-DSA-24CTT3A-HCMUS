#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n, m, k;
	cout << "Enter amount tickets and guests:";
	cin >> n >> m;

	vector<int> cost;
	vector<int> maxprice;
	cout << "Enter cost each ticket: ";
	for (int i = 0; i < n; ++i) {
		cin >> k;
		cost.push_back(k);
	}
	cout << "Enter max price: ";
	for (int j = 0; j < m; ++j) {
		cin >> k;
		maxprice.push_back(k);
	}

	vector<bool> used(n, false);
	
	for (int i = 0; i < m; ++i) {
		int max_cost = -1;
		int max_index = -1;
		for (int j = 0; j < n; ++j) {
			if (!used[j] && cost[j] <= maxprice[i] && cost[j] > max_cost) {
				max_cost = cost[j];
				max_index = j;
			}
		}
		if (max_index == -1) {
			cout << -1 << endl;
		}
		else {
			cout << max_cost << endl;
			used[max_index] = true;
		}
	}

	cout << endl;
	return 0;
}
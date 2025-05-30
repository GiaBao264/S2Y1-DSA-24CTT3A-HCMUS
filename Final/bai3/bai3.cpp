#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<vector<char>>& house, vector<vector<bool>>& visited, int i, int j, int n, int m) {
	if (i < 0 || i >= n || j < 0 || j >= m || visited[i][j] || house[i][j] == '#') {
		return;
	}
	visited[i][j] = true;
	dfs(house, visited, i - 1, j, n, m);
	dfs(house, visited, i + 1, j, n, m);
	dfs(house, visited, i, j - 1, n, m);
	dfs(house, visited, i, j + 1, n, m);
}

int main() {
	int n, m;
	cout << "Enter house's size (nxm): ";
	cin >> n >> m;

	cout << "Enter house: " << endl;
	vector<vector<char>> house(n, vector<char>(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> house[i][j];
		}
	}

	vector<vector<bool>> visited(n, vector<bool>(m, false));
	int rooms = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (house[i][j] == '.' && !visited[i][j]) {
				dfs(house, visited, i, j, n, m);
				rooms++;
			}
		}
	}

	cout << rooms;

	return 0;
}
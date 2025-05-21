#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<vector<int>> convertMatrixToList(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Error opening file: " << filename << endl;
		return {};
	}
	int n;
	file >> n;
	if (n <= 0) {
		cerr << "Invalid number."<< endl;
		return {};
	}

	vector<vector<int>> adjMatrix(n, vector<int>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			file >> adjMatrix[i][j];
		}
	}

	int count = 0;
	vector<vector<int>> list(n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (adjMatrix[i][j] == 1) {
				count++;
				list[i].push_back(j);
			}
		}
		list[i].insert(list[i].begin(), count);
	}
	file.close();
	return list;
}

vector<vector<int>> convertListToMatrix(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Error opening file: " << filename << endl;
		return {};
	}
	int n;
	file >> n;
	if (n <= 0) {
		cerr << "Invalid number." << endl;
		return {};
	}

	vector<vector<int>> adjList(n);
	for (int i = 0; i < n; ++i) {
		int num;
		file >> num;
		adjList[i].resize(num);
		for (int j = 0; j < num; ++j) {
			file >> adjList[i][j];
		}
	}

	vector<vector<int>> matrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j : adjList[i]) {
			matrix[i][j] = 1;
		}
	}
	file.close();
	return matrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix) {
	for (int i = 0; i < adjMatrix.size(); ++i) {
		for (int j = 0; j < adjMatrix.size(); ++j) {
			if (adjMatrix[i][j] != adjMatrix[j][i]) {
				return true;
			}
		}
	}
	return false;
}

int countVertices(const vector<vector<int>>& adjMatrix) {
	return adjMatrix.size();
}

int countEdges(const vector<vector<int>>& adjMatrix) {
	int count = 0;
	for (int i = 0; i < adjMatrix.size(); ++i) {
		for (int j = (isDirected(adjMatrix) ? 0 : i + 1); j < adjMatrix.size(); ++j) {
			if (adjMatrix[i][j] == 1) count++;
		}
	}
	return count;
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
	vector<int> isolatedVertices;
	for (int i = 0; i < adjMatrix.size(); ++i) {
		bool IsisolatedVertices = true;
		for (int j = 0; j < adjMatrix.size(); ++j) {
			if (adjMatrix[i][j] == 1) {
				IsisolatedVertices = false;
				break;
			}
		}
		if (IsisolatedVertices) isolatedVertices.push_back(i);
	}
	return isolatedVertices;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
	for (int i = 0; i < adjMatrix.size(); ++i) {
		for (int j = 0; j < adjMatrix.size(); ++j) {
			if (i != j) {
				if (adjMatrix[i][j] == 0 || adjMatrix[j][i] == 0) return false;
			}
		}
	}
	return true;
}

bool isBipartite(const vector<vector<int>>& adjMatrix) {

}
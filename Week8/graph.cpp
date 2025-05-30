#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <stack>

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
	int count = 0;
	vector<vector<int>> list(n);
	for (int i = 0; i < n; ++i) {
		int count = 0;
		for (int j = 0; j < n; ++j) {
			file >> adjMatrix[i][j];
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

	vector<vector<int>> matrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; ++i) {
		int num, v;
		file >> num;
		for (int j = num; j > 0; --j) {
			file >> v;
			matrix[i][v] = 1;
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
	int n = adjMatrix.size();
	vector<int> color(n, -1);

	for (int i = 0; i < n; ++i) {
		if (color[i] != -1) continue;

		queue<int> q;
		q.push(i);
		color[i] = 0;

		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v = 0; v < n; ++v) {
				if (adjMatrix[u][v] == 1) {
					if (color[v] == -1) {
						color[v] = 1 - color[u];
						q.push(v);
					}
					else if (color[v] == color[u]) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> color(n, -1);
	if (!isBipartite(adjMatrix)) return false;

	vector<vector<int>> groups(2);

	for (int i = 0; i < n; ++i) if (color[i] != -1) groups[color[i]].push_back(i);
	for (int u : groups[0]) {
		for(int v : groups[1]) {
			if (adjMatrix[u][v] == 0) return false;
		}
	}
	return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> result(n, vector<int>(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if(adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1) {
				result[i][j] = result[j][i] = 1;
			}
		}
	}
	return result;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> complement(n, vector<int>(n, 0));
	for(int i =0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i != j && adjMatrix[i][j] == 0) {
				complement[i][j] = 1;
			}
		}
	}
	return complement;
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> graph = adjMatrix;
	stack<int> stack;
	vector<int> cycle;
	stack.push(0);
	while (!stack.empty()) {
		int u = stack.top();
		bool found = false;
		for (int v = 0; v < n; ++v) {
			if (graph[u][v] == 1) {
				stack.push(v);
				graph[u][v] = graph[v][u] = 0;
				found = true;
				break;
			}
		}
		if(!found) {
			cycle.push_back(u);
			stack.pop();
		}
	}
	return cycle;
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<vector<int>> tree(n, vector<int>(n, 0));
	vector<bool> visited(n, false);
	stack<int> stack;
	visited[start] = true;
	stack.push(start);
	while (!stack.empty()) {
		int u = stack.top(); stack.pop();
		for (int v = 0; v < n; ++v) {
			if (adjMatrix[u][v] == 1 && !visited[v]) {
				visited[v] = true;
				tree[u][v] = tree[v][u] = 1;
				stack.push(v);
			}
		}
	}
	return tree;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<vector<int>> tree(n, vector<int>(n, 0));
	vector<bool> visited(n, false);
	queue<int> queue;
	visited[start] = true;
	queue.push(start);
	while (!queue.empty()) {
		int u = queue.front(); queue.pop();
		for (int v = 0; v < n; ++v) {
			if (adjMatrix[u][v] == 1 && !visited[v]) {
				visited[v] = true;
				tree[u][v] = tree[v][u] = 1;
				queue.push(v);
			}
		}
	}
	return tree;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	if (u < 0 || u >= n || v < 0 || v >= n) return false;
	vector<bool> visited(n, false);
	queue<int> queue;
	queue.push(u);
	visited[u] = true;
	while (!queue.empty()) {
		int current = queue.front(); queue.pop();
		if (current == v) return true;
		for (int i = 0; i < n; ++i) {
			if (adjMatrix[current][i] == 1 && !visited[i]) {
				visited[i] = true;
				queue.push(i);
			}
		}
	}
	return false;
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	if (start < 0 || start >= n || end < 0 || end >= n) return {};
	vector<int> dist(n, INT_MAX), prev(n, -1);
	vector<bool> visited(n, false);
	dist[start] = 0;
	for (int i = 0; i < n; ++i) {
		int u = -1;
		for (int j = 0; j < n; ++j) {
			if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
				u = j;
			}
		}
		if (u == -1 || dist[u] == INT_MAX) break;
		visited[u] = true;
		for (int v = 0; v < n; ++v) {
			if (adjMatrix[u][v] > 0 && !visited[v] && dist[v] > dist[u] + adjMatrix[u][v]) {
				dist[v] = dist[u] + adjMatrix[u][v];
				prev[v] = u;
			}
		}
	}
	vector<int> path;
	for (int at = end; at != -1; at = prev[at]) {
		path.insert(path.begin(), at);
	}
	if (path.size() == 1 && path[0] != start) return {};
	return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> dist(n, INT_MAX), prev(n, -1);
	dist[start] = 0;
	for (int i = 0; i < n - 1; ++i) {
		for (int u = 0; u < n; ++u) {
			for (int v = 0; v < n; ++v) {
				if (adjMatrix[u][v] && dist[u] != INT_MAX && dist[v] > dist[u] + adjMatrix[u][v]) {
					dist[v] = dist[u] + adjMatrix[u][v];
					prev[v] = u;
				}
			}
		}
	}
	vector<int> path;
	for (int at = end; at != -1; at = prev[at]) {
		path.insert(path.begin(), at);
	}
	return path;
}
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 2e5 + 5;
vector<int> adj[MAXN];
int subordinates[MAXN];

int dfs(int u) {
    int count = 0;
    for (int v : adj[u]) {
        count += 1 + dfs(v);
    }
    subordinates[u] = count;
    return count;
}

int main() {
    int n;
    cin >> n;

    for (int i = 2; i <= n; ++i) {
        int boss;
        cin >> boss;
        adj[boss].push_back(i);
    }

    dfs(1);

    for (int i = 1; i <= n; ++i) {
        cout << subordinates[i] << " ";
    }
    cout << endl;
    return 0;
}

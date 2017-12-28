#include <bits/stdc++.h>
using namespace std;

const int MAX = 100100;
vector<int> adj[MAX];
int n, m, mx[MAX], vis[MAX], co[MAX];

int dfs(int u) {
	if (vis[u])
		return mx[u];
	vis[u] = 1;
	mx[u] = co[u];
	for (int i = 0, len = adj[u].size(); i < len; ++i)
		mx[u] = max(mx[u], (co[u] && !co[adj[u][i]]) + dfs(adj[u][i]));
	return mx[u];
}
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> co[i];
	for (int i = 0, u, v; i < m; ++i) {
		cin >> u >> v;
		adj[u].push_back(v);
	}

	int ans = 0;
	for (int i = 0; i < n; ++i)
		ans = max(ans, dfs(i));
	cout << ans << endl;
	return 0;
}
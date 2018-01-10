/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: D. Jzzhu and Cities
	@link: http://codeforces.com/contest/450/problem/D
	@judge: Codeforces
	@idea: calculate single source shortest path from the capital city to all cities, in the paths comparison
		if there's a tie in the cost of two paths take the one that doesn't end with a train track
*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define U se
#define W fi.fi
#define T fi.se
using namespace std;
typedef pair<pair<int, int>, int> node;
const int MAX = 300300;
vector<node> adj[MAX];
bool vis[MAX];
int n, m, k;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0, u, v, x; i < m; ++i) {
		scanf("%d%d%d", &u, &v, &x);
		adj[u].push_back({{ x, 0 }, v });
		adj[v].push_back({{ x, 0 }, u });
	}
	for (int i = 0, s, y; i < k; ++i) {
		scanf("%d%d", &s, &y);
		adj[1].push_back({{ y, 1 }, s });
		adj[s].push_back({{ y, 1 }, 1 });
	}

	priority_queue<node, vector<node>, greater<node> > q;
	q.push({{ 0, 0 }, 1 });
	while (!q.empty()) {
		node cur = q.top();
		q.pop();
		if (vis[cur.U])
			continue;
		vis[cur.U] = true;
		k -= cur.T;
		for (int i = 0, len = adj[cur.U].size(); i < len; ++i)
			if (!vis[adj[cur.U][i].U])
				q.push({{ cur.W + adj[cur.U][i].W, adj[cur.U][i].T }, adj[cur.U][i].U });
	}

	cout << k << endl;
	return 0;
	
}
/*input

7 9
1 5
2 7
7 5
5 4
4 6
6 1
4 3
3 2
6 2
0 0
*/
/*
6 7
1 6
6 3
3 4
4 1
4 5
5 2
2 3

8 12
1 3
3 4
4 2
2 5
5 6
6 1
1 7
7 1
8 7
7 8
8 2
2 8
2 1
1 2

6 8
1 6
6 3
1 3
3 4
4 1
4 5
5 2
2 4

7 14
1 3
3 4
4 5
5 1
5 6
6 7
7 5
5 7
7 2
2 7
2 6
3 8
8 5
1 2

15 26
1 3
3 4
4 5
5 2
2 5
5 4
4 3
3 1
1 6
6 7
7 2
2 8
8 7
7 9
9 6
6 10
10 1
2 11
11 12
12 1
1 13
13 12
12 14
14 11
11 15
15 2

5 10
1 3
3 1
3 4
4 3
4 2
2 4
1 5
5 1
5 2
2 5

8 18
1 3
3 4
4 5
5 1
5 6
6 7
7 5
5 7
7 2
2 7
2 6
3 8
8 5
1 2
1 1
2 2
3 3
5 5

7 9
1 5
2 7
7 5
5 4
4 6
6 1
4 3
3 2
6 2

6 7
1 6
6 3
3 4
4 1
4 5
5 2
2 3

7 8
1 6
6 3
4 1
4 5
5 2
2 3
3 7
7 4


0 0
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem:
	@link:
	@judge:
	@idea:
*/
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair<int, int> pii;
const int MAX = 110;
const int inf = MAX * MAX;
vector<vector<int> > adj;
bool vis[MAX][MAX];
int cost[MAX][MAX], ini[MAX][MAX], rev[MAX][MAX], common[MAX][MAX], n, m;

int main() {
	int T{};
	while (cin >> n >> m && (n || m)) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
					ini[i][j] = common[i][j] = rev[i][j] = inf;
		adj.clear(); adj.resize(n + 1);
		for (int i = 0, u, v; i < m; ++i) {
			cin >> u >> v;
			ini[u][v] = 1;
			rev[v][u] = 1;
		}

		for (int i = 1; i <= n; ++i)
			ini[i][i] = rev[i][i] = common[i][i] = 0;

		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (rev[i][j] == 1 && ini[i][j] == 1)
					common[i][j] = 1;

		for (int k = 1; k <= n; ++k)
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j) {
					ini[i][j] = min(ini[i][j], ini[i][k] + ini[k][j]);
					rev[i][j] = min(rev[i][j], rev[i][k] + rev[k][j]);
					common[i][j] = min(common[i][j], common[i][k] + common[k][j]);
				}

		cout << "Network " << ++T << endl;
		if (ini[1][2] >= inf || ini[2][1] >= inf) {
			cout << "IMPOSSIBLE" << endl << endl;
			continue;
		}

		

		memset(vis, 0, sizeof vis);
		priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<pair<int, pii> > > q;
		q.push({1, { 1, 1 } });
		int ans = 0;
		while (q.size()) {
			auto cur = q.top();
			int u = cur.se.fi, v = cur.se.se, c = cur.fi;
			q.pop();
			if (vis[u][v])
				continue;

			if (u == 2 && v == 2) {
				ans = c;
				break;
			}
			vis[u][v] = true;
			if (!vis[v][u])
				q.push({ c + common[u][v] - 1, { v, u }});
			for (int i = 1; i <= n; ++i) {
				if (!vis[i][v])
					q.push({ c + ini[u][i], { i, v }});
				if (!vis[u][i])
					q.push({ c + rev[v][i], { u, i }});
				if (u == v && !vis[i][i])
					q.push({ c + common[u][i], { i, i }});
			}
		}

		cout << "Minimum number of nodes = " << ans << endl << endl;
	}
	return 0;
}
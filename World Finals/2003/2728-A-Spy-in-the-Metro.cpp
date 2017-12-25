/*input
4
55
5 10 15
4
0 5 10 20
4
0 5 10 15
4
18
1 2 3
5
0 3 6 10 12
6
0 3 5 7 12 15
2
30
20
1
20
7
1 3 5 7 11 13 17
0
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 2728 - A Spy in the Metro
	@link: https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=729
	@judge: LIVE ARCHIVE
	@idea: dynamic programming
*/

#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
const int MAX = 52;
const int inf = 250;

int n, t, dist[MAX][MAX], offset[2][MAX], sz[2], st[2];
int mem[205][MAX];

int dp(int idx, int curt) {
	if (curt > t)
		return inf;
	if (idx == n && curt == t)
		return 0;
	int& ret = mem[curt][idx];
	if (~ret)
		return ret;
	ret = 1 + dp(idx, curt + 1);
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < sz[i]; ++j) {
			int nt = offset[i][j] + dist[idx][st[i]];
			if (nt < curt)
				continue;
			for (int k = 1; k <= n; ++k) {
				if ((!i && k > idx) || (i && k < idx)) {
					ret = min(ret, nt - curt + dp(k, nt + dist[k][idx]));
				}
			}
		}
	}
	return ret;
}

int main() {
	int Case = 0;
	while (cin >> n && n) {
		memset(dist, 11, sizeof dist);
		memset(mem, -1, sizeof mem);
		cin >> t;
		dist[0][0] = dist[1][1] = 0;
		for (int i = 2; i <= n; ++i) {
			dist[i][i] = 0;
			cin >> dist[i - 1][i];
			dist[i][i - 1] = dist[i - 1][i];
		}

		for (int k = 1; k <= n; ++k)
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

		st[0] = 1;
		st[1] = n;
		for (int i = 0; i < 2; ++i) {
			cin >> sz[i];
			for (int j = 0; j < sz[i]; ++j)
				cin >> offset[i][j];
		}

		int ans = dp(1, 0);

		cout << "Case Number " << ++Case << ": ";
		if (ans >= inf)
			cout << "impossible" << endl;
		else
			cout << ans << endl;
	}
	return 0;
}

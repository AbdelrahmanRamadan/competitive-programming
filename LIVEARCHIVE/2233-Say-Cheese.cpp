/*input
1
20 20 20 1
0 0 0
0 0 10
1
5 0 0 4
0 0 0
10 0 0
-1
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 2233 - Say Cheese
	@link: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=35&page=show_problem&problem=234
	@judge: LIVEARCHIVE
	@idea: dijkstra with holes as verticies and pair wise distances as weighted edges 
*/

#include <bits/stdc++.h>
using namespace std;

typedef long double myf;
typedef pair<myf, int> pfi;

const int MAX = 110;
int n;
myf x[MAX], y[MAX], z[MAX], r[MAX], ans[MAX], cost[MAX][MAX];
bool vis[MAX];

inline void scanp(int i) {
	cin >> x[i] >> y[i] >> z[i];
}

inline myf sqr(myf x) {
	return x * x;
}

int main() {
	int T{};
	while (cin >> n && n != -1) {
		memset(vis, 0, sizeof vis);
		for (int i = 1; i <= n; ++i) {
			scanp(i);
			cin >> r[i];
		}
		
		scanp(0);
		scanp(++n);
		r[0] = r[n] = 0;
		
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= n; ++j) {
				myf d = sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]) + sqr(z[i] - z[j]));
				cost[i][j] = max<myf>(0, d - (r[i] + r[j]));
			}
		}

		priority_queue<pfi, vector<pfi>, greater<pfi> > q;
		q.push({ 0, 0 });
		while (!q.empty()) {
			myf c = q.top().first;
			int cur = q.top().second;
			q.pop();

			if (vis[cur])
				continue;
			vis[cur] = true;
			ans[cur] = c;
			if (cur == n)
				break;

			for (int i = 0; i <= n; ++i)
				if (!vis[i])
					q.push({ c + cost[cur][i], i });

		}

		cout << setprecision(0) << fixed;
		cout << "Cheese " << ++T << ": Travel time = " << ans[n] * 10 << " sec" << endl;
	}
	return 0;
}
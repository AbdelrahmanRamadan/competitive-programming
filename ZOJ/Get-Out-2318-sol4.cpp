/*input
4

13
2 2 1.1
-2 2 1.1
2 -2 1.0
-2 -2 1.0
2 -5 1.0
0 -8 1.0
-2 -6 1.0
0 0 1
2 2 1.1
-2 2 1.1
2 -2 1.0
-2 -2 1.0
0 -3 0.01
10 10 1

5
2 2 1.1
-2 2 1.1
2 -2 1.0
-2 -2 1.0
0 -3 0.01
10 10 1

7
2 2 1.1
-2 2 1.1
2 -2 1.0
-2 -2 1.0
2 -5 1.0
0 -8 1.0
-2 -6 1.0
0 0 1

5
2 2 1.1
-2 2 1.1
2 -2 1.0
-2 -2 1.0
0 -3 0.01
0 0 1
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: ZOJ 2318 - Get Out!
	@link: http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemId=1318
	@judge: ZOJ
	@idea: complexity O(N ^ 2)
		first we turn Kolobok circle into single point by adding its radius to each other circle,
		whenever two circles strictly intersection (have non-zero common area) connect them with an edge,
		the edge weight should be the signed angle from A to B, now we have a graph that contains cycles,
		we run a dfs on the graph to find cycles and if we found any cycle then we check if the cycle angles sum to zero
		if they sum to zero then the point is outside the polygon since the winding number is zero
		Winding number: simply is how many full cycles of angle (2 * PI) done around the point

		Optimization: instead of calculating the angle it's sufficient to just keep track of the quarter we are
				in right now in the same way of the winding number inclusion test algorithm (see the next link for more calarification)
					http://geomalgorithms.com/a03-_inclusion.html
*/

#include <bits/stdc++.h>
#define X real()
#define Y imag()
#define fi first
#define se second
#define EPS 1e-8
using namespace std;
typedef long double myf;
typedef complex<myf> point;

const int MAX = 330;
const myf PI = acos(-1.0L);

int n, wn[MAX], vis[MAX];
point pnts[MAX], sp;
myf rad[MAX], sr;
vector<vector<pair<int, int> > > adj;

istream& operator >> (istream& fin, point& p) {
	myf x, y;
	fin >> x >> y;
	p = point({ x, y });
	return fin;
}

myf dist(const point& p) {
	return sqrt(p.X * p.X + p.Y * p.Y);
}

inline myf cross(const point& a, const point& b) {
	return a.X * b.Y - a.Y * b.X;
}

int winding(const point& a, const point& b) {
	if (a.Y <= EPS){
		if (b.Y > EPS && cross(b - a, point(0, 0) - a) > EPS)
			return 1;
	} else if(b.Y <= EPS && cross(b - a, point(0, 0) - a) < EPS)
		return -1;
	return 0;
}

bool dfs(int u, int p, int cur) {
	if (vis[u] == 1)
		return cur - wn[u] != 0;
	vis[u] = 1;
	wn[u] = cur;

	bool flag = false;
	for (int i = 0, len = adj[u].size(); i < len; ++i) {
		if(adj[u][i].fi != p && vis[adj[u][i].fi] != 2 && dfs(adj[u][i].fi, u, cur + adj[u][i].se)) {
			flag = true;
			break;
		}
	}
	vis[u] = 2;
	return flag;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		adj.clear();
		adj.resize(n + 1);
		memset(vis, 0, (n + 1) * sizeof vis[0]);

		for (int i = 1; i <= n; ++i)
			cin >> pnts[i] >> rad[i];
		cin >> sp >> sr;

		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (i != j && dist(pnts[j] - pnts[i]) + EPS < rad[i] + rad[j] + sr * 2)
					adj[i].push_back({ j, winding(pnts[i] - sp, pnts[j] - sp) });
	
		bool flag = false;
		for (int i = 1; i <= n; ++i)
			if (!vis[i])
				flag |= dfs(i, 0, 0);

		cout << (flag ? "NO" : "YES") << endl;
		if (T)
			cout << endl;
	}
	return 0;
}

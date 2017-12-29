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
	@idea: 
		first we turn Kolobok circle into single point by adding its radius to each other circle,
		whenever two circles strictly intersection (have non-zero common area) connect them with an edge,
		now we have a graph that contains cycles, we run a dfs on the graph to find cycles and if we find any cycle
		then we found a closed polygon of circles and we check if our point is inside that polygon.
		CAUTION: There might be self-intersecting polygons so raycasting algorithm for point inclusion test won't work
			in this solution i calculated the winding number to check for inclusion
*/

#include <bits/stdc++.h>
#define X real()
#define Y imag()
#define fi first
#define se second
#define dot(A,B) ((A).X*(B).X+(A).Y*(B).Y)
#define dot3(a,b,c) dot(VEC(a,b),VEC(a,c))
#define cross(A,B) ((A).X*(B).Y-(A).Y*(B).X)
#define cross3(a,b,c) cross(VEC(a,b),VEC(a,c))
#define VEC(a,b) ((b)-(a))
#define EPS 1e-7
using namespace std;
typedef long double myf;
typedef complex<myf> point;

const int MAX = 330;
int n;
point pnts[MAX], sp;
myf rad[MAX], sr;
vector<vector<int> > adj;
int vis[MAX];

istream& operator >> (istream& fin, point& p) {
	myf x, y;
	fin >> x >> y;
	p = point({ x, y });
	return fin;
}

myf dist(const point& p) {
	return sqrt(p.X * p.X + p.Y * p.Y);
}

bool in_poly(const vector<point>& v, point p) {
	int wn = 0;
	for (int i = 0, len = v.size(); i < len; ++i) {
		int j = i == (len - 1) ? 0 : (i + 1);
		if (v[i].Y <= p.Y + EPS)
			wn += (v[j].Y > p.Y + EPS) && cross(v[j] - v[i], p - v[i]) > EPS;
		else
			wn -= (v[j].Y <= p.Y + EPS) && cross(v[j] - v[i], p - v[i]) < EPS;
	}
	return wn != 0;
}

bool dfs(int u, int p, vector<int>& v) {
	if (vis[u] == 1) {
		vector<point> poly;
		int i = v.size();
		do {
			poly.push_back(pnts[v[--i]]);
		} while (v[i] != u);
		return in_poly(poly, sp);
	}

	vis[u] = 1;
	v.push_back(u);
	bool flag = false;
	for (int i = 0, len = adj[u].size(); i < len; ++i)
		if(adj[u][i] != p && vis[adj[u][i]] != 2 && dfs(adj[u][i], u, v)) {
			flag = true;
			break;
		}

	vis[u] = 2;
	v.pop_back();
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
				if (i != j && dist(VEC(pnts[i], pnts[j])) + EPS < rad[i] + rad[j] + sr * 2)
					adj[i].push_back(j);
	
		bool flag = false;
		for (int i = 1; i <= n; ++i) if (!vis[i]) {
			vector<int> v;
			flag |= dfs(i, 0, v);
		}

		cout << (flag ? "NO" : "YES") << endl;
		if (T)
			cout << endl;
	}
	return 0;
}

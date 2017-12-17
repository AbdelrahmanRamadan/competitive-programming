/*input
2
3 3
1 3 4 3
3 4 3 1
3 1 5 1
1 2
1 3
2 2
3 3
1 1 3 1
2 1 3 1
3 2 4 1
1 2
1 3
2 3
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: ANTTT - The Ant
	@link: http://www.spoj.com/problems/ANTTT/
	@judge: SPOJ
	@idea: add edge if two segments intersect, then check connectivity using dsu or flood fill
*/

#include <bits/stdc++.h>
#define EPS 1e-9
#define X real()
#define Y imag()
using namespace std;
vector<vector<int> > adj;
typedef long double myf;
typedef complex<myf> point;

const int MAX = 1010;
point pnts[MAX][2];
int parent[MAX];

inline myf cross(point a, point b) {
	return a.X * b.Y - a.Y * b.X;
}

inline point vec(point a, point b) {
	return b - a;
}

istream& operator >> (istream& fin, point& o) {
	int x, y;
	fin >> x >> y;
	o = point(x, y);
	return fin;
}

bool operator < (point a, point b) {
	return a.X + EPS < b.X || (a.X - b.X < EPS && a.Y + EPS < b.Y);
}

pair<point, int> in(point a0, point a1, point b0, point b1) {
	myf s = cross(vec(b0, a0), vec(a0, a1)) / cross(vec(b0, b1), vec(a0, a1));
	return { vec(b0, b1) * s + b0, isnan(s) + isinf(s) * 2 };
}

bool seg_intersect(point a, point b, point c, point d) {
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);
	
	auto p = in(a, b, c, d);
	if (p.second == 2)
		return false;

	if(p.second == 1)
		return !((a < c && b < c) || (d < a && d < b));
	
	return !((p.first < a || b < p.first) || (p.first < c || d < p.first));
}

int get_parent(int u) {
	if (u == parent[u])
		return u;
	return parent[u] = get_parent(parent[u]);
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n, m;
		cin >> n >> m;
		adj.clear();
		adj.resize(n + 1);
		for (int i = 1; i <= n; ++i)
			parent[i] = i;

		for (int i = 1; i <= n; ++i) {
			cin >> pnts[i][0] >> pnts[i][1];
			for (int j = 1; j < i; ++j) {
				if (seg_intersect(pnts[i][0], pnts[i][1], pnts[j][0], pnts[j][1])) {
					parent[get_parent(i)] = get_parent(j);
				}
			}
		}

		for (int i = 1; i <= m; ++i) {
			int a, b;
			cin >> a >> b;
			cout << (get_parent(a) == get_parent(b) ? "YES" : "NO") << endl;
		}

	}	
	return 0;
}

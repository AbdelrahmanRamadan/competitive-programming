/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 11665 - Chinese Ink
	@link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2712
	@judge: UVA
	@idea: two polygons are connected if one of them contain any point of the second vertexes or if any
		edge from the first intersected with edge from the second.
		so we mark all connected polygons in a single group using disjoint set or dfs for instance.
*/

#include <bits/stdc++.h>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> point;
const int MAX = 55;
int parent[MAX];

istream& operator >> (istream& fin, point& o) {
	fin >> o.X >> o.Y;
	return fin;
}
ostream& operator << (ostream& fout, const point& o) {
	fout << o.X << ',' << o.Y;
	return fout;
}
inline point vec(const point& a, const point& b) {
	return point(b.X - a.X, b.Y - a.Y);
}
inline int sign(int c) {
	return c < 0 ? -1 : c > 0 ? 1 : 0;
}
inline int cross(const point& a, const point& b) {
	return a.X * b.Y - a.Y * b.X;
}

bool in(const point& p, const vector<point>& v) {
	int mx = -1, mn = 1;
	for (int i = 1, len = v.size(); i < len; ++i) {
		int s = sign(cross(vec(p, v[i - 1]), vec(p, v[i])));
		mx = max(mx, s);
		mn = min(mn, s);
	}
	return abs(mx - mn) < 2;
}

bool seg_intersect(point a, point b, point c, point d) {
	int sa = sign(cross(vec(c, d), vec(c, a)));
	int sb = sign(cross(vec(c, d), vec(c, b)));
	if (!sa && !sb) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !((a < c && b < c) || (d < a && d < b));
	}
	int sc = sign(cross(vec(a, b), vec(a, c)));
	int sd = sign(cross(vec(a, b), vec(a, d)));
	return sa * sb < 1 && sc * sd < 1;
}

int get_parent(int u) {
	if (u == parent[u])
		return u;
	return parent[u] = get_parent(parent[u]);
}

int main() {
	int n;
	while (cin >> n && n) {
		cin.ignore();
		vector<vector<point> > polys(n);
		for (int i = 0; i < n; ++i) {
			string str;
			getline(cin, str);
			stringstream ss(str);
			point p;
			while (ss >> p)
				polys[i].push_back(p);
			polys[i].push_back(polys[i][0]);
		}

		int zones = n;
		iota(parent, parent + n, 0);

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (get_parent(i) == get_parent(j))
					continue;
				
				bool flag = false;
				for (int k = 0, len = polys[j].size(); k < len; ++k)
					flag = flag || in(polys[j][k], polys[i]);

				for (int k1 = 1, len1 = polys[i].size(); k1 < len1; ++k1)
					for (int k2 = 1, len2 = polys[j].size(); k2 < len2; ++k2)
						flag = flag || seg_intersect(polys[i][k1 - 1], polys[i][k1], polys[j][k2 - 1], polys[j][k2]);

				if (flag) {
					parent[parent[i]] = parent[j];
					--zones;
				}
			}
		}
		cout << zones << endl;

	}
	return 0;
}
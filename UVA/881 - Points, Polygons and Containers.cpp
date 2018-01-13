/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 881 - Points, Polygons and Containers
	@link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=822
	@judge: UVA
	@idea: the polygons form a tree, so we have to create a proper adjacent list for the tree
		then check if the points are in the leaves first then check in the parents of the leaves and so on
		we can do that using dfs, check for the current node after calling the children dfs.
		* the point inclusion in polygon test could be done efficiently using winding numbers algorithm or
		ray casting.
		* I formed the tree here by sorting the polygons acording to polygon areas, then starting from the
		smallest polygon to the largest, find for each one his children in the smaller polygons that aren't
		reserved yet as another polygon children. This could be done also by sorting the polygons according
		to the size of the subtree of each polygon, or by iterativly pick the polygon with in-degree zero
		and updating the in-degree of all polygons affected after the pick.
*/

#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define X first
#define Y second
#define EPS 1e-9
using namespace std;
typedef long double myf;
typedef pair<myf, myf> point;

istream& operator >> (istream& fin, point& o) {
	fin >> o.X >> o.Y;
	return fin;
}
point operator - (const point& a, const point& b) {
	return point(a.X - b.X, a.Y - b.Y);
}

myf cross(const point& a, const point& b) {
	return a.X * b.Y - a.Y * b.X;
}

int in(const vector<point>& v, point p) {
	int wn = 0;
	for (int i = 0, len = v.size(); i < len; ++i) {
		int j = i == (len - 1) ? 0 : (i + 1);
		if (v[i].Y <= p.Y + EPS)
			wn += (v[j].Y > p.Y + EPS) && cross(v[j] - v[i], p - v[i]) > EPS;
		else
			wn -= (v[j].Y <= p.Y + EPS) && cross(v[j] - v[i], p - v[i]) < EPS;
	}
	return wn;
}

myf area(const vector<point>& v) {
	myf ret = 0;
	for (int i = 0, len = v.size(); i < len; ++i)
		ret += cross(v[i], v[(i + 1) % len]);
	return fabs(ret) * 0.5;
}

int n, m;
vector<int> realc, realp, ans;
vector<vector<int> > adj;
vector<vector<point> > polys;
vector<point> pnts;

void dfs(int cur) {
	for (int i = 0, len = adj[cur].size(); i < len; ++i)
		dfs(adj[cur][i]);
	for (int i = 0; i < m; ++i) 
		if (!ans[i] && in(polys[cur], pnts[i]))
			ans[i] = realc[cur];
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		realc.resize(n);
		polys.clear(); polys.resize(n);
		for (int i = 0; i < n; ++i) {
			cin >> realc[i];
			string str;
			getline(cin, str);
			stringstream ss(str);
			point p;
			while (ss >> p)
				polys[i].push_back(p);
		}

		cin >> m;
		realp.resize(m);
		pnts.resize(m);
		for (int i = 0; i < m; ++i)
			cin >> realp[i] >> pnts[i];

		vector<int> v(n), vis(n);	
		iota(all(v), 0);
		sort(all(v), [&] (int a, int b) {
			return area(polys[a]) < area(polys[b]) - EPS;
		});

		adj.clear(); adj.resize(n);
		for (int i = 0; i < n; ++i) {
			int u = v[i];
			for (int j = 0; j < i; ++j) if (!vis[j]) {
				int ch = v[j];
				for (auto& p : polys[ch]) if (in(polys[u], p)) {
					adj[u].push_back(ch);
					vis[j] = 1;
					break;
				}
			}
		}

		ans.clear(); ans.resize(m);
		dfs(v[n - 1]);

		v.resize(m);
		iota(all(v), 0);
		sort(all(v), [&] (int a, int b) {
			return realp[a] < realp[b];
		});

		for (int i = 0; i < m; ++i)
			cout << realp[v[i]] << ' ' << ans[v[i]] << endl;
		if (T)
			cout << endl;
	}
	return 0;
}
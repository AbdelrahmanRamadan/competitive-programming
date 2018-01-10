/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 3270 - Simplified GSM Network
	@link: https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=1271
	@judge: LIVEARCHIVE
	@idea: voronoi diagram is answering the question of "for each tower what's its convex domination region"
		So calculate voronoi diagram for towers then for each edge the number of handoffs (switching tower)that the
		cell makes while walking through that edge is equal to half the number of intersections between that edge segment
		and all voronoi polygons segments because whenever you enter or leave tower area you intersect with edge segment once for leaving
		the old tower region and once for entering the adjacent tower region.
*/

#include <bits/stdc++.h>
#define X real()
#define Y imag()
#define cross(A,B) ((A).X*(B).Y-(A).Y*(B).X)
#define VEC(a,b) ((b)-(a))
#define CCWPerp(v) (point(-(v).Y,(v).X))
#define MID(a,b) (((a)+(b))/2.0L)
#define EPS 1e-9
#define fi first
#define se second
using namespace std;
typedef long double myf;
typedef complex<myf> point;
const int inf = 1e9;
const myf PI = 4.0L * atan2l(1.0L, 1.0L);

bool operator < (const point& a, const point& b) {
	return a.X < b.X - EPS || (a.X - b.X < EPS && a.Y < b.Y - EPS);
}

istream& operator >> (istream& fin, point& o) {
	myf x, y;
	fin >> x >> y;
	o = point(x, y);
	return fin;
}

pair<point, int> llIntersect(const point& A0, const point& A1, const point& B0, const point& B1){
	myf s = cross(A0 - B0, A1 - A0) / cross(B1 - B0, A1 - A0);
	return pair<point, int> (B0 + (B1 - B0) * s, isnan(s) + isinf(s) * 2);
}

vector<point> polygonCut(const vector<point>& pnts, const point& A, const point& B){
	int sz = pnts.size();
	vector<point> ret;
	for(int i = 0; i < sz; ++i){
		int j = (i + 1) * (i < sz - 1);
		bool in1 = cross(VEC(A, B), VEC(A, pnts[i])) > EPS;
		bool in2 = cross(VEC(A, B), VEC(A, pnts[j])) > EPS;
		if(in1)
			ret.push_back(pnts[i]);
		if(in1 ^ in2){
			auto r = llIntersect(pnts[i], pnts[j], A, B);
			if(ret.empty() || !(ret.back() == r.fi))
				ret.push_back(r.fi);
		}
	}
	if(!ret.empty() && ret.back() == ret.front())
		ret.pop_back();
	return ret;
}

vector<vector<point> > voronoi(const vector<point> &pnts, const vector<point> &borders) {
	vector<vector<point> > res;
	int sz = pnts.size();
	for(int i = 0; i < sz; i++) {
		res.push_back(borders);
		for(int j = 0; j < sz; j++) {
			if(j == i) continue;
			point p = CCWPerp(VEC(pnts[i], pnts[j]));
			point m = MID(pnts[i], pnts[j]);
			res.back() = polygonCut(res.back(), m, m + p);
		}
	}
	return res;
}


bool seg_intersect(point a, point b, point c, point d) {
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);
	
	auto p = llIntersect(a, b, c, d);
	if (p.second == 2)
		return false;

	if(p.second == 1)
		return !((a < c && b < c) || (d < a && d < b));
	
	return !((p.first < a || b < p.first) || (p.first < c || d < p.first));
}

int main() {
	int t, c, r, q;
	int T = 0;
	while (cin >> t >> c >> r >> q && t) {
		vector<point> cities(c);
		vector<point> towers(t);
		for (int i = 0; i < t; ++i)
			cin >> towers[i];
		vector<point> borders({
			{ -1001, -1001 },
			{ 1001, -1001 },
			{ 1001, 1001 },
			{ -1001, 1001 },
		});
		vector<vector<point> > polys = voronoi(towers, borders);
		vector<pair<point, point> > segs;
		
		for (auto &v : polys) {
			for (int i = 0, len = v.size(); i < len; ++i) {
				int j = (i + 1) % len;
				segs.push_back({ v[i], v[j] });
			}
		}

		
		vector<vector<int> > adj(c, vector<int> (c, inf));
		for (int i = 0; i < c; ++i) {
			cin >> cities[i];
			adj[i][i] = 0;
		}
		for (int i = 0, u, v; i < r; ++i) {
			cin >> u >> v;
			--u, --v;
			int cnt = 0;
			for (auto seg : segs) {
				cnt += seg_intersect(cities[u], cities[v], seg.first, seg.second);
			}
			adj[u][v] = adj[v][u] = cnt / 2;
		}

		for (int k = 0; k < c; k++)
			for (int i = 0; i < c; i++)
				for (int j = 0; j < c; j++)
					adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

		cout << "Case " << ++T << ":" << endl;
		for (int i = 0, u, v; i < q; ++i) {
			cin >> u >> v;
			--u, --v;
			if (adj[u][v] < inf - 1)
				cout << adj[u][v] << endl;
			else
				cout << "Impossible" << endl;
		}
	}
	return 0;
}

/*input
2
15 14 4
0 9 7 7 10 7 16 11 20 12 24 11 25 9 24 4 25 2 31 1 38 3 41 11 44 15 49 17 51 17
0 19 3 20 8 19 11 19 15 21 21 23 25 23 26 20 26 18 34 19 37 21 42 23 47 24 51 24
4
5 11 9 11 7 15 4 14
3
17 14 16 16 19 17
3
28 15 33 13 30 17
6
31 5 27 7 29 12 31 8 35 9 34 6
2 2 0
0 0 1000 0
0 100 1000 100
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 10514 River Crossing
	@link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1455
	@judge: Uva
	@idea: calculating min path with Floyd-Warshall, and calculating the distance between two islands as
	the minimum distance between two edges
		implementation trick: treat the rever also as an island but don't connect the last point with the first
			instead connect the last one with the prev
*/

#include <bits/stdc++.h>
#define EPS 1e-9 
#define plDist(A,B,P) (fabsl(cross3(A,B,P)/(ppDist(A,B))))
#define cross(A,B) ((A).X*(B).Y-(A).Y*(B).X)
#define cross3(a,b,c) cross(VEC(a,b),VEC(a,c))
#define dot(A,B) ((A).X*(B).X+(A).Y*(B).Y)
#define dot3(a,b,c) dot(VEC(a,b),VEC(a,c))
#define X first
#define Y second
using namespace std;
typedef long double myf;
typedef pair<int, int> point;
const myf inf = 1e9;

myf ppDist(const point& a, const point& b) {
	return sqrt(1.0L * (a.X - b.X) * (a.X - b.X) + 1.0L * (a.Y - b.Y) * (a.Y - b.Y));
}

point VEC(const point& a, const point& b) {
	return point({ b.X - a.X, b.Y - a.Y });
}

myf psDist(const point& A, const point& B, const point& P){
	return dot3(A, B, P) < -EPS ? ppDist(A, P) : dot3(B, A, P) < -EPS ? ppDist(B, P) : plDist(A, B, P);
}

myf ssDist(const point& a, const point& b, const point& c, const point& d) {
	return min({ psDist(c, d, a), psDist(c, d, b), psDist(a, b, c), psDist(a, b, d) });
}

myf calc(vector<point>& s, vector<point>& e) {
	myf ret = inf;
	for (int i = 1; i < s.size(); ++i)
		for (int j = 1; j < e.size(); ++j) 
			ret = min(ret, ssDist(s[i], s[i - 1], e[j], e[j - 1]));
	return ret;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		int r1, r2, n;
		cin >> r1 >> r2 >> n;
		n += 2;
		vector<vector<point> > polys(n);
		vector<vector<myf> > dist(n, vector<myf> (n, inf));

		polys[0].resize(r1);
		polys[1].resize(r2);
		for (int i = 0; i < r1; ++i)
			cin >> polys[0][i].X >> polys[0][i].Y;
		for (int i = 0; i < r2; ++i)
			cin >> polys[1][i].X >> polys[1][i].Y;
		polys[0].push_back(polys[0][r1 - 2]);
		polys[1].push_back(polys[1][r2 - 2]);

		for (int i = 2; i < n; ++i) {
			int m;
			cin >> m;
			polys[i].resize(m);
			for (int j = 0; j < m; ++j)
				cin >> polys[i][j].X >> polys[i][j].Y;
			polys[i].push_back(polys[i][0]);
		}

		for (int i = 0; i < n; ++i) {
			dist[i][i] = 0;
			for (int j = i + 1; j < n; ++j) {
				dist[i][j] = dist[j][i] = calc(polys[i], polys[j]);
			}
		}
		
		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
		cout << setprecision(3) << fixed;
		cout << dist[0][1] << endl;
	}
	return 0;
}
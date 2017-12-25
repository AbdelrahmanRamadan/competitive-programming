/*input
7
-10 0
0 -10
10 0
0 10
-20 10
-10 20
-2 4
4
-10000 10000
10000 10000
10000 -10000
-10000 -9999
3
-1 0
0 0
1 0
0
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 12240 - Cocircular Points
	@link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3392
	@judge: UVA
	@idea: O(n^3*log(n^3))
		get circle center for each non-colinear 3 points then find common centers using map or hashing
*/

#include <bits/stdc++.h>
#define EPS 1e-9
#define fi first
#define se second
#define X real()
#define Y imag()
using namespace std;
typedef double myf;
typedef complex<myf> point;

const int MAX = 100;

point pnts[MAX];
int n;

struct cmp {
	bool operator () (const pair<point, myf>& a, const pair<point, myf>& b) {
		if (fabs(a.se - b.se) > EPS)
			return a.se < b.se;
		if (fabs(a.fi.X - b.fi.X) > EPS)
			return a.fi.X < b.fi.X;
		if (fabs(a.fi.Y - b.fi.Y) > EPS)
			return a.fi.Y < b.fi.Y;
		return false;
	}
};

inline point mid(const point& a, const point& b) {
	return (a + b) * 0.5;
}
inline point vec(const point& a, const point& b) {
	return b - a;
}
inline point perp(const point& v) {
	return point({ -v.Y, v.X });
}
inline myf cross(const point& a, const point& b) {
	return a.X * b.Y - a.Y * b.X;
}
inline myf dist(const point& v) {
	return sqrtl(v.X * v.X + v.Y * v.Y);
}

pair<point, myf> in(const point& A0, const point& A1, const point& B0, const point& B1) {
	myf s = cross(vec(B0, A0), vec(A0, A1)) / cross(vec(B0, B1), vec(A0, A1));
	return pair<point, myf> ({ vec(B0, B1) * s + B0, isnan(1.0L * s) + 2 * isinf(1.0L * s) });
}


int main() {

	while (cin >> n && n) {
		int ans = 1 + (n > 1);
		map<pair<point, myf>, bitset<101>, cmp> mp; 
		for (int i = 0; i < n; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			pnts[i] = point({ (myf)x, (myf)y });
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < i; ++j) {
				for (int k = 0; k < j; ++k) {
					point a = pnts[i], b = pnts[j], c = pnts[k];
					auto p = in(mid(a, b), perp(vec(a, b)) + mid(a, b), mid(a, c), perp(vec(a, c)) + mid(a, c));

					if (!p.second) {
						auto& s = mp[{ p.first, dist(vec(p.first, a)) }];
						s.set(i);
						s.set(j);
						s.set(k);
					}
				}
			}
		}

		for (auto& p : mp)
			ans = max<int>(ans, p.se.count());
		printf("%d\n", ans);
	}
	return 0;
}
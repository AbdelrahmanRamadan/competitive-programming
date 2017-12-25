/*input
3
0 40 200 40
40 0 40 200
0 200 200 0
4
0 30 230 30
0 200 230 200
30 0 30 230
200 0 200 230
3
0 1 121 1
0 0 121 4
0 4 121 0
0
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 3000 - Tree-Lined Streets
	@link: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=38&page=show_problem&problem=1001
	@judge: LIVE ARCHIVE
	@idea: cut each segment with other segments then calculate the answer for each segment individually by
		dividing each length over 50 and take the ceil after subtracting 25 of each end if it comes from an intersection
*/

#include <bits/stdc++.h>
#define X real()
#define Y imag()
#define EPS 1e-9
using namespace std;
typedef long double myf;
typedef complex<myf> point;
const int MAX = 110;
int n;
point pnts[MAX][2];

inline myf cross(const point& A, const point& B) {
	return A.X * B.Y - B.X * A.Y;
}

inline point vec(point a, point b) {
	return b - a;
}

inline myf dist(point a) {
	return sqrtl(a.X * a.X + a.Y * a.Y);
}

bool operator < (const point& a, const point& b) {
	return a.X + EPS < b.X || (a.X - b.X < EPS && a.Y + EPS < b.Y);
}

pair<point, int> in(point a0, point a1, point b0, point b1) {
	myf s = cross(vec(b0, a0), vec(a0, a1)) / cross(vec(b0, b1), vec(a0, a1));
	return { vec(b0, b1) * s + b0, isnan(s) + isinf(s) * 2 };
}

pair<point, bool> seg_intersect(point a, point b, point c, point d) {
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);
	
	auto p = in(a, b, c, d);
	if (p.second == 2)
		return { p.first, false };

	if(p.second == 1)
		return { p.first, !((a < c && b < c) || (d < a && d < b)) };
	
	return { p.first, !((p.first < a || b < p.first) || (p.first < c || d < p.first)) };
}

bool cmp (const point& a, const point& b) {
	return a.X + EPS < b.X || (a.X - b.X < EPS && a.Y + EPS < b.Y);
}

istream& operator >> (istream& fin, point& o) {
	int x, y;
	fin >> x >> y;
	o = point(x, y);
	return fin;
}


int main() {
	int T = 0;
	while (cin >> n && n) {
		int ans = 0;
		for (int i = 0; i < n; ++i)
			cin >> pnts[i][0] >> pnts[i][1];
		for (int i = 0; i < n; ++i) {
			vector<point> v;
			v.push_back(pnts[i][0]);
			v.push_back(pnts[i][1]);
			for (int j = 0; j < n; ++j) {
				if (i == j)
					continue;
				auto p = seg_intersect(pnts[i][0], pnts[i][1], pnts[j][0], pnts[j][1]);
				if (p.second)
					v.push_back(p.first);
			}
			sort(v.begin(), v.end(), cmp);
			for (int i = 1, len = v.size(); i < len; ++i) {
				ans += max<int>(0, ceil((dist(vec(v[i - 1], v[i])) - (i != len - 1) * 25 - (i != 1) * 25) / 50.0L + EPS));
			}
		}
		cout << "Map " << ++T << endl;
		cout << "Trees = " << ans << endl;
	}
	return 0;
}
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: SRM373 Div.2 1000 Rectangle Crossings
	@link:
	@judge: Topcoder
	@idea: bruteforce, try to intersect all segments with each rectangle
*/

#include <bits/stdc++.h>
#define fi first
#define se second
#define X real()
#define Y imag()
#define EPS 1e-9
using namespace std;
typedef long double myf;
typedef complex<myf> point;
typedef pair<point, point> segment;

bool operator < (const point& A, const point& B){
	return A.X < B.X - EPS || (A.X - B.X < EPS && A.Y < B.Y - EPS);
}

istream& operator >> (istream& fin, point& o) {
	myf x, y;
	fin >> x >> y;
	o = point(x, y);
	return fin;
}

point operator - (const point& A, const point& B) {
	return point(A.X - B.X, A.Y - B.Y);
}

myf cross(const point& A, const point& B) {
	return A.X * B.Y - A.Y * B.X;
}

class RectangleCrossings {
public:

	pair<point, int> llIntersect(const point& A0, const point& A1, const point& B0, const point& B1){
		myf s = cross(A0 - B0, A1 - A0) / cross(B1 - B0, A1 - A0);
		return pair<point, int> (B0 + (B1 - B0) * s, isnan(s) + isinf(s) * 2);
	}

	bool in(point a, point b, point c, point d) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		
		auto p = llIntersect(a, b, c, d);
		if (p.second == 2)
			return false;

		if(p.second == 1)
			return !((a < c && b < c) || (d < a && d < b));
		
		return !((p.first < a || b < p.first) || (p.first < c || d < p.first));
	}

	bool inside(const segment& r, const point& p, bool f = false) {
		if (p.X >= r.fi.X - EPS && p.X <= r.se.X + EPS && p.Y >= r.fi.Y - EPS && p.Y <= r.se.Y + EPS
			&& (f || (fabs(p.X - r.fi.X) > EPS && fabs(p.X - r.se.X) > EPS && fabs(p.Y - r.fi.Y) > EPS && fabs(p.Y - r.se.Y) > EPS)))
			return true;
		return false;
	}
	segment parse(const string& str) {
		stringstream ss(str);
		segment ret;
		ss >> ret.fi >> ret.se;
		if (ret.se < ret.fi)
			swap(ret.fi, ret.se);
		return ret;
	}
	vector <int> countAreas(vector <string> rects, vector <string> segs) {
		int n = rects.size(), m = segs.size();
		vector<int> ans(2);

		for (int i = 0; i < n; ++i) {
			segment r = parse(rects[i]);
			bool f1 = false, f2 = false;
			for (int j = 0; j < m; ++j) {
				segment s = parse(segs[j]);
				f1 = f1 || inside(r, s.fi) || inside(r, s.se);
				f2 = f1 || f2
					|| in(r.fi, point(r.fi.X, r.se.Y), s.fi, s.se)	
					|| in(r.fi, point(r.se.X, r.fi.Y), s.fi, s.se)	
					|| in(point(r.se.X, r.fi.Y), r.se, s.fi, s.se)	
					|| in(point(r.fi.X, r.se.Y), r.se, s.fi, s.se);
			}
			if (f1 || f2)
				ans[!f1] += (r.se.X - r.fi.X) * (r.se.Y - r.fi.Y);
		}
		return ans;
	}

};

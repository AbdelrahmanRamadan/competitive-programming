/*input

*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem:
	@link:
	@judge:
	@idea:
*/

#include <bits/stdc++.h>
#define EPS 1e-9
#define X real()
#define Y imag()
#define rotate(v,theta) ((v)*polar(1.0L,theta))
#define polar(len,theta) (point(cosl(theta),sinl(theta))*(len))
using namespace std;
typedef long double myf;
typedef complex<myf> point;
const myf OO = 1e17;

inline myf cross(const point& A, const point& B) {
	return A.X * B.Y - B.X * A.Y;
}

inline point vec(point a, point b) {
	return b - a;
}

inline myf dist(point a) {
	return sqrtl(a.X * a.X + a.Y * a.Y);
}

inline point unit(point a) {
	return a / dist(a);
}

bool operator < (const point& a, const point& b) {
	return a.X + EPS < b.X || (a.X - b.X < EPS && a.Y + EPS < b.Y);
}

bool operator == (const point& a, const point& b) {
	return fabs(a.X - b.X) < EPS && fabs(a.Y - b.Y) < EPS;
}

bool point_in_convex(const vector<point>& pnts, const point& p) {
	point c = pnts[0];
	for (point& i : pnts)
		c = min(c, i);
	int a = upper_bound(pnts.begin(), pnts.end());
}

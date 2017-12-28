/*input
10 10
20
5 12
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: GEOM - Geometry and a Square
	@link: http://www.spoj.com/problems/GEOM/
	@judge: SPOJ
	@idea: simple line line intersection
		special cases: when multiple lines overlap you have to treat them like a single line.
		implementation: get any intersection point and check if it belongs to all lines
						if there's no intersection point (all lines overlap - zero side length case) then
						print any point on the line
*/

#include <bits/stdc++.h>
#define X real()
#define Y imag()
#define EPS 1e-9
using namespace std;
typedef long double myf;
typedef complex<myf> point;


istream& operator >> (istream& fin, point& o) {
	myf x, y;
	fin >> x >> y;
	o = point({ x, y });
	return fin;
}

inline point vec(const point& a, const point& b) {
	return b - a;
}

inline myf cross(const point& a, const point& b) {
	return a.X * b.Y - a.Y * b.X;
}

point perp(const point& v) {
	return point({ -v.Y, v.X });
}

pair<point, myf> in(point A0, point A1, point B0, point B1) {
	myf s = cross(vec(B0, A0), vec(A0, A1)) / cross(vec(B0, B1), vec(A0, A1));
	return { s * vec(B0, B1) + B0, isnan(s) + 2 * isinf(s) };
}

int main() {
	point cen, v0[5], v1[4], p;
	cin >> cen;
	myf s;
	cin >> s >> p;
	cout << setprecision(1) << fixed;

	v0[0] = cen + point({ -s / 2, s / 2 });
	v0[1] = cen + point({ s / 2, s / 2 });
	v0[2] = cen + point({ s / 2, -s / 2 });
	v0[3] = cen + point({ -s / 2, -s / 2 });
	v0[4] = v0[0];

	for (int i = 0; i < 4; ++ i)
		v1[i] = perp(vec(v0[i + 1], p)) + v0[i];

	point ans = v0[0];
	for (int i = 0; i < 4; ++i) {
		for (int j = i + 1; j < 4; ++j) {
			auto temp = in (v0[i], v1[i], v0[j], v1[j]);
			if (!temp.second)
				ans = temp.first;
		}
	}

	for (int i = 0; i < 4; ++i)
		if (cross(vec(ans, v0[i]), vec(ans, v1[i])) > EPS)
			return cout << "NO" << endl, 0;

	cout << "YES" << endl;
	cout << ans.X << ' ' << ans.Y << endl;
	return 0;
}
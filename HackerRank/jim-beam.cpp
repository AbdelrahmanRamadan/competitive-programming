/*input
5
1 2 2 1 2 2
-1 1 1 1 1 -1
1 1 2 2 3 3
2 2 3 3 1 1
0 1 1 1 0 2
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: Jim Beam
	@link: https://www.hackerrank.com/challenges/jim-beam/problem
	@judge: Hackerrank
	@idea: check if two segments intersect
*/

#include <bits/stdc++.h>
#define EPS 1e-9
#define X real()
#define Y imag() 
using namespace std;
typedef long double myf;
typedef complex<myf> point;

inline myf cross(const point& A, const point& B) {
	return A.X * B.Y - B.X * A.Y;
}

inline point vec(point a, point b) {
	return b - a;
}

pair<point, int> in(point a0, point a1, point b0, point b1) {
	myf s = cross(vec(b0, a0), vec(a0, a1)) / cross(vec(b0, b1), vec(a0, a1));
	return { vec(b0, b1) * s + b0, isnan(s) + isinf(s) * 2 };
}
bool operator < (const point& a, const point& b) {
	return a.X + EPS < b.X || (a.X - b.X < EPS && a.Y + EPS < b.Y);
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

istream& operator >> (istream& fin, point& o) {
	int x, y;
	fin >> x >> y;
	o = point(x, y);
	return fin;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		point a, b, c, d{ 0, 0 };
		cin >> a >> b >> c;
		cout << (seg_intersect(a, b, c, d) ? "NO" : "YES") << endl;
	} 
}

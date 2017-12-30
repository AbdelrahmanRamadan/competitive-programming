/*input
8
-2 -2
-5 1
-2 4
1 3
-2 0
-3 1
-2 2
1 1
3
-2 1
0 0
1 2
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 1599 Winding Numbers
	@link: http://acm.timus.ru/problem.aspx?space=1&num=1599
	@judge: Timus
	@idea: number of full ccw turns around point is the same as the winding numbers used to check if a point is included
		in a general (not neccesarly simple) polygon or not 
*/

#include <bits/stdc++.h>
using namespace std;

struct point {
	int X, Y;
	point operator - (const point & o) const {
		return point({ X - o.X, Y - o.Y });
	} 
};
int n, q;

long long cross(const point& a, const point& b) {
	return 1LL * a.X * b.Y - 1LL * a.Y * b.X; 
}

long long dot(const point  & a, const point& b) {
	return 1LL * a.X * b.X + 1LL * a.Y * b.Y;
}

int winding(const vector<point>& v, point p) {
	int wn = 0;
	for (int i = 0, len = v.size(); i < len; ++i) {
		int j = i == (len - 1) ? 0 : (i + 1);
		if (v[i].Y <= p.Y)
			wn += (v[j].Y > p.Y) && cross(v[j] - v[i], p - v[i]) > 0;
		else
			wn -= (v[j].Y <= p.Y) && cross(v[j] - v[i], p - v[i]) < 0;
	}
	return wn;
}

int main() {
	scanf("%d", &n);
	vector<point> v(n);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", &v[i].X, &v[i].Y);
	
	scanf("%d", &q);
	while (q--) {
		point p;
		scanf("%d%d", &p.X, &p.Y);
		bool edge = false;
		for (int i = 0; i < n; ++i) {
			int j = i == (n - 1) ? 0 : (i + 1);
			edge |= !cross(v[i] - p, v[j] - p) && dot(p - v[i], v[j] - v[i]) >= 0 && dot(p - v[j], v[i] - v[j]) >= 0;
		}

		if (edge)
			puts("EDGE");
		else
			printf("%d\n", winding(v, p));
	}
	return 0;
}
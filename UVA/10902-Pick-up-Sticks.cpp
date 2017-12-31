/*input
5
1 1 4 2
2 3 3 1
1 -2.0 8 4
1 4 8 2
3 3 6 -2.0
3
0 0 1 1
1 0 2 1
2 0 3 1
0
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 10902 - Pick-up Sticks
	@link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1843
	@judge: UVA
	@idea: brute force, you'll always have at most 1000 sticks on the top so whenever a new stick gets thrown
		check if it intersects any old top stick, if so remove the old one
	@comments: very ambiguous statement it's not clear if it's in the end there'll be no more that 1000 sticks on the top or at any moment
*/

#include <bits/stdc++.h>
#define EPS 1e-9
#define X real()
#define Y imag()
using namespace std;
typedef double myf;
typedef complex<myf> point;
const int MAX = 100100;
point a[MAX], b[MAX];
int n, sz, s[MAX];

bool operator < (const point& a, const point& b) {
	return a.X + EPS < b.X || (fabsl(a.X - b.X) < EPS && a.Y + EPS < b.Y);
}

inline myf cross(const point& a, const point& b) {
	return a.X * b.Y - a.Y * b.X;
}

pair<point, int> llIntersect(const point& A0, const point& A1, const point& B0, const point& B1){
	myf s = cross(A0 - B0, A1 - A0) / cross(B1 - B0, A1 - A0);
	return pair<point, int> (B0 + (B1 - B0) * s, isnan((long double)s) + isinf((long double)s) * 2);
	// 1 -> overlapping, 2 -> parallel
}

bool seg_intersect(point a, point b, point c, point d) {
	auto p = llIntersect(a, b, c, d);
	if (p.second == 2)
		return false;

	if(p.second == 1)
		return !((a < c && b < c) || (d < a && d < b));
	
	return !((p.first < a || b < p.first) || (p.first < c || d < p.first));
}

int main() {
	while (~scanf("%d", &n) && n) {
		sz = 0;
		for (int i = 1; i <= n; ++i) {
			myf x1, y1, x2, y2;
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			a[i] = point({ x1, y1 });
			b[i] = point({ x2, y2 });
			if (b[i] < a[i])
				swap(a[i], b[i]);
			int k = 0;
			for (int j = 0; j < sz; ++j) {
				if (!seg_intersect(a[s[j]], b[s[j]], a[i], b[i]))
					s[k++] = s[j];
			}
			sz = k;
			s[sz++] = i;
		}
		printf("Top sticks:");
		for (int i = 0; i < sz; ++i)
			printf(" %d%c", s[i], i == sz - 1 ? '.' : ',');
		puts("");
	}
	return 0;
}
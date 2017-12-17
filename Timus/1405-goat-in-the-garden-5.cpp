/*input
8
1 1
-2 0
5 3
-2 3
8 3.10
-2 -1
-2 2
8 4.10
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 1405. Goat in the Garden 5
	@link: http://acm.timus.ru/problem.aspx?space=1&num=1405
	@judge: TIMUS
	@idea: bruteforce, precompute the nearest tree for each tree, then try all possible pairs, to get the maximum
		area try to maximize the largest radius for each tree, even if you minimized the other tree radius 
*/

#include <bits/stdc++.h>
#define EPS 1e-9
#define X real()
#define Y imag()
using namespace std;

typedef long double myf;
typedef complex<myf> point;

const int MAX = 1010;
const myf inf = 1e9;
const myf PI = acos(-1);
point pnts[MAX];
myf dist[MAX];

istream& operator >> (istream& fin, point& o) {
	myf x, y;
	fin >> x >> y;
	o = point(x, y);
	return fin;
}

myf ppdist(point a, point b) {
	return sqrtl((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y));
}

int main() {
	int n;
	cin >> n;
	fill(dist, dist + n, inf);
	for (int i = 0; i < n; ++i) {
		cin >> pnts[i];
		for (int j = 0; j < i; ++j) {
			myf d = ppdist(pnts[i], pnts[j]);
			dist[i] = min({ 50.0L, dist[i], d });
			dist[j] = min({ 50.0L, dist[j], d });
		}
	}
	
	myf ans = 0;

	for (int i = 0; i < n; ++i) {
		if (dist[i] < 1 - EPS)
			continue;
		for (int j = 0; j < n; ++j) {
			if (dist[j] < 1 - EPS)
				continue;
			
			myf d1 = dist[i];
			myf d2 = dist[j];
			myf pp = ppdist(pnts[i], pnts[j]);

			if (d1 < d2) swap(d1, d2);
			d2 = min(d2, pp - d1);
			if (d2 + EPS < 1) {
				d1 -= 1 - d2;
				d2 = 1;
			}
			ans = max(ans, d1 * d1 * PI + d2 * d2 * PI);			
		}
	}

	cout << setprecision(4) << fixed;
	cout << ans << endl;
	return 0;
}

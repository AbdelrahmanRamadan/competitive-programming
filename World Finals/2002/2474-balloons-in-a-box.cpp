/*input
6
0 0 0
10 10 10
1 1 1
2 2 2
4 4 6
8 5 9
9 2 4
6 8 6
4
0 0 0
10 10 10
4 4 6
8 5 9
9 2 4
6 8 6
1
10 10 10
0 0 0
5 5 5
0
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 2474 Balloons in a box
	@link: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=475
	@judge: LIVEARCHIVE
	@idea: bruteforce - try all possible permutations to put the ballons in the box
*/
#include <bits/stdc++.h>
using namespace std;
typedef long double myf;
const myf PI = acos(-1);
struct point {
	long long x, y, z;
	point operator - (const point& o) const {
		return point({ x - o.x, y - o.y, z - o.z });
	}
	myf len() const {
		return sqrtl(1.0L * x * x + 1.0L * y * y + 1.0L * z * z);
	}
	bool operator < (const point& o) const {
		return x < o.x || (x == o.x && y < o.y) || (x == o.x && y == o.y && z < o.z);
	}
} p[10];

int main() {
	int n, T = 0;
	while (cin >> n && n) {
		point ci, c;
		cin >> ci.x >> ci.y >> ci.z;
		cin >> c.x >> c.y >> c.z;
		if (ci.x > c.x)
			swap(ci.x, c.x);
		if (ci.y > c.y)
			swap(ci.y, c.y);
		if (ci.z > c.z)
			swap(ci.z, c.z);
		c = c - ci;

		for (int i = 0; i < n; ++i) {
			cin >> p[i].x >> p[i].y >> p[i].z;
			p[i] = p[i] - ci;
		}

		myf ans = 1.0L * c.x * c.y * c.z;
		sort(p, p + n);
		int cnt = 0;
		do {
			myf tot = 1.0L * c.x * c.y * c.z; 
			vector<myf> r(n, 0);
			for (int i = 0; i < n; ++i) {
				r[i] = min({ p[i].x, c.x - p[i].x, p[i].y, c.y - p[i].y, p[i].z, c.z - p[i].z });
				for (int j = 0; j < i; ++j)
					r[i] = min(r[i], (p[i] - p[j]).len() - r[j]);
				r[i] = max(0.0L, r[i]);

				tot -= 4.0L/3.0L * PI * r[i] * r[i] * r[i];
			}
			ans = min(tot, ans);
		} while (next_permutation(p, p + n));
		cout << setprecision(0) << fixed;
		cout << "Box " << ++T << ": " << ans << endl << endl;
	}
	return 0;
}
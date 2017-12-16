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
	@problem:
	@link:
	@judge:
	@idea:
*/

#include <bits/stdc++.h>
using namespace std;
struct point {
	int x, y;
} p[4];

bool orientation(point a, point b, point c) {
	return 1LL * (b.x - a.x) * (c.y - a.y) - 1LL * (b.y - a.y) * (c.x - a.x) < 0;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		for (int i = 0; i < 3; ++i)
			cin >> p[i].x >> p[i].y;

		bool flag = true;
		for (int i = 0; i < 4; i += 2) 
			flag &= orientation(p[i], p[i + 1], p[(i + 2) % 4])
				!= orientation(p[i], p[i + 1], p[(i + 3) % 4]);

		cout << (flag ? "NO" : "YES") << endl;
	}
	return 0;
}
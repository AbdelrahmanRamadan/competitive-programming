/*input
6 5
1 2
1 4
2 3
2 2
2 4
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

int main() {
	int n, m;
	cin >> n >> m;
	int rot = 0;
	bool flip = 1;
	while (m--) {
		int type, k;
		cin >> type >> k;
		rot = (rot + k) % n;
		if (type == 2) {
			flip ^= 1;
		}
	}
	if (flip)
		cout << 2 << ' ' << rot << endl;
	else
		cout << 1 << ' ' << n - rot << endl;
	return 0;
}
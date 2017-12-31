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
	@problem: Xrange's Pancakes
	@link: https://www.hackerrank.com/challenges/xrange-and-pizza/problem
	@judge: HackerRank
	@idea: fix the position of the first vertex (variable rot) starting with zero
		* when performing rotation add the rotation amount to rot: rot = (rot + k) % n
		* when performing reflection add the amount that our fixed vertex moved by after
			the reflection: rot = (rot + (k - rot * 2)) % n
		this amount comes from the fact that the vertext travels double the distance between it and the reflection axis

*/

#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	int rot = 0;
    int is_ref = 0;
	while (m--) {
		int type, k;
		cin >> type >> k;
		if (type == 1) {
			rot = (rot + k) % n;
		} else {
            rot = (rot + (k - rot * 2) + n) % n;
			is_ref ^= 1;
		}
	}
	if (is_ref)
		cout << 2 << ' ' << rot << endl;
	else
		cout << 1 << ' ' << (n - rot) % n << endl;
	return 0;
}
/*input
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: C. Component Tree
	@link: http://codeforces.com/gym/100513/problem/C
	@judge: Codeforces Gym
	@idea:
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(NULL));
	int T = 40;
	while (T--) {
		int n = abs(rand()) % 10 + 1;
		cout << n << endl;
		vector<vector<bool> > vis(n + 1, vector<bool> (n + 1, false));
		for (int i = 0; i < n; ++i) {
			int r = abs(rand()) % n + 1;
			int c = abs(rand()) % n + 1;
			if (vis[r][c]) {
				--i;
				continue;
			}
			vis[r][c] = true;
			cout << r << ' ' << c << ' ';
		}
		cout << endl;
	}
	cout << 0 << endl;
	return 0;
}
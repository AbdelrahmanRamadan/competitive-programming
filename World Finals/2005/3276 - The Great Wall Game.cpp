/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 3276 - The Great Wall Game
	@link: https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=1277
	@judge: LIVEARCHIVE
	@idea: first notice that if we know the final position of each stone there'll always be some order
		of movements to get them to these final positions without intersecting with any other stone
		so we can now neglect this rule "any single stone can move into an unoccupied location".
		Now try all possible horizontal, vertical and diagonal walls and get the best total cost of moving the
		stones to each wall using dynamic programming on bit masks.
		DP state will be a mask representing the stones (in input order) that already went to the first x positions
		in the wall, where x is the number of 1 bits in the mask. to calculate the answer for new state, iterate over
		all possible stones to put them in the x's position in the wall.
		* Note: used direction arrays to represent all possible walls that can be formed instead of hard code dp calls
		for each wall.
*/

#include <bits/stdc++.h>
using namespace std;
const int MAX = 50;
const int inf = 1e5;
int n, row[MAX], col[MAX];
int dr[MAX], dc[MAX], sr[MAX], sc[MAX];
int main() {
	int T = 0;
	while (cin >> n && n) {
		for (int i = 0; i < n; ++i) {
			cin >> row[i] >> col[i];
			--row[i], --col[i];
		}
		for (int i = 0; i < n; ++i) {
			sr[i] = i;
			dc[i] = 1;
			sc[n + i] = i;
			dr[n + i] = 1;
			sc[i] = dr[i] = sr[n + i] = dc[n + i] = 0;
		}
		dr[n + n] = dc[n + n] = 1;
		dr[n + n + 1] = 1;
		dc[n + n + 1] = -1;
		sc[n + n + 1] = n - 1;
		sr[n + n + 1] = sr[n + n] = sc[n + n] = 0;

		int sz = n + n + 2, ans = inf;
		for (int i = 0; i < sz; ++i) {
			int lim = 1 << n;
			vector<int> dp(lim);
			for (int mask = 1; mask < lim; ++mask) {
				int d = __builtin_popcount(mask) - 1;
				int r = sr[i] + dr[i] * d;
				int c = sc[i] + dc[i] * d;
				dp[mask] = inf;
				for (int j = 0; j < n; ++j)
					if ((mask >> j) & 1)
						dp[mask] = min(dp[mask], dp[mask - (1 << j)] + abs(r - row[j]) + abs(c - col[j]));
			}
			ans = min(ans, dp[(1 << n) - 1]);
		}
		cout << "Board " << ++T << ": "<< ans << " moves required." << endl;
		cout << endl;
	}
	return 0;
}

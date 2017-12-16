/*input
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: CF900-D2-E
	@link: http://codeforces.com/problemset/problem/900/E
	@judge: Codeforces
	@idea: dynamic programming with pre-compution
*/
#include <bits/stdc++.h>
#define debug(x) #x<<" = "<<x
using namespace std;

const int MAX = 100100;
int n, m, match[MAX][2], cnt[MAX][2];
char str[MAX];
pair<int, int> dp[MAX];

void add(int i, bool c) {
	match[i][c] = match[i - 1][!c] + 1;
	cnt[i][c] = cnt[i - 1][!c] + (str[i] == '?');
	if (match[i][c] > m) {
		--match[i][c];
		cnt[i][c] -= (str[i - m] == '?');
	}
}

int main() {
	cin >> n >> (str + 1) >> m;
	str[0] = '?';
	bool c = !(m & 1);
	for (int i = 1; i <= n; ++i) {
		if (str[i] == 'a' || str[i] == '?')
			add(i, 0);
		if (str[i] == 'b' || str[i] == '?')
			add(i, 1);
		dp[i] = dp[i - 1];
		if (match[i][c] == m)
			dp[i] = max(dp[i], { dp[i - m].first + 1, dp[i - m].second - cnt[i][c] });
	}

	cout << -dp[n].second << endl;
	return 0;
}

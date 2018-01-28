/*input
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
const int inf = 1e9;
int n, m;
int L[20][200], mem[20][200];
bool vis[20][200];
int dp(int idx, int rem) {
	if (rem < 0)
		return -inf;
	if (idx == n)
		return 0;
	if (vis[idx][rem])
		return mem[idx][rem];
	
	mem[idx][rem] = -inf;
	for (int i = 1; i <= m; ++i)
		if (L[idx][i] >= 5)
			mem[idx][rem] = max(mem[idx][rem], L[idx][i] + dp(idx + 1, rem - i));

	vis[idx][rem] = true;
	
	return mem[idx][rem];
}
int main() {
	int T;
	cin >> T;
	while (T--) {
		memset(vis, 0, sizeof vis);
		cin >> n >> m;
		for (int i = 0; i < n; ++i)
			for (int j = 1; j <= m; ++j)
				cin >> L[i][j];
		int ans = dp(0, m);
		cout << setprecision(2) << fixed;
		if (ans < 0)
			cout << "Peter, you shouldn't have played billiard that much." << endl;
		else
			cout << "Maximal possible average mark - " << round((long double)ans * 100 / n) / 100 << "." << endl;
	}	
	return 0;
}
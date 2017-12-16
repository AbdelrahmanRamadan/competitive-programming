/*input
1
1
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: CF900-D2-C
	@link: http://codeforces.com/problemset/problem/900/C
	@judge: Codeforces
	@idea: ad-hoc
*/
#include <bits/stdc++.h>
using namespace std;
const int MAX = 100100;
int cnt[MAX];
int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	set<int> s;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		auto it = s.insert(x).first;
		if (++it == s.end())
			--cnt[x];
		else if (next(it) == s.end())
			++cnt[*it];
	}
	int mx = -1, ans = 1;
	for (int i = 1; i <= n; ++i) {
		if (cnt[i] > mx) {
			mx = cnt[i];
			ans = i;
		}
	}
	cout << ans << endl;
	return 0;
}
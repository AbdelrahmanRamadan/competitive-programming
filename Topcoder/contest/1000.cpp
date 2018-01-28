/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: SRM 728 Div.1 500 - Increasing Sequences
	@judge: Topcoder
*/
#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 998244353;
const int MAX = 660;

ll inv[MAX];

class IncreasingSequences {
public:
	
	int count(vector <int> L, vector <int> R) {
		int n = L.size();
		vector<int> v;
		for (int i : L) v.push_back(i);
		for (int i : R) v.push_back(i + 1);

		sort(all(v));
		v.resize(unique(all(v)) - v.begin());
		int m = v.size() - 1;

		L.insert(L.begin(), 0);
		R.insert(R.begin(), 0);
		v.insert(v.begin(), 0);
		
		vector<vector<ll> > dp(n + 1, vector<ll> (m + 1));
		for (ll &i : dp[0]) i = 1;
		inv[1] = 1;
		for (int i = 2; i < MAX; ++i)
			inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				int len = v[j + 1] - v[j];
				ll comp = 1;
				int k = -1;
				do {
					++k;
					dp[i][j] = (dp[i][j] + dp[i - k][j - 1] * comp) % MOD;
					comp = comp * inv[k + 1] % MOD * (len - k) % MOD;
				} while (v[j] >= L[i - k] && v[j] <= R[i - k]);
			}
		}

		return dp[n][m];
	}
};

int main() {
	IncreasingSequences test;
	cout << test.count( {1, 1},
{1000000000, 1000000000}) << endl;
	// cout << test.count( {5, 5, 3, 8, 2},
	// 					{7, 9, 12, 10, 11}) << endl;
	return 0;
}
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long double myf;
typedef pair<int, int> pii;



class IncreasingSequencesEasy {
public:
	static const int MOD = 998244353;
	static const int MAX = 1e4 + 10;
	int count(vector <int> L, vector <int> R) {
		int n = L.size();
		vector<vector<int> > dp(n, vector<int> (MAX));
		for (int j = L[0]; j < MAX; ++j)
			dp[0][j] = dp[0][j - 1] + (j <= R[0]);

		for (int i = 1; i < n; ++i) {
			for (int j = L[i]; j <= R[i]; ++j) {
				dp[i][j] = dp[i - 1][j - 1];
			}

			for (int j = 1; j < MAX; ++j) {
				dp[i][j] += dp[i][j - 1];
				if (dp[i][j] >= MOD)
					dp[i][j] -= MOD;
			}
		}
		return dp[n - 1][MAX - 1];
	}
};

int main() {
	IncreasingSequencesEasy test;
	cout << test.count({1, 3, 1, 4}
					 , {6, 5, 4, 6}) << endl;
	return 0;
}
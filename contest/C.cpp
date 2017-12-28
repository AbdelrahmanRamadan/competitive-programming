/*input
4
s
f
f
s
*/
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long double myf;
typedef pair<int, int> pii;

const int MAX = 5050;
const int MOD = 1000000007;

char arr[MAX];
int dp[MAX][MAX], n;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf(" %c", &arr[i]);
	}

	if (arr[n - 1] == 'f')
		return cout << 0 << endl, 0;

	dp[n][0] = 1;
	for (int i = 1; i <= n + 1; ++i)
		dp[n][i] = 1;

	for (int i = n - 1; ~i; --i) {
		for (int j = 0; j <= n; ++j) {
			if (arr[i] == 'f') {
				dp[i][j] = (dp[i + 1][j + 1] + MOD - dp[i + 1][j]) % MOD;
			} else {
				dp[i][j] = dp[i + 1][j];
			}
			if (j)
				dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
		}
	}

	cout << dp[0][0] << endl;
	return 0;
}
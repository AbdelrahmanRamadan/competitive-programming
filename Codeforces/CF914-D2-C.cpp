/*input
111111011
2

*/
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long double myf;
typedef pair<int, int> pii;

const int MAX = 1010;
const int MOD = 1000000007;

string str;
int cnt[MAX], mem[MAX][MAX][2], k, n;
int main() {
	cin >> str >> k;
	if (k == 0)
		return cout << 1 << endl, 0;
	n = str.size();
	for (int i = 1; i <= n; ++i) {
		int temp = i;
		cnt[i] = 1;
		while (temp > 1) {
			++cnt[i];
			temp = __builtin_popcount(temp);
		}
	}
	cnt[0] = -1;

	for (int i = 0; i <= n; ++i)
		mem[n][i][0] = mem[n][i][1] = (cnt[i] == k);
	
	for (int i = n - 1; i >= 0; --i) {
		for (int j = 0; j <= n; ++j) {
			for (int f = 0; f < 2; ++f) {
				int &ret = mem[i][j][f];
				ret = mem[i + 1][j][f | (str[i] == '1')];
				if (f || str[i] == '1')
					ret += mem[i + 1][j + 1][f];
				if (ret >= MOD)
					ret -= MOD;
			}
		}
	}
	int ans = mem[0][0][0];
	if (k == 1) {
		ans += MOD - 1;
		if (ans >= MOD)
			ans -= MOD;
	}
	cout << ans << endl;
	return 0;
}
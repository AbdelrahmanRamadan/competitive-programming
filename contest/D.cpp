/*input
sasasasas
*/
/*

*/
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long double myf;
typedef pair<int, int> pii;

const int MAX = 1000100;
int cnt[2][MAX];
char col[2][MAX];
char str[MAX];

int main() {
	scanf("%s", str);
	int idx = 0;
	++cnt[0][idx], col[0][idx] = str[0];
	for (int i = 1; str[i]; ++i) {
		if (str[i] != col[0][idx])
			col[0][++idx] = str[i];
		++cnt[0][idx];
	}


	int ans = 0;
	bool c = 0;
	while (idx >= 0) {
		bool flag = false;

		for (int i = 0; i <= idx; ++i) {
			int f = (int)(i && col[c][i] != col[c][i - 1]) + (i < idx && col[c][i] != col[c][i + 1]);
			flag |= f;
			cnt[c][i] -= min(f, cnt[c][i]);
		}



		int idx2 = 0, idx1 = 0;
		while (idx1 <= idx) {
			cnt[!c][idx2] = 0;
			col[!c][idx2] = col[c][idx1];
			while (idx1 <= idx && (col[c][idx1] == col[!c][idx2] || !cnt[c][idx1])) {
				cnt[!c][idx2] += cnt[c][idx1];
				++idx1;
			}
			
			if (cnt[!c][idx2])
				++idx2;
		}

		if (!flag)
			break;

		idx = idx2 - 1;
		++ans;
		c = !c;
	}

	cout << ans << endl;
	return 0;
}
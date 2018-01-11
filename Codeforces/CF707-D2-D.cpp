#include <bits/stdc++.h>
using namespace std;
const int MAXQ = 100100;
const int MAX = 1010;

vector<bitset<MAX> > row[MAX];
int op[MAXQ][MAX], sum[MAXQ], n, m, q;
int main() {
	scanf("%d%d%d", &n, &m, &q);
	bitset<MAX> width(string(m, '1') + '0');
	for (int i = 1; i <= n; ++i)
		row[i].push_back(bitset<MAX>());

	for (int t = 1; t <= q; ++t) {
		int type, x, y;
		scanf("%d%d", &type, &x);

		int prv = type == 4 ? x : (t - 1);
		sum[t] = sum[prv];
		for (int i = 1; i <= n; ++i)
			op[t][i] = op[prv][i];

		if (type == 1) {
			scanf("%d", &y);
			sum[t] = sum[t - 1];
			op[t][x] = row[x].size();
			row[x].push_back(row[x][op[t - 1][x]]);
			if (!row[x].back().test(y)) {
				row[x].back().set(y);
				++sum[t];
			}
		} else if (type == 2) {
			scanf("%d", &y);
			sum[t] = sum[t - 1];
			op[t][x] = row[x].size();
			row[x].push_back(row[x][op[t - 1][x]]);
			if (row[x].back().test(y)) {
				row[x].back().reset(y);
				--sum[t];
			}
		} else if (type == 3) {
			op[t][x] = row[x].size();
			row[x].push_back(~row[x][op[t - 1][x]] & width);
			sum[t] = sum[t - 1] - m + 2 * row[x].back().count();
		}

		cout << sum[t] << endl;
	}
	return 0;
}

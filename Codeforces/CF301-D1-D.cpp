#include <bits/stdc++.h>
using namespace std;
const int MAX = 200200;
int bit[MAX], arr[MAX], seen[MAX], ans[MAX], n, m;
vector<int> adj[MAX], en[MAX], q[MAX];

void update(int idx) {
	while (idx <= n) {
		++bit[idx];
		idx += idx & -idx;
	}
}

int query(int idx) {
	int ret = 0;
	while (idx) {
		ret += bit[idx];
		idx -= idx & -idx;
	}
	return ret;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", arr + i);

	for (int i = 1, l, r; i <= m; ++i) {
		scanf("%d%d", &l, &r);
		en[l].push_back(r);
		q[l].push_back(i);
	}

	for (int i = n; i; --i) {
		seen[arr[i]] = i;
		int c = arr[i];

		for (int j = 0, len = adj[c].size(); j < len; ++j)
			update(adj[c][j]);
		
		while (c <= n) {
			if (seen[c])
				update(seen[c]);
			else
				adj[c].push_back(i);
			c += arr[i];
		}

		for (int j = 0, len = q[i].size(); j < len; ++j)
			ans[q[i][j]] = query(en[i][j]);
	}

	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
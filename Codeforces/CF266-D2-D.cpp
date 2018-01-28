#include <bits/stdc++.h>
using namespace std;
const int MAX = 210;
int inf;
int n, m, cost[MAX][MAX];
int U[MAX * MAX], V[MAX * MAX], W[MAX * MAX];

bool check(int mid) {
	for (int i = 0; i < m; ++i) {
		int a = U[i], b = V[i];
		int w = W[i];
		vector<pair<int, int> > v(1);
		int start = 0;
		bool valid_edge = true;
		for (int i = 1; i <= n && valid_edge; ++i) {
			int r1 = mid - cost[i][a];
			int r2 = mid - cost[i][b];
			if (r1 + r2 >= w) {
				++start;
			} else {
				valid_edge = false;
				if (r1 >= 0) {
					valid_edge = true;
					++start;
					v.push_back({ r1 + 1, -1 });
				}
				if (r2 >= 0) {
					valid_edge = true;
					v.push_back({ w - r2, 1 });
				}
			}
		}
		if (!valid_edge)
			continue;
		v.push_back({ 0, start });
		sort(v.begin(), v.end());

		for (int i = 1, len = v.size(); i < len; ++i) {
			v[i].second += v[i - 1].second;
			if (v[i].second == n)
				return true;
		}
	}
	return false;
}

int main() {
	scanf("%d%d", &n, &m);
	
	memset(cost, 11, sizeof cost);
	inf = cost[0][0];
	for (int i = 1; i <= n; ++i)
		cost[i][i] = 0;

	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d", U + i, V + i, W + i);
		W[i] <<= 1;
		cost[U[i]][V[i]] = cost[V[i]][U[i]] = W[i];
	}

	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				cost[i][j] = min(cost[i][j], cost[k][i] + cost[k][j]);



	int low = 0, high = 1e5 * MAX;
	while (low <= high) {
		int mid = (low + high) >> 1;
		if (check(mid))
			high = mid - 1;
		else
			low = mid + 1;
	}
	printf("%f\n", (high + 1) / 2.0);
	return 0;
}

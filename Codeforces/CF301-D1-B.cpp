#include <bits/stdc++.h>
using namespace std;
const int MAX = 110;
const int inf = 1e9;
int n, d, arr[MAX], cost[MAX], dist[MAX][MAX], X[MAX], Y[MAX];

bool check(int mid) {
	fill(cost, cost + n + 1, -inf);
	cost[1] = mid;
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (i != j && cost[i] >= 0)
					cost[j] = max(cost[j], cost[i] + dist[i][j]);
	return cost[n] >= 0;
}

int main() {
	cin >> n >> d;
	for (int i = 2; i < n; ++i)
		cin >> arr[i];
	for (int i = 1; i <= n; ++i)
		cin >> X[i] >> Y[i];

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			dist[i][j] = arr[j] - (abs(X[i] - X[j]) + abs(Y[i] - Y[j])) * d;

	int low = 0, high = 4e2 * d;
	while (low <= high) {
		int mid = (low + high) >> 1;
		if (check(mid))
			high = mid - 1;
		else
			low = mid + 1;
	}

	cout << high + 1 << endl;
	return 0;
}

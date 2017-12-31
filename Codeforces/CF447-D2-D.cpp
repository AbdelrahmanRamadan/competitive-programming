/*input
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: D - DZY Loves Modification
	@link: http://codeforces.com/contest/447/my
	@judge: Codeforces
	@idea: TODO: update with formal proof
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 1010;
int v[2][MAX], sz[2], k, p;
ll sum[2][MAX * MAX];
int main() {
	scanf("%d%d%d%d", &sz[0], &sz[1], &k, &p);
	for (int i = 0; i < sz[0]; ++i) {
		for (int j = 0, x; j < sz[1]; ++j) {
			scanf("%d", &x);
			v[0][i] += x;
			v[1][j] += x;
		}
	}
	for (int i = 0; i < 2; ++i) {
		priority_queue<long long> q;
		for (int j = 0; j < sz[i]; ++j)
			q.push(v[i][j]);
		for (int j = 1; j <= k; ++j) {
			sum[i][j] = sum[i][j - 1] + q.top();
			long long nval = q.top() - p * sz[!i];
			q.pop();
			q.push(nval);
		}
	}

	long long ans = LLONG_MIN;
	for (int i = 0; i <= k; ++i)
		ans = max(ans, sum[0][i] + sum[1][k - i] - 1LL * p * i * (k - i));

	printf("%lld\n", ans);
	return 0;
}
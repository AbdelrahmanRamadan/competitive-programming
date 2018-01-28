#include <bits/stdc++.h>
using namespace std;


const int MAX = 1e5;


int dp(int idx, int prv) {
	if (idx == n)
		return 0;
	if (vis[idx][prv])
		return ans[idx][prv];
	
	ans[idx][prv] = dp(idx + 1, prv);
	if (val[idx] > val[prv])
		ans[idx][prv] = max(ans[idx][prv], dp(idx + 1, idx));

	vis[idx][prv] = true;
	return ans[idx][prv];
}

int dp(int i1, int i2) {
	if (i1 == n1 || i2 == n2)
		return 0;
	ans[i1][i2] = max({
		dp(i1 + 1, i2),
		dp(i1, i2 + 1)
	});
	if (str1[i1] == str2[i2])
		ans[i1][i2] = max(ans[i1][i2], dp(i1 + 1, i2 + 1) + 1);
	return ans[i1][i2];
}





int dp(int w) {

	ans[w] = 0;
	for (int i = 0; i < n; ++i) {
		ans[w] = max(ans[w], p[i] + dp(w - weight[i]));
	}
}


int dp2(int idx, int w) {

	ans[idx][w] = max({
		dp(idx + 1, w),
		p[i] + dp(idx + 1, w - weight[idx]),
		p[i] + dp(idx, w - weight[idx]);
	});
}

int dp(int len) {

	ans[len] = p[len];
	for (int i = 1; i < n; ++i)
		ans[len] = max(ans[len], dp(i, len - i));
}

int dp(int r, int c) {
	if (vis[r][c])
		return ans[r][c];
	ans[r][c] = val[r][c] + max(dp(r + 1, c), dp(r, c + 1));
	vis[r][c] = true;
	return ans[r][c];
}


int dp(int i, int len) {
	ans[i][len] = max({
		p[i] + dp(i + 1, len - i),
		p[i] + dp(i, len - i),
		dp(i + 1, len);
	});
}

int dp(int idx, int rem) {
	id (rem < 0)
		return 0;
	if (idx == n) {
		if (rem == 0)
			return 1;
		else
			return 0;
	}
	ans[idx][rem] = dp(idx + 1, rem - p[idx])
					+ dp(idx + 1, rem);
}


int main() {



	return 0;
 }


/*





*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: C. Matrix
	@link: http://codeforces.com/contest/365/problem/C
	@judge: Codeforces
	@idea: Submatrix sum can be converted with a simple math to = SUM(x <= i <= y){ S[i] } * SUM(z <= i <= t){ S[i] }
			means the multiplication of the sum of two substrings, so we calculate the sum of all substrings and for
			each substring sum add to the answer the number of substrings have sum equal to A / current_sum.
			* handle A = 0 case
*/

#include <bits/stdc++.h>
using namespace std;
const int MAX = 50000;
char str[MAX];
int cnt[MAX], a;

int main() {
	long long ans = 0, all = 0;
	cin >> a >> str;
	int n = strlen(str);
	for (int i = 0; i < n; ++i) {
		int sum = 0;
		for (int j = i; j < n; ++j) {
			sum += str[j] - '0';
			++cnt[sum];
			++all;
		}
	}
	for (int i = 0; i < n; ++i) {
		int sum = 0;
		for (int j = i; j < n; ++j) {
			sum += str[j] - '0';
			if (!sum && !a)
				ans += all;
			if (sum > 0 && a % sum == 0 && a / sum < MAX)
				ans += cnt[a / sum];
		}
	}
	cout << ans << endl;
	return 0;
}
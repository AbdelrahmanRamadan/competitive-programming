/*input
5 8
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: CF900-D2-D
	@link: http://codeforces.com/problemset/problem/900/D
	@judge: Codeforces
	@idea: inclusion-exclusion principal
*/
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;

void mod(int& x) {
	while (x < 0)
		x += MOD;
	while (x >= MOD)
		x -= MOD;
}

int power(long long base, int exp) {
	long long ret = 1;
	while (exp) {
		if (exp & 1)
			ret = ret * base % MOD;
		base = base * base % MOD;
		exp >>= 1;
	}
	return ret;
}
unordered_map<int, int > mp;
int solve(int sum) {
	if (sum == 1)
		return 1;
	if (mp.count(sum))
		return mp[sum];
	int &ret = mp[sum];
	
	ret = power(2, sum - 1) - 1;
	int i;
	for (i = 2; i * i < sum; ++i) {
		if (sum % i == 0) {
			ret -= solve(i) + solve(sum / i);
			mod(ret);
		}
	}
	if (i * i == sum)
		ret -= solve(i);
	mod(ret);
	return ret;
}
int main() {
	int x, y;
	cin >> x >> y;
	cout << (y % x ? 0 : solve(y / x)) << endl;	
	return 0;
}
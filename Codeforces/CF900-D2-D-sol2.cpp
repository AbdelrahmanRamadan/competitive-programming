/*input
3 9
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

int solve(int sum) {
	vector<int> p;
	int temp = sum;
	for (int i = 2; i * i <= temp; ++i) {
		if (temp % i == 0) {
			p.push_back(i);
			while (temp % i == 0)
				temp /= i;
		}
	}
	if (temp != 1)
		p.push_back(temp);

	int sz = p.size();
	int mask = 1 << sz;
	int ans = 0;
	while (--mask >= 0) {
		int mul = 1, cnt = 0;
		for (int i = 0; i < sz; ++i) {
			if ((mask >> i) & 1) {
				mul *= p[i];
				++cnt;
			}
		}
		if (cnt & 1)
			ans += MOD - power(2, sum / mul - 1);
		else
			ans += power(2, sum / mul - 1);
		if (ans > MOD)
			ans -= MOD;
	}
	return ans;
}

int main() {
	int x, y;
	cin >> x >> y;
	cout << (y % x ? 0 : solve(y / x)) << endl;	
	return 0;
}
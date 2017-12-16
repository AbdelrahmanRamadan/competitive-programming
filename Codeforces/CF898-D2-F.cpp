/*input
123123123456456456579579579
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: CF898-D2-F
	@link: http://codeforces.com/contest/898/problem/F
	@judge: Codeforces
	@idea: bruteforce but calculate the sum of the hashes instead of the actual sum
*/
#include <bits/stdc++.h>
using namespace std;
const int H = 3;
const int MOD[H] = { 1000001957, 1000000579, 1000000223 };
const int BASE = 10;
const int MAX = 1000100;
int base_pow[MAX][H];
char str[MAX];

struct hash {
	vector<int> h;
	hash() : h(vector<int>(H, 0)) {}
	bool operator == (const hash& o) const {
		return h == o.h;
	}
	hash operator + (const hash& o) const {
		hash ret{};
		for (int i = 0; i < H; ++i)
			ret.h[i] = (h[i] + o.h[i]) % MOD[i];
		return ret;
	}
	void push_back(char c) {
		for (int i = 0; i < H; ++i)
			h[i] = (1LL * h[i] * BASE + (c - '0')) % MOD[i];
	}
	hash sub(const hash& o, int exp) {
		hash ret{};
		for (int i = 0; i < H; ++i)
			ret.h[i] = (h[i] + MOD[i] - 1LL * o.h[i] * base_pow[exp][i] % MOD[i]) % MOD[i]; 
		return ret;
	}
} hashed[MAX];

bool test(int i, int j, int res) {
	if (i < 1 || j < 1 || res < 1 || (i > 1 && str[1] == '0') || (j > 1 && str[i + 1] == '0') || (res > 1 && str[i + j + 1] == '0'))
		return false;
	j += i;
	res += j;
	return hashed[i] + hashed[j].sub(hashed[i], j - i) == hashed[res].sub(hashed[j], res - j);
}

void print(int i, int j, int res) {
	int idx = 1;
	while (i--)
		putchar(str[idx++]);
	putchar('+');
	while (j--)
		putchar(str[idx++]);
	putchar('=');
	while (res--)
		putchar(str[idx++]);
}

int main() {
	scanf("%s", str + 1);
	int n = strlen(str + 1);

	for (int i = 0; i < H; ++i)
		base_pow[0][i] = 1;

	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < H; ++j)
			base_pow[i][j] = 1LL * base_pow[i - 1][j] * BASE % MOD[j];

	for (int i = 1; i <= n; ++i) {
		hashed[i] = hashed[i - 1];
		hashed[i].push_back(str[i]);
	}

	for (int i = 1; i < n; ++i) {
		int res = max(i, (n - i) / 2);
		for (int j = 0; j < 3; ++j)
			if (test(i, n - i - res - j, res + j))
				return print(i, n - i - res - j, res + j), 0;
	}
	return 0;
}
/*input
67878 100000 8
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: CF900-D2-B
	@link: http://codeforces.com/problemset/problem/900/B
	@judge: Codeforces
	@idea: math - long division
*/
#include <bits/stdc++.h>
using namespace std;
const int MAX = 1000100;
int main() {
	int a, b, c;
	cin >> a >> b >> c;
	for (int i = 1; i < MAX; ++i) {
		a %= b;
		a *= 10;
		if (c == a / b)
			return cout << i << endl, 0;
	}
	cout << -1 << endl;
	return 0;
}
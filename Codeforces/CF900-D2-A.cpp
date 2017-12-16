/*input
3
1 2
2 1
4 60
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: CF900-D2-A
	@link: http://codeforces.com/problemset/problem/900/A
	@judge: Codeforces
	@idea: count all Xs less/greater than 0
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		cnt += x > 0;
	}
	if (cnt < 2 || n - cnt < 2)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	return 0;
}
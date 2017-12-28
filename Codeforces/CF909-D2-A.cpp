/*input
tom riddle
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: http://codeforces.com/contest/909/problem/A
	@link: Generate Login
	@judge: Codeforces
	@idea: bruteforce - try all possible prefixes
*/

#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long double myf;
typedef pair<int, int> pii;

const int MAX = 100100;

int main() {
	string a, b;
	cin >> a >> b;
	int n = a.size();
	int m = b.size();
	string ans = (string("") + a[0]) + b[0];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			string temp = a.substr(0, i) + b.substr(0, j);
			ans = min(ans, temp);
		}
	cout << ans << endl;
	return 0;
}
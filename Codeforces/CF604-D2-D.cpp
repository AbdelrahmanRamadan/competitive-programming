/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: D. Moodular Arithmetic
	@link: http://codeforces.com/contest/604/problem/D
	@judge: Codeforces
	@idea: if we know the output of the function at f(x) then we know its output at f(x*k % p),
		f(x*k^2 % p), f(x*k^3 % p), ..., f(x*k^y % p) until k^y % p == 1 then f(x*k^y % p) = f(x)
		so we need to know how many cycles in numbers and the answer should be p^cycles_count
		because we can take each cycle and assign any output from 0 to p-1 for its start node f(x)
		then generates the output of the remaining nodes of the cycle multiplying each time by k.
		There's still a tricky case to handle:-
		* the 0 cycle case, for x = 0, f(k * x) = f (k * 0) = k * f(0) = f(0)
		so in order to satisfy this equality f(0) should be always equal to zero or k should be equal to one
		so we remove the 0 cycles in all cases unless k = 1

		Note: since p is always a prime larger than k, the graph will always be a group of disconnected
		cycles except for k = 0 case which the above algorithm handles correctly
*/

#include <bits/stdc++.h>
using namespace std;
const int MAX = 1001000;
const int MOD = 1000000007;
bool vis[MAX];
int main() {
	int p, k;
	cin >> p >> k;
	int cnt = p - (k != 1);
	for (int i = 0; i < p; ++i) if (!vis[i]) {
		int j = i;
		++cnt;
		while (!vis[j]) {
			vis[j] = true;
			j = 1LL * j * k % p;
			--cnt;
		}
	}
	int ans = 1;
	for (int i = 0; i < cnt; ++i)
		ans = 1LL * ans * p % MOD;
	cout << ans << endl;
	return 0;
}
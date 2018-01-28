/*input



1 10 1 
2 10 1 



1 10 1 
1 10 1 


 
1 10 1 
4 4 1 
1 5 1 
6 10 1
1 10 1 
1 5 1 
6 10 1



*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem:
	@link:
	@judge:
	@idea:
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 10001000;
const int BUFF = 100;

ll X[MAX], Y[MAX], Z[MAX];
int n;
char str[BUFF];

inline bool empty(char *str) {
	return str[0] > '9' || str[0] < '0';
}

inline char* mygets(char *str) {
	return fgets(str, BUFF, stdin);
}

bool input(){
	n = 0;
	while(true) {
		if (mygets(str) == NULL)
			return n > 0;
		if (empty(str))
			return true;
		sscanf(str, "%lld%lld%lld", X + n, Y + n, Z + n);
		n++;
	}
	assert(false);
	return false;
}


ll count(ll mid) {
	ll ret = 0;
	for (int i = 0; i < n; ++i) {
		if (mid >= X[i])
			ret += (min(Y[i], mid) - X[i]) / Z[i] + 1;
	}
	return ret;
};

int main() {
	while (input()) {
		if (!n) continue;

		ll low = *min_element(X, X + n), high = *max_element(Y, Y + n);
		while (low <= high) {
			ll mid = (low + high) >> 1;
			if (count(mid) & 1)
				high = mid - 1;
			else
				low = mid + 1;
		}

		ll ans = high + 1;
		if (!(count(ans) & 1)) {
			puts("no corruption");
			continue;
		}
		printf("%lld %lld\n", ans, count(ans) - count(ans - 1));
	}
	return 0;
}
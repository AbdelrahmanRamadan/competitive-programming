/*input
2
*/
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long double myf;
typedef pair<int, int> pii;

const int MAX = 100100;

int main() {
	int n, ans = 0;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < i; ++j)
			if (j + i <= n)
				++ans;
	}
	cout << ans << endl;
	return 0;
}
/*input
2
1 1
*/
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long double myf;
typedef pair<int, int> pii;

const int MAX = 100100;
int cnt[MAX];
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		cnt[x]++;
	}
	for (int i = 1; i < MAX; ++i)
		if (cnt[i] & 1)
			return cout << "Conan" << endl, 0;
	cout << "Agasa" << endl;
	return 0;
}
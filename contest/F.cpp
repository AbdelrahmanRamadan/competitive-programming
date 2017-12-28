/*input
12
*/
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long double myf;
typedef pair<int, int> pii;

const int MAX = 100100;
int n, arr[MAX];

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i)
		arr[i] = i;
	do {
		bool f1 = true, f2 = true;
		for (int i = 1; i <= n; ++i) {
			f1 &= !(arr[i] & i) && arr[i] != i;
			f2 &= (bool)(arr[i] & i) && arr[i] != i;
		}
		if (f2) {
			for (int i = 1; i <= n; ++i)
				cout << arr[i] << ' ';
			cout << endl;
			cout << f1 << ":" << f2 << endl;
		}

	} while (next_permutation(arr + 1, arr + 1 + n));
	return 0;
}
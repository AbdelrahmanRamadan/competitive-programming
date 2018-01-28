/*input
8
1 2 4 8 16 32 64 576
*/
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long double myf;
typedef pair<int, int> pii;

const int MAX = 1010;

int main() {
	set<int> s;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		s.insert(x);
	}
	for (int i = 0; i <= MAX; ++i) {
		if (s.count(i * i))
			s.erase(i * i);
	}
	cout << *s.rbegin() << endl;
	return 0;
}
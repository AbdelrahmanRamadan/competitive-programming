#include <bits/stdc++.h>
using namespace std;
int v[10];
int main() {
	set<int, function<bool(int, int)> > s([&] (int a, int b) {
		return v[a] < v[b];
	});

	for (int i = 1; i < 5; ++i) {
		v[i] = 5 - i;
		s.insert(i);
	}
	v[0] = 3;
	cout << *s.lower_bound(0) << endl;
	for (auto i : s)
		cout << i << ":" << v[i] << endl;
	return 0;
}
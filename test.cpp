#include <bits/stdc++.h>
using namespace std;

vector<int> solve(const vector<int>& v) {
	vector<int> ret;
	int n = v.size();
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i + k < n; ++i) {
			int val = 0;
			for (int j = 0; j <= k; ++j)
				val = max(val, v[i + j]);
			ret.push_back(val); 
		}
	}
	return ret;
}
int main() {
	srand(time(NULL));
	int n = 9;
	// vector<int> v(n);
	vector<int> v({1, 2, 3, 4, 5, 6, 7, 8, 9});
	// iota(v.begin(), v.end(), 1);
	// random_shuffle(v.begin(), v.end());
	vector<int> w(n + 1), freq(n + 1);
	// for (int i = 0; i < n; ++i) {
	// 	w[v[i]] = 1;
	// 	for (int j = i + 1; j < n && v[j] < v[i]; ++j)
	// 		++w[v[i]];
	// 	for (int j = i - 1; j >= 0 && v[j] < v[i]; --j)
	// 		++w[v[i]];
	// }
	for (int i : v)
		cout << i << ' ';
	cout << endl;

	v = solve(v);

	for (int i : v)
		cout << i << ' ';
	cout << endl;
	
	v = solve(v);

	for (int i : v)
		cout << i << ' ';
	cout << endl;
	int sum = 0;
	for (int i : v)
		freq[i]++, sum += i;
	for (int i = 1; i <= n; ++i)
		cout << i << ":" << freq[i] << endl;
	cout << sum << ":" << endl;

	// for (int i : v)
	// 	++freq[i];

	return 0;
}
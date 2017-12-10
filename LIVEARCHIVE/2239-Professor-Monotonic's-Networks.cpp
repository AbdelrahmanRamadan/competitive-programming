/*input
4 5
1 2 3 4 1 3
2 4 2 3
8 0
3 3
1 2 2 3 1 2
0 0
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 2239 Professor Monotonic's Networls
	@link: https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=240
	@judge: LIVEARCHIVE
	@idea:
		- to check if it's a valid sorting network you only need to test it on all sequences with at least
			to distinct numbers so generate all binary sequences of length n and test the algorithm on it
		- the time needed to compelete the sorting algorithm is simply the longest path in the network
			assuming the comparators as the vertecies, and since the comparators in the problem are given
			in running order so we don't need to store the graph to calculate the longest path
		- intuition behind the two distinct numbers solution is that at any unsorted sequence there must be
			at least two numbers in a the wrong orders so all i need to generate such a sequence is those
			two numbers and any set of numbers that's below/above each of them, and any equal number could be
			considered below or above.
*/

#include <bits/stdc++.h>
using namespace std;
const int MAX = 155;
const int VAL = 20;

int n, m, a[MAX], b[MAX];
int main() {
	int T = 0;
	while (cin >> n >> m && (n || m)) {
		int occ[VAL]{}, mx = 0;
		for (int i = 0; i < m; ++i) {
			cin >> a[i] >> b[i];
			occ[a[i]] = occ[b[i]] = max(occ[a[i]], occ[b[i]]) + 1;
			mx = max(mx, occ[a[i]]);
		}

		int mask = 1 << n;
		bool flag = true;
		while (--mask >= 0) {
			int arr[VAL]{};
			for (int i = 0; i < n; ++i)
				arr[i + 1] = (mask >> i) & 1;
			
			for (int i = 0; i < m; ++i)
				if (arr[a[i]] > arr[b[i]])
					swap(arr[a[i]], arr[b[i]]);

			for (int i = 2; i <= n; ++i)
				flag &= arr[i] >= arr[i - 1];
		}

		cout << "Case " << ++T << " is ";
		if (!flag)
			cout << "not ";
		cout << "a sorting network and operates in " << mx << " time units." << endl;
	}

	return 0;
}

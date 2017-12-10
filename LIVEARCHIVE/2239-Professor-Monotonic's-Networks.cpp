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
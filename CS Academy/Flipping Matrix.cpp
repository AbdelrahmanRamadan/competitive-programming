/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: Flipping Matrix
	@link: https://csacademy.com/contest/archive/task/flipping-matrix
	@judge: CS Academy
	@idea: recursive maximum matching
*/
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long double myf;
typedef pair<int, int> pii;

const int MAX = 1010;
int n, matched[MAX], vis[MAX], head[MAX];
int nxt[MAX * MAX], to[MAX * MAX], Ecnt = 1, ID = 1;

void addEdge(int u, int v) {
	nxt[Ecnt] = head[u];
	head[u] = Ecnt;
	to[Ecnt++] = v;
}

int match(int cur) {
	if (vis[cur] == ID)
		return false;
	vis[cur] = ID;
	for (int i = head[cur]; i; i = nxt[i])
		if (!matched[to[i]] || match(matched[to[i]])) {
			matched[to[i]] = cur;
			return true;
		}
	return false;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1, x; j <= n; ++j) {
			scanf("%d", &x);
			if (x) addEdge(i, j);
		}
	}

	for (int i = 1; i <= n; ++i, ++ID)
		if (!match(i))
			return cout << -1 << endl, 0;

	++ID;
	for (int i = 1; i <= n; ++i) {
		vis[i] = ID;
		int cur = matched[i];
		while (vis[cur] != ID) {
			vis[cur] = ID;
			cout << "R " << matched[cur] << ' ' << cur << endl;
			swap(cur, matched[cur]);
		}
	}

    return 0;
}
#include <bits/stdc++.h>
#define leftNode (root << 1)
#define rightNode (leftNode | 1)
#define midRange ((st + en) >> 1)
#define goLeft st, midRange, leftNode
#define goRight midRange + 1, en, rightNode
using namespace std;
const int LG = 18;
const int MAX = 1 << LG;
int n, q, _time, val[MAX], arr[MAX], in[MAX], out[MAX], par[MAX][LG], dpth[MAX];
long long seg[MAX * 2], lazy[MAX * 2];
vector<int> adj[MAX];

void dfs(int u, int p) {
	dpth[u] = dpth[p] + 1;
	par[u][0] = p;
	for (int i = 1; i < LG; ++i)
		par[u][i] = par[par[u][i - 1]][i - 1];

	in[u] = ++_time;
	arr[_time] = val[u];
	
	for (int i = 0, len = adj[u].size(); i < len; ++i)
		if (adj[u][i] != p)
			dfs(adj[u][i], u);

	out[u] = _time;
}

int up(int u, int d) {
	for (int i = 0; i < LG; ++i)
		if ((d >> i) & 1)
			u = par[u][i];
	return u;
}

int lca(int u, int v) {
	if (dpth[u] < dpth[v])
		swap(u, v);
	u = up(u, dpth[u] - dpth[v]);
	for (int i = LG - 1; i >= 0; --i) {
		if (par[u][i] != par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	}

	return u == v ? u : par[u][0];
}

long long build(int st = 1, int en = n, int root = 1) {
	if (st == en)
		return seg[root] = arr[st];
	return seg[root] = build(goLeft) + build(goRight);
}

void split(int root, int r) {
	lazy[leftNode] += lazy[root];
	lazy[rightNode] += lazy[root];

	seg[leftNode] += (r + 1) / 2 * lazy[root];
	seg[rightNode] += r / 2 * lazy[root];

	lazy[root] = 0;
}

long long update(int l, int r, int x, int st = 1, int en = n, int root = 1) {
	if (st > r || en < l)
		return seg[root];
	if (st >= l && en <= r) {
		lazy[root] += x;
		return seg[root] += 1LL * x * (en - st + 1);
	}
	
	if (lazy[root])
		split(root, en - st + 1);
	return seg[root] = update(l, r, x, goLeft) + update(l, r, x, goRight);
}

long long query(int l, int r, int st = 1, int en = n, int root = 1) {
	if (st > r || en < l)
		return 0;
	if (st >= l && en <= r)
		return seg[root];
	
	if (lazy[root])
		split(root, en - st + 1);
	return query(l, r, goLeft) + query(l, r, goRight);
}

int real_lca(int u, int v, int root) {
	int l1 = lca(u, v), l2 = lca(u, root), l3 = lca(v, root);
	u = dpth[l1] > dpth[l2] ? l1 : l2;
	u = dpth[l3] > dpth[u] ? l3 : u;
	return u;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i)
		cin >> val[i];

	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 0);
	build();

	int root = 1;
	while (q--) {
		int type, u, v, x;
		cin >> type >> u;
		if (type == 1) {
			root = u;
		} else if (type == 2) {
			cin >> v >> x;
			u = real_lca(u, v, root);
			if (u == root) {
				update(in[1], out[1], x);
			} else if (lca(u, root) != u) {
				update(in[u], out[u], x);
			} else {
				update(in[1], out[1], x);
				v = up(root, dpth[root] - dpth[u] - 1);
				update(in[v], out[v], -x);
			}
		} else {
			long long ans;
			if (u == root) {
				ans = query(in[1], out[1]);
			} else if (lca(u, root) != u) {
				ans = query(in[u], out[u]);
			} else {
				ans = query(in[1], out[1]);
				v = up(root, dpth[root] - dpth[u] - 1);
				ans -= query(in[v], out[v]);
			}

			cout << ans << '\n';
		}
	}
	return 0;
}
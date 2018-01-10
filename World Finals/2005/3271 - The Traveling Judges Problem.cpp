/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 3271 - The Traveling Judges Problem
	@link: https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=1272
	@judge: LIVEARCHIVE
	@idea: try to construct a minimum spanning tree from all possible connected subsets of nodes which convers
		all nodes containing judges and the root, then choose the minimum one.
		* this codes contains many tweeks for optimizing the MST build and the comparison process
		* Complexity: O(2^(V-2) * E * log_star(V))
*/

#include <bits/stdc++.h>
#define U second.first
#define V second.second
#define W first
using namespace std;
typedef pair<int, pair<int, int> > edge;
const int MAX = 22;
const int inf = 2e9;
int n, m, k, src, parent[MAX], sz[MAX];
vector<edge> e;
vector<vector<int> > adj;
bool dfs(int u, int par, vector<int> &v) {
	if (u == src) {
		v.push_back(u);
		return true;
	}
	for (int i = 0, len = adj[u].size(); i < len; ++i) if(adj[u][i] != par)
		if (dfs(adj[u][i], u, v)) {
			v.push_back(u);
			return true;
		}
	return false;
}
int getPar(int u) {
	if (u == parent[u])
		return u;
	return parent[u] = getPar(parent[u]);
}
int main() {
	int T = 0, x;
	while (~scanf("%d%d%d", &n, &x, &m) && ~n) {
		e.resize(m);
		src = x - 1;
		for (int i = 0, u, v, w; i < m; ++i) {
			scanf("%d%d%d", &e[i].U, &e[i].V, &e[i].W);
			--e[i].U, --e[i].V;
		}
		sort(e.begin(), e.end());
		
		scanf("%d", &k);
		vector<int> J(k);
		int judges = 1 << src;
		for (int i = 0; i < k; ++i) {
			scanf("%d", &J[i]);
			--J[i];
			judges |= 1 << J[i];
		}

		int lim = (1 << n);
		int ansd = inf, ansm = 0, ansc = 0;
		for (int mask = 0; mask < lim; mask = (mask + 1) | judges) {
			int curd = 0, curc = __builtin_popcount(mask);
			for (int i = 0; i < n; ++i)
				parent[i] = i;
			int comp = curc;
			for (int i = 0; i < m; ++i) {
				if (((mask >> e[i].U) & 1) && ((mask >> e[i].V) & 1) && getPar(e[i].V) != getPar(e[i].U)) {
					parent[parent[e[i].V]] = parent[e[i].U];
					curd += e[i].W;
					--comp;
				}
			}
			if (comp != 1)
				continue;
			if (curd < ansd) {
				ansd = curd;
				ansm = mask;
			} else if (curd == ansd) {
				if (curc < ansc) {
					ansd = curd;
					ansm = mask;
				} else if (curc == ansc) {
					int f = mask ^ ansm;
					f = f & -f;
					if (f & mask) {
						ansd = curd;
						ansm = mask;
					}
				}
			}	
		}
		adj.clear();
		adj.resize(n);
		int mask = ansm;
		for (int i = 0; i < n; ++i)
			parent[i] = i;
		for (int i = 0; i < m; ++i) {
			if (((mask >> e[i].U) & 1) && ((mask >> e[i].V) & 1) && getPar(e[i].V) != getPar(e[i].U)) {
				parent[parent[e[i].V]] = parent[e[i].U];
				adj[e[i].U].push_back(e[i].V);
				adj[e[i].V].push_back(e[i].U);
			}
		}
		cout << "Case " << ++T << ": distance = " << ansd << endl;
		for (int i = 0; i < k; ++i) {
			vector<int> v;
			dfs(J[i], -1, v);
			cout << "   ";
			for (int j = v.size() - 1; j >= 0; --j)
				cout << v[j] + 1 << (!j ? '\n' : '-');
		}
		cout << endl;
	}
	return 0;
}

/*input
4
0 2
enabled=true
foreground=white
1 2
enabled=false
fontSize=12
2 3
enabled=true
foreground=black
caption=OK
2 1
fontSize=10
5
3 enabled
4 enabled
3 fontSize
4 foreground
2 caption
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: C. Component Tree
	@link: http://codeforces.com/gym/100513/problem/C
	@judge: Codeforces Gym
	@idea: ordering nodes by time of visiting and leaving during dfs
		* the obvious use of the dfs in/out time (order) is represent each subtree as a single substring in an array
		* it's also possible to do a very important function that's done otherwise using persistent data structures or
		 HLD which is representing a single path in the tree and calculating its value in log(n) time using binary search:
		 By pushing each node twice, push it once with the accumulative value from the root to this node when
		 visiting the node, and push it again when leaving the node with the last value was in the array before pushing the
		 node for the first time (inverting the node value)
*/

#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
const int MAX = 300300;

vector<int> adj[MAX];
unordered_map<string, vector<pair<int, string> > > vis;
unordered_map<string, string> mp[MAX];
int n, q, par, _time, in[MAX], out[MAX];
char str[20];

void dfs(int u) {
	in[u] = ++_time;
	for (auto& p : mp[u]) {
		auto& v = vis[p.fi];
		v.push_back({ in[u], p.se });
		p.se = v.size() > 1 ? v[v.size() - 2].se : "N/A";
	}

	for (int i = 0, len = adj[u].size(); i < len; ++i)
		dfs(adj[u][i]);

	out[u] = ++_time;
	for (auto& p : mp[u])
		vis[p.fi].push_back({ out[u], p.se });
	
}

int main() {
	scanf("%d", &n);
	for (int i = 1, m, u; i <= n; ++i) {
		scanf("%d %d", &u, &m);
		adj[u].push_back(i);
		while (m--) {
			scanf("%s", str);
			int x = find(str, str + strlen(str), '=') - str;
			str[x++] = '\0';
			mp[i][string(str)] = string(str + x);
		}
	}

	dfs(1);

	scanf("%d", &q);
	while (q--) {
		int c;
		scanf("%d%s", &c, str);
		auto& v = vis[string(str)];
		auto it = lower_bound(v.begin(), v.end(), make_pair(in[c] + 1, string()));
		printf("%s\n", (it != v.begin() ? (--it) -> se.c_str() : "N/A"));
		fflush(stdout);
	}
	return 0;
}

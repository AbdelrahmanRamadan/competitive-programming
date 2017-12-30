/*input
1
0 2
width=300
height=500
2
1 width
1 Width
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: C. Component Tree
	@link: http://codeforces.com/gym/100513/problem/C
	@judge: Codeforces Gym
	@idea:
*/

#include <bits/stdc++.h>
using namespace std;
const int MAX = 300300;
const int LG = 18;
const int SQRT = 1000; // sqrt(MAX / LG)

vector<int> adj[MAX];
unordered_map<int, int> mp[MAX];
unordered_map<string, int> hashed;
vector<string> vec;
int n, q, par[MAX], mx[MAX], vis[MAX], H;
char str[20];

int maxi(int u) {
	int d = 0;
	for (int i = 0, len = adj[u].size(); i < len; ++i) {
		int temp = maxi(adj[u][i]);
		if (temp > d) {
			d = temp;
			mx[u] = i;
		}
	}
	return d + 1;
}

void dfs(int u, int d) {
	if (d % SQRT == 0) {
		int v = par[u];
		int x = 0;
		while (v) {
			for (auto i : mp[v])
				if (!mp[u].count(i.first))
					mp[u][i.first] = i.second;
			if (vis[v])
				break;
			v = par[v];
		}
		vis[u] = 1;
	}

	for (int i = 0, len = adj[u].size(); i < len; ++i)
		dfs(adj[u][i], mx[u] == i ? (d + 1) : 1);
}

int main() {
	scanf("%d", &n);
	for (int i = 1, m; i <= n; ++i) {
		scanf("%d %d", &par[i], &m);
		adj[par[i]].push_back(i);
		while (m--) {
			scanf("%s", str);
			int x = find(str, str + strlen(str), '=') - str;
			str[x++] = '\0';
			string s1 = string(str), s2 = string(str + x);
			if (!hashed.count(s1)) {
				hashed[s1] = H++;
				vec.push_back(s1);
			}
			if (!hashed.count(s2)) {
				hashed[s2] = H++;
				vec.push_back(s2);
			}

			mp[i][hashed[s1]] = hashed[s2];
		}
	}

	maxi(1);
	dfs(1, 1);


	scanf("%d", &q);
	while (q--) {
		int c;
		scanf("%d%s", &c, str);
		if (!hashed.count(string(str))) {
			puts("N/A");
			continue;
		}
		int s = hashed[string(str)], ans = -1;
		int lim = SQRT * 10;
		for (int i = 0; i <= lim && c; ++i, c = par[c])
			if (mp[c].count(s)) {
				ans = mp[c][s];
				break;
			}
		string ans_str = ans == -1 ? "N/A" : vec[ans];
		printf("%s\n", ans_str.c_str());
		fflush(stdout);
	}
	return 0;
}

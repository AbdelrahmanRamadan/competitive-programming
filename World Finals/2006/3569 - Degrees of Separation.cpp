/*input
4 4
Ashok Kiyoshi Ursala Chun Ursala Kiyoshi
Kiyoshi Chun
4 2
Ashok Chun Ursala Kiyoshi
6 5
Bubba Cooter Ashok Kiyoshi Ursala Chun
Ursala Kiyoshi Kiyoshi Chun
0 0
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem:
	@link:
	@judge:
	@idea:
*/

#include <bits/stdc++.h>
using namespace std;
int n, m;
int bfs(const string& src, unordered_map<string, vector<string> >& adj) {
	queue<string> q;
	unordered_map<string, bool> vis;
	q.push(src);
	int lev = 0, cnt = n, ret = 0;
	while (q.size()) {
		int sz = q.size();
		while (sz--) {
			string cur = q.front();
			q.pop();
			if (vis[cur])
				continue;
			ret = max(ret, lev);
			--cnt;
			vis[cur] = 1;
			for (auto& s : adj[cur])
				if (!vis[s])
					q.push(s);
		}
		++lev;
	}
	return cnt > 0 ? -1 :  ret;
}
int main() {
	int T{};
	while (cin >> n >> m && (n || m)) {
		unordered_map<string, vector<string> > adj;
		
		for (int i = 0; i < m; ++i) {
			string a, b;
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		int ans = 0;
		bool dis = false;
		for (auto& s : adj) {
			int ret = bfs(s.first, adj);
			if (ret == -1) {
				dis = true;
				break;
			}
			ans = max(ans, ret);
		}
		cout << "Network " << ++T << ": ";
		if (dis)
			cout << "DISCONNECTED";
		else
			cout << ans;
		cout << endl << endl;;
	}
	return 0;
}
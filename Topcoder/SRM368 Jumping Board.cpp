/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: SRM 368 Jumping Board
	@link:
	@judge: Topcoder
	@idea: detect all cells inside cycles using dfs and give them infinity answer, then apply a dp on
		the resulting dag to find the answer
*/
#include <bits/stdc++.h>
using namespace std;
class JumpingBoard {
public:
	static const int MAX = 55;
	static const int inf = MAX * MAX;
	int dr[4] = {0, 0, 1, -1};
	int dc[4] = {1, -1, 0, 0};
	
	bool vis[MAX][MAX];
	int mem[MAX][MAX], n, m;
	
	bool out(int r, int c) {
		return r < 0 || c < 0 || r >= n || c >= m;
	}
	
	bool dfs(int r, int c, int tr, int tc, const vector<string> &v) {
		if (out(r, c) || vis[r][c] || v[r][c] == 'H')
			return false;
		vis[r][c] = true;
		for (int i = 0; i < 4; ++i) {
			int nr = r + (v[r][c] - '0') * dr[i];
			int nc = c + (v[r][c] - '0') * dc[i];
			if ((nr == tr && nc == tc) || dfs(nr, nc, tr, tc, v))
				return true;
		}
		return false;
	}
	
	int dp(int r, int c, const vector<string>& v) {
		if (out(r, c) || v[r][c] == 'H')
			return 0;
		int &ret = mem[r][c];
		if (~ret)
			return ret;
		ret = 0;
		for (int i = 0; i < 4; ++i)
			ret = max(ret, dp(r + (v[r][c] - '0') * dr[i], c + (v[r][c] - '0') * dc[i], v));
		return ++ret; 
	}
	
	int maxJumps(vector <string> v) {
		memset(mem, -1, sizeof mem);
		n = v.size(), m = v[0].size();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				memset(vis, 0, sizeof vis);
				if (dfs(i, j, i, j, v))
					mem[i][j] = inf;
			}
		}
		int ans = dp(0, 0, v);
		return ans < inf ? ans : -1;
	}
};

int main() {

	return 0;
}
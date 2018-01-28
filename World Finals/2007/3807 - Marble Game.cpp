/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 3807 - Marble Game
	@link: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1808
	@judge: LIVEARCHIVE
	@idea: BFS, compress the grid into long long to represent the current state, then try to apply all valid moves
		on the current grid.
		Direction arrays were used to write a generic move functions for all directions 
*/

#include <bits/stdc++.h>
using namespace std;
int n, m, w;

// R L D U
int dc[] = { 1, -1, 0, 0 };
int dr[] = { 0, 0, 1, -1 };
vector<vector<int> > sc, sr;
bool wall[5][5][5];
vector<vector<int> > hole;

vector<vector<int> > move(int d, vector<vector<int> > grid) {
	vector<bool> alive(m + 1);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			alive[grid[i][j]] = true;
	alive[0] = 0;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int r = sr[d ^ 1][i] + dr[d ^ 1] * j;
			int c = sc[d ^ 1][i] + dc[d ^ 1] * j;

			if (grid[r][c]) {
				int oldr = r, oldc = c;
				while (!wall[d][r][c] && !alive[hole[r][c]] && !grid[r + dr[d]][c + dc[d]]) {
					r += dr[d];
					c += dc[d];
				}
				if (alive[hole[r][c]]) {
					if (hole[r][c] != grid[oldr][oldc])
						return vector<vector<int> >();
					alive[hole[r][c]] = false;
					grid[oldr][oldc] = 0;
				} else {
					int hold = grid[oldr][oldc];
					grid[oldr][oldc] = 0;
					grid[r][c] = hold;
				}
			}
		}
	}
	return grid;
}

long long comp (const vector<vector<int> >& grid) {
	long long ret = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			ret = ret * (m + 1) + grid[i][j];
	return ret;
}

vector<vector<int> > decomp (long long h) {
	vector<vector<int> > grid(n, vector<int> (n));
	for (int i = n - 1; i >= 0; --i)
		for (int j = n - 1; j >= 0; --j) {
			grid[i][j] = h % (m + 1);
			h /= (m + 1);
		}
	return grid;
}

int main() {
	int T{};
	while (cin >> n >> m >> w && n) {

		memset(wall, 0, sizeof wall);
		sc.assign({
			{ 0, 0, 0, 0 },
			{ n - 1, n - 1, n - 1, n - 1 },
			{ 0, 1, 2, 3 },
			{ 0, 1, 2, 3 },
		});
		sr.assign({
			{ 0, 1, 2, 3 },
			{ 0, 1, 2, 3 },
			{ 0, 0, 0, 0 },
			{ n - 1, n - 1, n - 1, n - 1 },
		});

		vector<vector<int> > grid(n, vector<int> (n));
		for (int i = 1, r, c; i <= m; ++i) {
			cin >> r >> c;
			grid[r][c] = i;
		}

		hole.clear(); hole.resize(n, vector<int> (n));
		for (int i = 1, r, c; i <= m; ++i) {
			cin >> r >> c;
			hole[r][c] = i;
		}

		bool flag = false;
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < n; ++c) {
				if (grid[r][c] && hole[r][c]) {
					flag |= grid[r][c] != hole[r][c];
					for (int i = 0; i < n; ++i) {
						for (int j = 0; j < n; ++j) {
							if (grid[r][c] < grid[i][j])
								--grid[i][j];
							if (hole[r][c] < hole[i][j])
								--hole[i][j];
						}
					}
					--m;
					grid[r][c] = 0;
					hole[r][c] = 0;
				}
			}
		}

		for (int i = 1; i <= w; ++i) {
			int r1, c1, r2, c2;
			cin >> r1 >> c1 >> r2 >> c2;
			if (r1 == r2) {
				wall[0][r1][min(c1, c2)] = 1;
				wall[1][r1][max(c1, c2)] = 1;
			} else {
				wall[2][min(r1, r2)][c1] = 1;
				wall[3][max(r1, r2)][c1] = 1;
			}
		}

		for (int d = 0; d < 4; ++d)
			for (int i = 0; i < n; ++i)
				wall[d][sr[d ^ 1][i]][sc[d ^ 1][i]] = 1;

		cout << "Case " << ++T << ": ";

		if (flag) {
			cout << "impossible" << endl << endl;
			continue;
		}

		if (!m) {
			cout << 0 << " moves" << endl << endl;
			continue;
		}


		queue<long long> q;
		unordered_set<long long> vis;
		
		long long hgrid = comp(grid);
		q.push(hgrid);
		vis.insert(hgrid);

		int ans = 1;

		while (!q.empty()) {
			int sz = q.size();
			while (sz--) {
				grid = decomp(q.front());
				q.pop();
				for (int d = 0; d < 4; ++d) {
					vector<vector<int> > temp = move(d, grid);
					if (temp.size() == 0)
						continue;

					long long h = comp(temp);
					if (!h) {
						cout << ans << " moves" << endl << endl;
						goto LOOP;
					}
					
					if (!vis.count(h)) {
						q.push(h);
						vis.insert(h);
					}
				}

			}
			++ans;
		}
	
		cout << "impossible" << endl << endl;

		LOOP:;
	}

	return 0;
}
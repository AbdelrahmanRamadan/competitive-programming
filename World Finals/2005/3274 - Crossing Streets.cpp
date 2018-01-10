/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 3274 - Crossing Streets
	@link: https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=1275
	@judge: LIVEARCHIVE
	@idea: compress the grid then model the problem to grid shortest path problem.
		apply 0-1 bfs from home to univercity, any step that crosses a line will have a cost of 1,
		and 0 otherwise, this bfs can be easily applied using 2 queues or a single deque.
*/

#include <bits/stdc++.h>
#define debug(x) #x << " = " << x
#define st first
#define en second
#define X first
#define Y second
#define all(v) v.begin(), v.end()
using namespace std;
typedef pair<int, int> point;
typedef pair<point, point> segment;
const int MAX = 550;
int n;
map<int, int> mp;

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

istream& operator >> (istream& fin, point& o) {
	fin >> o.X >> o.Y;
	mp[o.X], mp[o.Y];
	return fin;
}
istream& operator >> (istream& fin, segment& o) {
	fin >> o.st >> o.en;
	if (o.st > o.en)
		swap(o.st, o.en);
	return fin;
}
ostream& operator << (ostream& fout, const point& o) {
	fout << o.X << ',' << o.Y;
	return fout;
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	int T{};

	while (cin >> n && n) {
		mp.clear();
		vector<segment> segs(n);
		point src, dist;
		for (auto& i : segs)
			cin >> i;
		cin >> src >> dist;

		int H = 0;
		for (auto& i : mp)
			i.second = ++H;

		vector<vector<int> > cost(H + 2, vector<int>(H + 2));
		vector<vector<bool> > vis(H + 2, vector<bool>(H + 2));

		for (auto& i : segs) {
			int xst = mp[i.st.X], yst = mp[i.st.Y];
			int xen = mp[i.en.X], yen = mp[i.en.Y];
			for (int x = xst; x <= xen; ++x)
				for (int y = yst; y <= yen; ++y)
					cost[x][y] = 1;
		}

		src = point(mp[src.X], mp[src.Y]);
		dist = point(mp[dist.X], mp[dist.Y]);
		for (int i = 0; i <= H; ++i)
			vis[i][0] = vis[0][i] = vis[H + 1][i] = vis[i][H + 1] = true;

		queue<point> q[2];
		int crosses = 0, ans = -1;
		q[0].push(src);

		while (!q[0].empty()) {
			while (!q[0].empty()) {
				point cur = q[0].front();
				q[0].pop();

				if (vis[cur.X][cur.Y])
					continue;

				vis[cur.X][cur.Y] = true;
				if (cur == dist)
					ans = crosses;

				for (int i = 0; i < 4; ++i) {
					int nx = cur.X + dx[i], ny = cur.Y + dy[i];
					if (!vis[nx][ny])
						q[cost[nx][ny]].push(point(nx, ny));
				}
				
			}
			swap(q[0], q[1]);
			++crosses;
		}

		cout << "City " << ++T << endl;
		cout << "Peter has to cross " << ans << " streets" << endl;
	}
	return 0;
}
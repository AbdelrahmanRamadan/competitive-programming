/*input
3
RRR RRR RRR RRR RRR RRR
RRG RRR GRR RRG RRR RRR
RRR RRR RRR RRR RRR RRR
2
A. .A .A A. .. A.
.. .. .. .. A. ..
3
.R. YYR .Y. RYY .Y. .R.
GRB YGR BYG RBY GYB GRB
.R. YRR .Y. RRY .R. .Y.
2
ZZ ZZ ZZ ZZ ZZ ZZ
ZZ ZZ ZZ ZZ ZZ ZZ
0
*/

/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 2995 - Image Is Everything
	@link: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=996
	@judge: LIVEARCHIVE
	@idea: first assume that the cube is full with cells,
		then remove any cell from the cube that makes a contradiction in the sides view,
		after removing any cell you have to check if all the old cells are valid again because removing a cell may
		create another new contradiction, continue until there's no contradictions in the cube.
		Contradiction happens when there's a cell that appears with two different colors from two sides,
		or if the cell appear empty from any side.
		Use transfromation matrixes to find the color of each cube cell from any side view prespective as follows
		// front, 	left,	 	back, 		right, 		top,		bottom
		// x,y,(z)  x,-z,(y)	x,-y,(-z)	x,z,(-y)	-z,y,(x)	z,y,(-x)
*/


#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

int d[6][3] = {
	{ 0, 1, 2 },
	{ 0, 2, 1 },
	{ 0, 1, 2 },
	{ 0, 2, 1 },
	{ 2, 1, 0 },
	{ 2, 1, 0 }
};
int sign[6][3] = {
	{ 1, 1, 1 },
	{ 1, -1, 1 },
	{ 1, -1, -1 },
	{ 1, 1, -1 },
	{ -1, 1, 1 },
	{ 1, 1, -1 },
};
int dir[6][3] = {
	{ 0, 0, 1 },
	{ 0, 1, 0 },
	{ 0, 0, -1 },
	{ 0, -1, 0 },
	{ 1, 0, 0 },
	{ -1, 0, 0 },
};


const int MAX = 15;
int ans[MAX][MAX][MAX], n;
char grid[6][MAX][MAX];

char color(vector<int> v, int s) {
	vector<int> ret(3);
	for (int i = 0; i < 3; ++i) {
		ret[i] = v[d[s][i]];
		if (sign[s][i] == -1)
			ret[i] = n - ret[i] - 1;
	}
	return grid[s][ret[0]][ret[1]];
}

bool check(int x, int y, int z) {
	char col = '?';
	for (int s = 0; s < 6; ++s) {
		vector<int> v({ x, y, z });
		char cur = color(v, s);
		if (cur == '.')
			return false;
		
		bool flag = false;
		while (true) {
			bool out = false;
			for (int i = 0; i < 3; ++i) {
				v[i] -= dir[s][i];
				if (v[i] < 0 || v[i] >= n)
					out = true;
			}
			if (out)
				break;
			if (!ans[v[0]][v[1]][v[2]])
				flag = true;
		}

		if (flag)
			continue;

		if (col == '?')
			col = cur;
		if (col != cur)
			return false;
	}
	return true;
}

int main() {
	while (cin >> n && n) {
		memset(ans, 0, sizeof ans);
		int cnt = 0;
		for (int x = 0; x < n; ++x)
			for (int s = 0; s < 6; ++s)
				cin >> grid[s][x];

		while (true) {
			bool flag = false;
			for (int x = 0; x < n; ++x) {
				for (int y = 0; y < n; ++y) {
					for (int z = 0; z < n; ++z) {
						if (!ans[x][y][z] && !check(x, y, z))
							++ans[x][y][z], ++cnt, flag = true;
					}
				}
			}
			if (!flag)
				break;
		}

		cout << "Maximum weight: " << n * n * n - cnt << " gram(s)" << endl;
	}
	return 0;
}
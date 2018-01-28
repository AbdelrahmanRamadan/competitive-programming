/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: D - AlgoRace
	@link: http://codeforces.com/contest/189/problem/D
	@judge: Codeforces
	@idea: we usually calculate the shortest paths matrix of a graph using DP (floyd warshall algorithm)
		but we can also calculate it using matrix "multiplication"
		(not exactly multiplication, we will use min() and + as the operators instead of the usual +, * operators) 
		so C[i][j] = (0 <= k < n) min{ C[i][k] + C[k][j] }
		
		So we can say that (Adj * Adj) contains all minimum paths that uses at most two edges between each pair
		of cities, and Adj^k is the shortest paths matrix for this graph.
		
		Now the cool thing about matrixes approach is that we can customize the multiplication process to solve
		a wide range of problems like counting paths in a graph for example, also the power process could be done in
		logarithmic complexity using matrix power.
		
		In this problem we need to calculate the shortest paths matrix using k cars,
		so consider matrix M is the shortest paths matrix using only one car of any type, then the shortest paths matrix
		using two cars or less is M * M, and M ^ k should be the one using k cars or less.

		all we need now is to calculate the shortest paths matrix using only one car of any type, this could be done easily
		using floyed for each car type adjacency matrix alone, then our matrix should be defines as follows
			M[i][j] = (0 <= k < m) min{ adj[k][i][j] }
		m is the number of car types and adj[k] is the adjacency matrix for the car of type k after running floyed on it.


*/
#include <bits/stdc++.h>
using namespace std;
const int MAX = 66;
const int inf = 1e9;
int cost[MAX][MAX][MAX], ans[MAX][MAX][MAX], adj[MAX][MAX], n, m, r;
int main() {
	scanf("%d%d%d", &n, &m, &r);
	memset(ans[0], 11, sizeof ans[0]);

	for (int i = 1; i <= m; ++i) {
		auto& mat = cost[i];

		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				scanf("%d", &mat[i][j]);

		for (int k = 1; k <= n; ++k)
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);

		
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				ans[0][i][j] = min(ans[0][i][j], mat[i][j]);
	}


	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				ans[k][i][j] = ans[k - 1][i][j];
				for (int c = 1; c <= n; ++c)
					ans[k][i][j] = min(ans[k][i][j], ans[k - 1][i][c] + ans[0][c][j]);
			}
		}
	}

	while (r--) {
		int s, t, k;
		scanf("%d%d%d", &s, &t, &k);
		printf("%d\n", ans[min(k, n)][s][t]);
	}

	return 0;
}
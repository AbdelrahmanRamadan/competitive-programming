/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 11234 - Expressions
	@link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2175
	@judge: UVA
	@idea: the difference between stack and queue is that stack operates using depth first search, but queue
		operates using breadth first search, so in order to have the same result using queue we have to build
		the expression tree then serialize it again level by level from the lowest level to the highest.
		* to get better grasp and understanding of the idea, draw the expression tree and check how stack
		and queue process the tree.
		* building the tree could be done easily using stack by the same algorithm descriped in the problem
		* serializing the tree level by level could be done using BFS or using an order array which compares
		the nodes in terms of depth first and order in level second, build this array using dfs then sort	
		the original string according to this order array like my solution below.
*/

#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
using namespace std;
vector<vector<int> > adj;
vector<pair<int, int> > order;
string str;
int n;

void dfs(int cur, int d = 0, int pos = 1) {
	order[cur] = { -d, pos };
	if (adj[cur].size()) {
		dfs(adj[cur][0], d + 1, pos * 2);
		dfs(adj[cur][1], d + 1, pos * 2 + 1);
	}
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> str;
		n = str.size();
		adj.clear(); adj.resize(n);
		order.resize(n);
		stack<int> stk;
		for (int i = 0; i < n; ++i) {
			if (isupper(str[i])) {
				int a = stk.top();
				stk.pop();
				int b = stk.top();
				stk.pop();
				stk.push(i);
				adj[i].push_back(a);
				adj[i].push_back(b);
			} else {
				stk.push(i);
			}
		}
		dfs(n - 1);
		
		vector<int> v(n); iota(all(v), 0);
		sort(all(v), [&] (int a, int b) {
			return order[a] < order[b];
		});

		for (int i : v)
			cout << str[i];
		cout << endl;
	}	
	return 0;
}
/*input
5 3
5 3 2 4 6
8 5 5
107 1 4
7 3 5
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: J - Shopping
	@link: http://codeforces.com/gym/101201/attachments
	@judge: Codeforces - Gym
	@idea: Key observation: when you stop by an item you continue buying from it until you have money less that its price
			so you apply a mod operation, every element is reduced at least by half after a mod operation on a number that smaller from it
			so every customer will be at most log(vi) unique items.
			all we need to do is that for each customer current money find effectively the next item that he can buy to apply another mod operation
			this can be done by iterating through the array holding a set containing the current remainder money for each customer. 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 200200;
ll arr[MAX], v[MAX];
vector<int> st[MAX], en[MAX];
int n, m;
int main() {
	set<pair<ll, int> > s;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%lld", &arr[i]);

	for (int i = 1, a, b; i <= m; ++i) {
		scanf("%lld%d%d", &v[i], &a, &b);
		st[a].push_back(i);
		en[b].push_back(i);
	}

	for (int i = 1; i <= n; ++i) {
		for (auto j : st[i])
			s.insert({ v[j], j });

		auto it = s.lower_bound({ arr[i], 0 });
		while (it != s.end()) {
			v[it -> second] = it -> first % arr[i];
			s.insert({ v[it -> second], it -> second });
			s.erase(it++);
		}

		for (auto j : en[i])
			s.erase({ v[j], j });
	}

	for (int i = 1; i <= m; ++i) {
		printf("%lld\n", v[i]);
	}
	return 0;
}

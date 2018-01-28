/*input
A
CBACBACBACBACBA
CCCCBBBBAAAA
ACMICPC
end
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 3752 - Containers
	@link: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1753
	@judge: LIVEARCHIVE
	@idea: greedy, process the containers in the arriving order, for each container, put it on the stack that has
		the greatest letter smaller than the new container's letter, this enssures the minimum number of stacks used.

*/

#include <bits/stdc++.h>
using namespace std;

int main() {
	int T{};
	string str;
	while (cin >> str && str != "end") {
		vector<char> top(27, 'Z' + 1);
		int ans = 0;
		for (int i = 0, len = str.size(); i < len; ++i) {
			int s = ans;
			for (int j = 0; j < 26; ++j)
				if (top[j] >= str[i] && top[j] < top[s])
					s = j;
			if (s == ans)
				++ans;
			top[s] = str[i];
		}
		cout << "Case " << ++T << ": " << ans << endl;

	}	
	return 0;
}
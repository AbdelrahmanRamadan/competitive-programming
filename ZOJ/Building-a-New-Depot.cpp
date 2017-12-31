/*input
6
1 1
1 3
3 3
2 1
3 2
2 2

0
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: Building a New Depot
	@link: http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=2157
	@judge: ZOJ
	@idea: iterating through each horizontal and vertical line, each two consecutive points will form a segment in the 
		fence so we add the distance between them to the answer 
*/

#include <bits/stdc++.h>
using namespace std;
const int MAX = 100100;
int main() {
	int n;
	while (cin >> n && n) {
		unordered_map<int, vector<int> > d[2];
		while (n--) {
			int x, y;
			scanf("%d%d", &x, &y);
			d[0][x].push_back(y);
			d[1][y].push_back(x);
		}
		long long ans = 0;
		for (int i = 0; i < 2; ++i) {
			for (auto& p : d[i]) {
				auto& v = p.second;
				sort(v.begin(), v.end());
				for (int i = 1, len = v.size(); i < len; i += 2)
					ans += v[i] - v[i - 1];
			}
		}
		cout << "The length of the fence will be " << ans << " units." << endl;
	}	
	return 0;
}
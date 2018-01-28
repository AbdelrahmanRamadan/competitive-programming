/*input

*/
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long double myf;
typedef pair<int, int> pii;

class HalvingEasy {
public:
	int count(vector <int> S, int T) {
		int ans = 0;
		for (int i : S) {
			while (i > T)
				i /= 2;
			ans += i == T;
		}
		return ans;
	}
};

int main() {

	return 0;
}
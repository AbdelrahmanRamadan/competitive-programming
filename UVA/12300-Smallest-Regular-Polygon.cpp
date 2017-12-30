/*input
0 0 1 1 4
1 2 3 4 5
2 3 4 5 6
0 0 0 0 0
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 12300 - Smallest Regular Polygon
	@link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=244&page=show_problem&problem=3722
	@judge: UVA
	@idea: find the area of the polygon with the diameter (longest line connecting two verticies) equal to distance between the two given points
*/

#include <bits/stdc++.h>
using namespace std;
const long double PI = acos(-1);

int main() {
	int x1, y1, x2, y2, n;
	while (cin >> x1 >> y1 >> x2 >> y2 >> n && n) {
		cout << setprecision(6) << fixed;
		
		if (n & 1) {
			long double theta = PI / 2 / n, hyp = hypot(x2 - x1, y2 - y1);
			long double base = hyp * sin(theta) * 2;
			long double height = 1 / tan(theta * 2) * (base / 2);
			cout << base * height / 2 * n << endl;

		} else {
			long double theta = 2 * PI / n, hyp = hypot(x2 - x1, y2 - y1);
			cout << hyp * hyp * sinl(theta) / 8 * n << endl;
		}
	}
	return 0;
}
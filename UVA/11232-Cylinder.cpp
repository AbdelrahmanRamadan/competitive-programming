/*input
10 10
10 50
10 30
0 0
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 11232 - Cylinder
	@link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2173
	@judge: UVA
	@idea:
		- Try to roll the longest side
			d + d * PI = w
			d = min(h, w / (1 + PI))
			area = (d / 2)^2 * PI
			vol = area * h
		- Try to roll the shortest side
			d * PI <= h
			vol = d^2 / 4 * PI * (w - d)
			c = PI / 4
			vol = c * w * d^2 - c * d^3
			Dvol/Dd = 0
			0 = 2 * c * w * d - 3 * c * d^2
			d * (2 * c * w - 3 * c * d) = 0
			d = 0 || d = (2 * w) / (3 * c)
					   = w * (8 / (3 * PI))
			d = min(h / PI, w * (8 / (3 * PI))) 
		- h / PI will be always smaller than w * (8 / (3 * PI))
			because h < w and 1 / PI < 1 / (8 / (3 * PI))
			so we don't need the differentiaition part to get accepted,
			but we need it to prove correctness

*/

#include <bits/stdc++.h>
using namespace std;
typedef long double myf;

const myf PI = 4.0L * atan2l(1.0L, 1.0L);

int main() {
	int w, h;
	while (cin >> w >> h && (w || h)) {
		if (w < h)
			swap(w, h);

		myf d = min<myf>(h, w / (1 + PI));
		myf area = (d * d) / 4 * PI;
		myf vol = area * h;

		// d = min(h / PI, w * (8 / (3 * PI)));
		d = h / PI;
		area = (d * d) / 4 * PI;
		vol = max(vol, area * (w - d));

		cout << setprecision(3) << fixed;
		cout << vol << endl;
	}
	return 0;
}
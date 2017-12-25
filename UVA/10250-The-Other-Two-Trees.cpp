/*input
10 0 -10 0
10 0 -10 0
10 0 -10 0
1.4 2.3 53.2 -1.0
1.1 4.2 10.4 -1002.4
4  1 66 2
-1342 .1 -2.4 2.5
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 10250 - The Other Two Trees
	@link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1191
	@judge: Uva
	@idea: get the perpendicular with the same length intersecting from the middle point of the line
		proof: from triangles congruence that length of both connecting lines are equal and the angle between
		them is 90 for any such parallelogram
	@comments: very ambiguous statement
				no need for the printing impossible
				you should print any possible tree
*/

#include <bits/stdc++.h>
using namespace std;
typedef long double myf;

int main() {
	myf x1, y1, x2, y2;
	while (cin >> x1 >> y1 >> x2 >> y2) {
		cout << setprecision(10) << fixed;
		myf midx = (x1 + x2) / 2;
		myf midy = (y1 + y2) / 2;
		myf nx1 = -(y1 - midy) + midx;
		myf ny1 = (x1 - midx) + midy;
		myf nx2 = -(y2 - midy) + midx;
		myf ny2 = (x2 - midx) + midy;

		cout << nx1 << ' ' << ny1 << ' ' << nx2 << ' ' << ny2 << endl;
	}
	return 0;
}
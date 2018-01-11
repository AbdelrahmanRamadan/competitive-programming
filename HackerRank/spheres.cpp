/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: Spheres
	@link: https://www.hackerrank.com/challenges/spheres/problem
	@judge: HackerRank
	@idea: at time `t` the position of the sphere is equal to: a0 + integration(t * db) = a0 + t^2 * da / 2
		such that a0 is the initial position of the sphere and da is the acceleration vector
		so we want to find t such that:
			distance(a0 + t^2 * da / 2, b0 + t^2 * db / 2) <= R1 + R2
			= Sum{x, y, z} { (a0 + t^2 * da / 2 - b0 + t^2 * db / 2) ^ 2 } <= (R1 + R2) ^ 2
			assume: c0 = a0 - b0, cd = (da - db) / 2
			= Sum{x, y, z} { (c0 + cd * t^2) ^ 2 } <= (R1 + R2) ^ 2
			= Sum{x, y, z} { cd^2 * t^4 + 2 * c0 * cd * t^2 + c0^2 } <= (R1 + R2) ^ 2
			= Sum(cd^2) * t^4 + Sum(2*c0*cd) * t^2 + Sum(c0^2) - (R1 + R2) ^ 2 <= 0
		then solve the final equation using quadratic equations general rule 
*/

#include <bits/stdc++.h>
#define EPS 1e-9
typedef long double myf;
using namespace std;

int main() {
	int T;
	cin >> T;
	while (T--) {
		myf r1, r2, a0[3], da[3], b0[3], db[3];
		cin >> r1 >> r2;
		cin >> a0[0] >> a0[1] >> a0[2];
		cin >> da[0] >> da[1] >> da[2];

		cin >> b0[0] >> b0[1] >> b0[2];
		cin >> db[0] >> db[1] >> db[2];


		myf a = 0, b = 0, c =  - (r1 + r2) * (r1 + r2);
		myf c0 = 0, cd = 0;
		for (int i = 0; i < 3; ++i) {
			myf c0 = a0[i] - b0[i];
			myf cd = 0.5 * (da[i] - db[i]);
			a += cd * cd;
			b += 2 * c0 * cd;
			c += c0 * c0;
		}

		myf under_root = b * b - 4 * a * c;
		if (under_root < EPS) {
			cout << "NO" << endl;
			continue;
		}
		myf t1 = (-b + sqrt(under_root)) / (2 * a);
		myf t2 = (-b - sqrt(under_root)) / (2 * a);
		cout << (max(t1, t2) < EPS ? "NO" : "YES") << endl;
	}
	return 0;
}
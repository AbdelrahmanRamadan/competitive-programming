/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 10297 - Beavergnaw
	@link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1238
	@judge: UVA
	@idea: assuming
	* Cy(x) is the volume of a cylender with the base diameter x and hight x 
		Cy(x) = pi * x^3 / 4
	* Co(x) is the volume of a cone with the base diameter x and hight x
		Co(x) = pi * x^3 / 24
	
	Note -> cone area could be easily derived from circle area rule (pi * r^2) using integration since
	regular cone(hight equal diameter) area = integration{0 -> x/2}(pi * r^2) = pi * x^3 / 24

	Then
	cy(D) = pi * D^3 / 4;
	co(D) = pi * D^3 / 24;
	V = cy(D) - 2 * co(D) - cy(d) + 2 * co(d)
	V = pi * D^3 / 4 - pi * D^3 / 12 - pi * d^3 / 4 + pi * d^3 / 12
	V = D^3 * (pi / 4 - pi / 12) - d^3 * (pi / 4 - pi / 12)
	d^3 = (D^3 * (pi / 4 - pi / 12) - V) / (pi / 4 - pi / 12)
	d = cbrt(d^3)
	
*/

#include <bits/stdc++.h>
using namespace std;
const long double pi = acos(-1);

int main() {
	long double D, V;
	while (cin >> D >> V && (D > 1e-9 || V > 1e-9)) {
		cout << setprecision(3) << fixed;
		cout << cbrt((D * D * D * (pi / 4 - pi / 12) - V) / (pi / 4 - pi / 12)) << endl;
	}
	return 0;
}
/*input
1
1 1
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem:
	@link:
	@judge:
	@idea:
		Assume Rl is the small radius and Rs is the large raduis.
	
		Volume of the intersection of two cylinders is the sum (integration) of all inner cylinders surface area
		in the small cylinder
		so if the inner cylinder radius in the current moment is t then its length:
			len = 2 * sqrt(Rl^2 - t^2)
			surface_area = len * 2 * PI * t
		
		and the total intersection volume = integration(surface_area) (0 <= t <= Rs)
									= 4 * PI / 3 * Rs^3 * (Rl^2 - Rs^2)^(3/2) / Rs / (Rl^2 - 2 * Rs^2) 
*/

#include <bits/stdc++.h>
typedef long double myf;
using namespace std;

const myf PI = acos(-1);

inline myf sqr(myf x) {
	return x * x;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		myf Rs, Rl;
		cin >> Rs >> Rl;
		if (Rs > Rl)
			swap(Rs, Rl);

		myf d = sqr(Rl) - sqr(Rs);
		myf vo1 = -1.0L / 3 * sqr(sqr(Rl) - sqr(Rs)) * sqrt(Rl * 4 * PI;
		myf vo2 = -1.0L / 3 * sqr(Rl) * Rl * 4 * PI;
		// myf vol1 = 4 * PI / 3 * sqr(Rs) * Rs * d * sqrt(d) / Rs / (sqr(Rl) - 2 * sqr(Rs));
		// myf vol2 = 4 * PI / 3 * sqr(Rs) * Rs * d * sqrt(d) / Rs / (sqr(Rl) - 2 * sqr(Rs));
		cout << setprecision(4) << fixed;
		cout << vol << endl;
		if (T)
			cout << endl;
	}
	return 0;
}
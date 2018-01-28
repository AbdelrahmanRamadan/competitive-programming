/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: 2395 - Jacquard Circuits
	@link: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=396
	@judge: LIVEARCHIVE
	@idea: get the origin polygon by dividing each edge over its lattice step (gcd(x, y)), then from picks theorem
		drive a closed form to represent the sum for all similar polygons from 1 to M as follows: 
	I = A - B / 2 + 1
	Sum(I) = Sum(A * i * i) - Sum(B / 2 * i) + M
			= A * Sum(i * i) - B / 2 * Sum(i) + M
	* such that i is an integer from 1 to m
	Sum(i) = m * (m + 1) / 2
	Sum(i * i) = m * (m + 1) * (2 * m + 1) / 6
	
	the frustrating thing about this problem is handling the overflow since the numbers will overflow in the
	unsigned long long before deviding them over 6, so you need to do a division over 2 first then check which factor
	should be divided over 3 before doing the result multiplication.
*/
#include <bits/stdc++.h>
#define X first
#define Y second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> point;

const int MAX = 1010;
point v[MAX], pnts[MAX];
int n;
ll m;
point vec(point a, point b) {
	return point({ b.X - a.X, b.Y - a.Y });
}

ll cross(point a, point b) {
	return a.X * b.Y - a.Y * b.X;
}

int main() {
	int T{};
	while (cin >> n >> m && n) {
		for (int i = 0; i < n; ++i)
			cin >> v[i].X >> v[i].Y;

		int sz = 0;

		for (int i = 0; i < n; ++i) {
			int j = (i + 1) % n;
			int k = (i - 1 + n) % n;
			if (cross(vec(v[i], v[j]), vec(v[i], v[k])))
				pnts[sz++] = v[i];
		}

		n = sz;
		ll g{}, B{}, A{};
		for (int i = 0; i < n; ++i) {
			int j = (i + 1) % n;
			point edge = vec(pnts[i], pnts[j]);
			ll temp = abs(__gcd(edge.X, edge.Y));
			g = __gcd(g, temp);
			B += temp;
			A += cross(pnts[i], pnts[j]);
		}

		A = abs(A) / g / g;
		B /= g;

		ull f1 = m * (m + 1) / 2;
		ull f2 = f1 * (m * 2 + 1);
		if (f2 % 3 == 0)
			f2 /= 3;
		else
			A /= 3;
		ull I = - (ull)f1 * B + m * 2 + (ull)f2 * A;
		cout << "Case " << ++T << ": "<< I / 2 << endl;
	}

	return 0;
}

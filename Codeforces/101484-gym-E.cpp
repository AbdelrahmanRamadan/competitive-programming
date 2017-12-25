/*input
3 3
2 1
5 1
2 -1
-3 1
0 1
0 -1
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: E. Double Fence
	@link: http://codeforces.com/gym/101484/problem/E
	@judge: Codeforces Gym
	@idea: calculate the convex hull of all the points (points of the two polygons together),
		then check if it equals any of the two polygons.
		Include all collinear points when calculating the convex hull
*/

#include <bits/stdc++.h>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> point;
const int MAX = 100100;

int n, m;

inline point vec(point a, point b) {
	return point({ b.X - a.X, b.Y - a.Y });
}

inline long long cross(point a, point b) {
	return 1LL * a.X * b.Y - 1LL * a.Y * b.X;
}

vector<point> convex_hull(vector<point> P)
{
	int n = P.size(), k = 0;
	vector<point> H(2 * n);
	sort(P.begin(), P.end());

	for (int i = 0; i < n; ++i){
		while (k >= 2 && cross(vec(H[k - 2], H[k - 1]), vec(H[k - 2], P[i])) < 0) --k;
		H[k++] = P[i];
	}

	for (int i = n - 2, t = k + 1; i >= 0; --i){
		while (k >= t && cross(vec(H[k - 2], H[k - 1]), vec(H[k - 2], P[i])) < 0) --k;
		H[k++] = P[i];
	}

	H.resize(--k);
	return H;
}

int main() {
	cin >> n >> m;
	vector<point> a(n), b(m), c(n + m);
	for (int i = 0; i < n; ++i) {
		cin >> a[i].X >> a[i].Y;
		c[i] = a[i];
	}
	for (int i = 0; i < m; ++i) {
		cin >> b[i].X >> b[i].Y;
		c[n + i] = b[i];
	}
	c = convex_hull(c);
	sort(c.begin(), c.end());
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	cout << ((c == a || c == b) ? "YES" : "NO") << endl;
	return 0;
}

/*input
*/
#include <bits/stdc++.h>
using namespace std;

struct point {
	int X, Y;
	bool operator == (const point& o) const {
		return X == o.X && Y == o.Y;
	}
	bool operator < (const point& o) const {
		return X < o.X || (X == o.X && Y < o.Y);
	}
};

int fix(vector<point>& v) {
	reverse(v.begin(), v.end());
	rotate(v.begin(), min_element(v.begin(), v.end()), v.end());
	return max_element(v.begin(), v.end()) - v.begin();
}

long long cross3(const point& o, const point& a, const point& b) {
	return 1LL * (a.X - o.X) * (b.Y - o.Y) - 1LL * (a.Y - o.Y) * (b.X - o.X);
}

int sign(long long c) {
	return c < 0 ? -1 : c > 0 ? 1 : 0;
}

int in_poly(const vector<point>& v, point p, int top) {
	if (p < v[0] || v[top] < p) return 1;
	int orient = sign(cross3(v[0], v[top], p));
	if (orient == 0) {
		if (p == v[0] || p == v[top]) return 0;
		return top == 1 || top + 1 == v.size() ? 0 : -1;
	} else if (orient < 0) {
		auto itr = lower_bound(v.begin() + 1, v.begin() + top, p);
		return sign(cross3(itr[-1], p, itr[0]));
	}
	auto itl = upper_bound(v.rbegin(), v.rend() - top - 1, p);
	return sign(cross3(itl[0], p, itl == v.rbegin() ? v[0] : itl[-1]));
}

int main() {
	int n, m;
	scanf("%d", &n);
	vector<point> v(n);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", &v[i].X, &v[i].Y);
	int top = fix(v);
	scanf("%d", &m);
	bool ok = 1;
	for (int i = 0; i < n; ++i) {
		point p;
		scanf("%d%d", &p.X, &p.Y);
		if (in_poly(v, p, top) >= 0) ok = 0;
	}
	cout << (ok ? "YES" : "NO");
	return 0;
}
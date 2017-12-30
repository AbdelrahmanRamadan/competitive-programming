/*input
4 4
1 1
1 -1
-1 -1
-1 1
2 2
2 -2
-2 -2
-2 2
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
	int sz[2];
	scanf("%d%d", sz, sz + 1);
	vector<point> v[2];
	for (int i = 0; i < 2; ++i) {
		v[i].resize(sz[i]);
		for (int j = 0; j < sz[i]; ++j)
			scanf("%d%d", &v[i][j].X, &v[i][j].Y);
	}
	for (int i = 0; i < 2; ++i) {
		int j = (i + 1) % 2;
		int top = fix(v[i]);
		bool ok = 1;
		for (int k = 0; k < sz[j]; ++k)
			if (in_poly(v[i], v[j][k], top) >= 0) ok = 0;
		if (ok)
			return puts("YES"), 0;
	}
	puts("NO");
	return 0;
}
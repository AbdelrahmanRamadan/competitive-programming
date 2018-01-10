#include <bits/stdc++.h>
#define st first
#define en second
#define X first
#define Y second
#define all(v) v.begin(), v.end()
using namespace std;
typedef pair<int, int> point;
typedef pair<point, point> segment;
const int MAX = 550;
int n;

istream& operator >> (istream& fin, point& o) {
	fin >> o.X >> o.Y;
	return fin;
}
istream& operator >> (istream& fin, segment& o) {
	fin >> o.st >> o.en;
	if (o.st > o.en)
		swap(o.st, o.en);
	return fin;
}

bool intersect(segment a, segment b, point& p) {
	if ((a.st.X == a.en.X) == (b.st.X == b.en.X))
		return false;
	if (a.st.X != a.en.X)
		swap(a, b);
	p = { a.st.X, b.st.Y };
	return p >= a.st && p <= a.en && p >= b.st && p <= b.en;
}

void fix(vector<point>& v) {
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
}

int main() {
	while (cin >> n && n) {
		map<point, vector<point> > mp;
		vector<segment> segs(n);
		for (int i = 0; i < n; ++i)
			cin >> segs[i];

		for (auto& u : segs) {
			vector<point> in({ u.st, u.en });
			for (auto& v : segs) {
				point p;
				if (intersect(u, v, p))
					in.push_back(p);
			}
			sort(all(in));
			in.resize(unique(all(in)) - in.begin());
			for (int i = 1, len = in.size(); i < len; ++i)
				mp[in[i]].push_back(in[i - 1]);
		}

		vector<segments> rects;

		for (auto& p : mp) {
			auto &v = p.se;
			fix(v);
			if (v.size() > 1) {
				auto &v0 = mp[v[0]];
				auto &v1 = mp[v[1]];
				fix(v0);
				fix(v1);
				if (v0.size() > 1 && v1.size() > 1 && v0[1] == v1[0])
					rects.push_back({ p.fi, v0[1] });
			}
		}

	}
	return 0;
}
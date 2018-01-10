/*input
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem:
	@link:
	@judge:
	@idea:
*/

#include <bits/stdc++.h>
#define EPS 1e-10
using namespace std;
typedef long double myf;
const int MAX = 10050;
struct point {
	myf X, Y, Z;
	friend istream& operator >> (istream& fin, point& o) {
		fin >> o.X >> o.Y >> o.Z;
		return fin;
	}
	friend ostream& operator << (ostream& fout, const point& o) {
		fout << o.X << ' ' << o.Y << ' ' << o.Z;
		return fout;
	}
	point operator / (myf sc) const {
		return point({ X / sc, Y / sc, Z / sc });
	}
	point operator * (myf sc) const {
		return point({ X * sc, Y * sc, Z * sc });
	}
	point operator + (const point& o) const {
		return point({ X + o.X, Y + o.Y, Z + o.Z });
	}
} pnts[MAX], st;
int n;
myf vp, vs;

point vec(const point& a, const point& b) {
	return point({ b.X - a.X, b.Y - a.Y, b.Z - a.Z });
}

myf dist(const point& v) {
	return sqrtl(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
}



int main() {
	cin >> n;
	for (int i = 0; i <= n; ++i)
		cin >> pnts[i];
	cin >> vp >> vs >> st;
	myf t0 = 0;
	for (int i = 1; i <= n; ++i) {
		myf ct = dist(vec(pnts[i - 1], pnts[i])) / vs;
		if (dist(vec(pnts[i], st)) / vp <= t0 + ct + EPS) {
			cout << "YES" << endl;
			point unit = vec(pnts[i - 1], pnts[i]) / ct;
			myf low = 0, high = ct;
			while (fabs(high - low) > EPS) {	
				myf mid = (low + high) * 0.5L;
				if (dist(vec(unit * mid + pnts[i - 1], st)) / vp <= t0 + mid + EPS)
					high = mid;
				else
					low = mid;
			}
			cout << setprecision(11) << fixed;
			cout << t0 + high << endl;
			cout << unit * high + pnts[i - 1] << endl;
			return 0;
		}
		t0 += ct;
	}
	cout << "NO" << endl;
	return 0;
}
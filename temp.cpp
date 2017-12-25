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
#define EPS 1e-9
#define X real()
#define Y imag()
#define rotate(v,theta) ((v)*polar(1.0L,theta))
#define polar(len,theta) (point(cosl(theta),sinl(theta))*(len))
using namespace std;
typedef long double myf;
typedef complex<myf> point;
const myf OO = 1e17;

inline myf cross(const point& A, const point& B) {
	return A.X * B.Y - B.X * A.Y;
}

inline point vec(point a, point b) {
	return b - a;
}

inline myf dist(point a) {
	return sqrtl(a.X * a.X + a.Y * a.Y);
}

inline point unit(point a) {
	return a / dist(a);
}

// bool operator < (const point& a, const point& b) {
// 	return a.X + EPS < b.X || (a.X - b.X < EPS && a.Y + EPS < b.Y);
// }

bool operator == (const point& a, const point& b) {
	return fabs(a.X - b.X) < EPS && fabs(a.Y - b.Y) < EPS;
}

myf cosRule(myf a, myf b, myf c){
	return acosl((a * a + b * b - c * c) / (2 * a * b));
}

int circleCircleIntersection(const point &c1, const myf &r1, const point &c2, const myf &r2, point &res1, point &res2){
	// 3awza ttzabat fel-library
	if(c1 == c2 && fabs(r1 - r2) < EPS){
		res1 = res2 = c1;
		return fabs(r1) < EPS ? 1 : OO;
	}
	myf len = dist(vec(c1, c2));
	if (fabs(len - (r1 + r2)) < EPS || fabs(fabs(r1 - r2) - len) < EPS){
		point d, c;
		myf r;
		if (r1 > r2)
			d = vec(c1,c2), c = c1, r = r1;
		else
			d = vec(c2,c1), c = c2, r = r2;
		res1 = res2 = unit(d) * r + c;
		return 1;
	}
	if (len > r1 + r2 || len < fabs(r1 - r2))
		return 0;
	myf a = cosRule(r1, len, r2);
	point c1c2 = unit(vec(c1,c2)) * r1;
	res1 = rotate(c1c2, a) + c1;
	res2 = rotate(c1c2, -a) + c1;
	return 2;
}

int main() {
	
	return 0;
}
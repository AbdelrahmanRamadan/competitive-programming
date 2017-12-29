/*input
1
0 2
width=300
height=500
2
1 width
1 Width
*/
/*
	@author: Abdelrahman Ramadan
	@email: abdelrahman0xff@gmail.com
	@repo: https://github.com/AbdelrahmanRamadan/competitive-programming
	@problem: C. Component Tree
	@link: http://codeforces.com/gym/100513/problem/C
	@judge: Codeforces Gym
	@idea:
*/

#include <bits/stdc++.h>
#define X real()
#define Y imag()
#define EPS 1e-9
using namespace std;
typedef long double myf;
typedef complex<myf> point;
const myf PI = acos(-1.0L);

/*

			deg		getAngle	asin	acos	atan		atan2
(1, 0)		0		0 | 2PI		0		0		0			0
(1, 1)		45		PI/4		PI/4	PI/4	PI/4		PI/4
(0, 1)		90		PI/2		PI/2	PI/2	(-|+)PI/2	PI/2
(-1, 1)		135		3PI/4		PI/4	3PI/4	-PI/4		3PI/4
(-1, 0)		180		PI			0		PI		0			(-|+)PI
(-1,-1)		225		5PI/4		-PI/4	3PI/4	PI/4		-3PI/4
(0, -1)		270		3PI/2		-PI/2	PI/2	(-|+)PI/2	-PI/2
(1, -1)		315		7PI/4		-PI/4	PI/4	-PI/4		-PI/4
(1, 0)		360		2PI | 0		0		0		0			0
*/

myf getAngle(myf x, myf y) {
	// returns ccw angle starting from 0 in the range 0 to 2 * PI
	myf theta = atan2(y, x);
	if (theta < -EPS)
		theta += 2 * PI;
	return theta;
}

inline myf cross(const point& a, const point& b) {
	return a.X * b.Y - a.Y * b.X;
}

// wn_PnPoly(): winding number test for a point in a polygon
//      Input:   P = a point,
//               V[] = vertex points of a polygon V[n+1] with V[n]=V[0]
//      Return:  wn = the winding number (=0 only when P is outside), undefined when point on boundry
int in_poly(const vector<point>& v, point p) {
	// check if point is on boundry before calling this function
	int wn = 0;
	for (int i = 0, len = v.size(); i < len; ++i) {
		int j = i == (len - 1) ? 0 : (i + 1);
		if (v[i].Y <= p.Y + EPS)
			wn += (v[j].Y > p.Y + EPS) && cross(v[j] - v[i], p - v[i]) > EPS;
		else
			wn -= (v[j].Y <= p.Y + EPS) && cross(v[j] - v[i], p - v[i]) < EPS;
	}
	return wn;
}

int main() {
	cout << fmod(10.3, 3) << endl;
	return 0;
}
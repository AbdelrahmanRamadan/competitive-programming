/*input
3
2 6 3
4
1 1 2 2
1 1 3 3
2 1 9
1 1 3 2
*/
#include <bits/stdc++.h>
#define leftNode (root << 1)
#define rightNode (leftNode | 1)
#define midRange ((st + en) >> 1)
#define goLeft st, midRange, leftNode
#define goRight midRange + 1, en, rightNode
#define fi first
#define se second
using namespace std;
typedef long double myf;
typedef pair<int, int> pii;

const int LG = 20;
const int MAX = 1 << LG;
int seg[MAX * 2], n;

int build(int st = 1, int en = n, int root = 1) {
	if (st == en) {
		scanf("%d", &seg[root]);
		return seg[root];
	}
	seg[root] = build(goLeft);
	return seg[root] = __gcd(seg[root], build(goRight));
}
int update(int x, int val, int st = 1, int en = n, int root = 1) {
	if (st > x || en < x)
		return seg[root];
	if (st == en)
		return seg[root] = val;
	return seg[root] = __gcd(update(x, val, goLeft), update(x, val, goRight));
}
int cnt = 0;
int query(int l, int r, int val, int st = 1, int en = n, int root = 1) {
	if (st > r || en < l)
		return 0;
	if (st >= l && en <= r) {
		if (st == en)
			return seg[root] % val != 0;
		if (seg[leftNode] % val != 0) {
			if (seg[rightNode] % val != 0)
				return 2;
			return query(l, r, val, goLeft);
		} else if (seg[rightNode] % val != 0) {
			return query(l, r, val, goRight);
		}
		return 0;
	}
	return query(l, r, val, goLeft) + query(l, r, val, goRight);
}

int main() {
	scanf("%d", &n);
	build();
	int q;
	scanf("%d", &q);
	while (q--) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			int l, r, x;
			scanf("%d%d%d", &l, &r, &x);
			puts(query(l, r, x) <= 1 ? "YES" : "NO");
		} else {
			int i, val;
			scanf("%d%d", &i, &val);
			update(i, val);
		}
	}
	return 0;
}
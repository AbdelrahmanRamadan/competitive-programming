/*input
1
18 0
*/
/*
    @author: Abdelrahman Ramadan
    @email: abdelrahman0xff@gmail.com
    @repo: https://github.com/AbdelrahmanRamadan/competitive-programming
    @problem: Circle City
    @link: https://www.hackerrank.com/challenges/circle-city/problem
    @judge: HackerRank
    @idea: optimized brute force (loop over all points on one axis and calculate the other access by Pythagorean Theorem)
*/

#include <bits/stdc++.h>
using namespace std;
const int SQRT = 44722;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    unordered_set<int> vis;
    for (int i = 0; i < SQRT; ++i)
        vis.insert(i * i); 
    
    int T;
    cin >> T;
    while (T--) {
        int d, k;
        cin >> d >> k;
        int lim = sqrt(d) + 1e-9;
        int lim2 = sqrt(d / 2) + 1e-9;
        k -= (lim * lim == d) * 4;
        k -= (lim2 * lim2 == d - lim2 * lim2) * 4;
        for (int x = 1; x * x < d - x * x; ++x)
            if (vis.count(d - x * x))
                k -= 8;
        cout << (k < 0 ? "impossible" : "possible") << endl;
    }
    return 0;
}

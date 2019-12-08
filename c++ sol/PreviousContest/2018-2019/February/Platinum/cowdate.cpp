/*
	This was the easiest plat problem all year lol. Hold two arrays, p and f. Let p[i] equal the probability of exactly one
of the first i cows accepting her invitation, and f[i] be the product of (1 - the jth probability given) for all j <= i. Now,
the probability of exactly one cow accepting the invitation in a range from l to i using the arrays stated previously is
(p[i] - p[l] * f[i] / f[l]) / f[l]. This is because you need the sum of (1 - pl) * ... * pk * ... (1 - pi) for all k, so you are
subtracting out all cases from p[i] such that k is before l, then you are dividing by the (1 - p) values that are less than l.
Now, you can solve this problem with 2 pointers by iterating through all values of i from 1 to n and seeing if it is optimal
to increase the value of l, as the probability will always be a concave function for a set i value and it is never optimal to
move l back when iterating i forward. This gives a time complexity of O(n).
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	freopen("cowdate.in", "r", stdin);
	freopen("cowdate.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	n++;
	long double ret = 0;
	long double p[n], f[n];
	p[0] = 0, f[0] = 1;
	
	int l = 0;
	for(int i = 1; i < n; i++){
		cin >> p[i];
		
		p[i] /= 1e6;
		f[i] = 1 - p[i];
		
		p[i] = p[i - 1] * f[i] + p[i] * f[i - 1];
		f[i] *= f[i - 1];
		
		while((p[i] - p[l] * f[i] / f[l]) / f[l] <= (p[i] - p[l + 1] * f[i] / f[l + 1]) / f[l + 1]){
			l++;
		}
		ret = max(ret, (p[i] - p[l] * f[i] / f[l]) / f[l]);
	}
	
	cout << (int)(ret * 1e6) << endl;

	return 0;
}

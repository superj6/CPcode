/*
	The first thing to realize for this problem is, after allocating one cow to 
each building, you need to greedily set the the cow to whichever building will make
it cause the most change. To do this, if you let the current number of cows currently
on a property a[i] be z, the change when adding one more cow is a[i] / z - a[i] / (z + 1)
which is equal to a[i] / (z * (z + 1)). However, because k is large, you cannot just find
the k best changes one at a time. Instead you can binary search on on what the minimum
final change is for each property such that it is more than x. This is because you want
to greedily choose them so they will all be as close to the minimum value as possible,
and as the final change decreases more cows will be needed, so for the binary search
you can see if the amount of cows used is greater than or equal to k and calculate
the answer used so far. Lastly for the answer, you need to adjust it by adding the
change added by the extra cows so you have the answer for exactly k. The complexity of
this is O(nlogk).
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'

long long n, k;
long long a[100000];
double ans;

long long solve(double x){
	long long ret = 0;
	for(int i = 0; i < n; i++){
		long long z = (long long)((sqrt(1 + 4 * a[i] / x) - 1) / 2);
		ans += 1.0 * a[i] / (z + 1);
		ret += z;
	}
	return ret;
}

int main(){
	freopen("tallbarn.in", "r", stdin);
	freopen("tallbarn.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	k -= n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	double l = 0, r = 1e18;
	
	for(int i = 0; i < 200; i++){
		double mid = l + (r - l) / 2;
		if(solve(mid) >= k) l = mid;
		else r = mid;
	}
	
	ans = 0;
	
	cout << (long long)round((solve(l) - k) * l + ans);

	return 0;
}

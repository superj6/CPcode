/*
  First I swap x and y. Realize that for an individual point, if you graph the distance traveled for a firework location as a function
of x, the result is a piecewise linear function with 4 or 6 segments depending on the value y, and each segment has a slope of 0, 1, 
or -1. If we can figure out these segments, we can do a line sweep holding the current sum of values for all locations and the sum of
slopes for all locations. Now you just sort all locations where the slope changes for each point and record how it changes, then when
you sweep you only update the sum of slopes at those locations, update the sum of values based on distance * sum of slopes, and check
if the new sum of values is the best result. You can find the points where each individual location's function's slope changes with
simple casework.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 500000;
ll n, m, k, s;
pi a[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++){
		int x, y;
		cin >> y >> x;
		s += (y *= 2 * (y > 0) - 1);
		
		a[m++] = {x, 2};
		if(y < k){
			a[m++] = {x - k, 1}, a[m++] = {x + k, 1};
			a[m++] = {x - y, -2}, a[m++] = {x + y, -2};
		}else{
			a[m++] = {x - y, -1}, a[m++] = {x + y, -1};
		}
	}
	
	sort(a, a + m);
	
	ll ret = s;
	for(ll i = 1, j = a[0].s; i < m; j += a[i++].s){
		ret = min(ret, s += j * (a[i].f - a[i - 1].f));
	}
	
	cout << ret << endl;

	return 0;
}

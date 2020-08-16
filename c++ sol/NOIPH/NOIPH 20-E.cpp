/*
	Compute sequence given in problem along with where the position of the last element is of each value. The optimal queueing
will always pair as many x with 2 * x as possible, because the limiting amount of a value is always the lower one except for possibly
at the endpoints. You can binary for the value of the endpoints and just iterate through all of them for 65 points.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const ll n = 1000001;
ll x, y, fx, fy;
ll a[n + 1], b[n];

ll f(int v){
	return v == fx ? b[fx] - x + 1 : v == fy ? y - b[fy - 1] : a[v] + a[v + 1]; 
}

void answer(){
	cin >> x >> y;
	
	fx = lower_bound(b, b + n, x) - b;
	fy = lower_bound(b, b + n, y) - b;
	
	ll ret = 1;
	for(int i = fy >> 1; i >= fx; i--){
		ret += min(f(i), f(i << 1));
	}
	ret = y - x + 1 - ret;
	
	cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	a[1] = a[2] = 1, b[1] = a[3] = 2;
	for(int i = 2; i < n; i++){
		b[i] = b[i - 1] + a[i] + a[i + 1];
		for(ll j = b[i - 1] + 1; j <= min(n, b[i]); j++) a[j] = i;
	}
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}

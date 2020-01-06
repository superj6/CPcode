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
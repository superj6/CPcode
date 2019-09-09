#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int n;
long long a[200000];

long long solve(long long x){
	long long ret = 0;
	for(int i = 0; i < n; i++) if(ret < 1000000007) ret += x / a[i];
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	long long t;
	cin >> n >> t;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	long long l = 0, r = 1000000000000000007;
	
	while(r - l > 1){
		long long mid = l + (r - l) / 2;
		if(solve(mid) >= t) r = mid;
		else l = mid;
	}
	
	cout << r << endl;

	return 0;
}
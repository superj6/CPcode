#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int n, k;
long a[200000];

bool works(long x){
	long amt = 0;
	for(long i = 0, cur = 0; i < n; i++){
		if(cur + a[i] > x){
			cur = 0;
			amt++;
			
			if(amt >= k || a[i] > x) return false;
		}
		
		cur += a[i];
	}
	
	return true;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	long l = 0, r = 200000000000000;
	
	while(r - l > 1){
		long mid = l + (r - l) / 2;
		if(works(mid)) r = mid;
		else l = mid;
	}
	
	cout << r << endl;

	return 0;
}
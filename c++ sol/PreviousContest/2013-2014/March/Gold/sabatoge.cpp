#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iomanip>
using namespace std;
#define endl '\n'

int n;
long a[100000];
long sum = 0;

bool works(long x){
	long maxv = a[1] - x, amt = 1;
	for(long i = 1, cur = 0, camt = 0; i < n - 1; i++){
		cur += a[i] - x;
		camt++;
		if(cur > maxv){
			maxv = cur;
			amt = camt;
		}
		if(cur < 0){
			cur = 0;
			camt = 0;
		}
	}
	
	return (sum - maxv - x * amt) / (n - amt) <= x;
}

int main(){
	freopen("sabotage.in", "r", stdin);
	freopen("sabotage.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << setprecision(3) << fixed;
	
	cin >> n;
	for(int i = 0; i < n; i++){
		 cin >> a[i];
		 a[i] *= 10000;
		 sum += a[i];
	}
	
	long l = 0, r = 100000000;
	
	while(r - l > 1){
		long mid = (l + r) / 2;
		if(works(mid)) r = mid;
		else l = mid;
	}
	
	cout << (r / 10000.0) << endl;

	return 0;
}
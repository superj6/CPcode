#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

long long n;

bool works(long long x){
	return x - x / 3 - x / 5 + x / 15 >= n;
}

int main(){
	freopen("moobuzz.in", "r", stdin);
	freopen("moobuzz.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	long long l = 0, r = 10000000000007;
	while(r - l > 1){
		long long mid = (l + r) / 2;
		if(works(mid)) r = mid;
		else l = mid;
	}
	
	cout << r << endl;

	return 0;
}
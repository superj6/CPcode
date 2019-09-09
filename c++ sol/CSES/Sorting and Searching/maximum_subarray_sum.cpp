#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	long long maxv = 0, cur = 0, maxs = -1000000007;
	
	for(int i = 0; i < n; i++){
		long long a;
		cin >> a;
		cur += a;
		if(cur < 0) cur = 0;
		
		maxv = max(maxv, cur);
		maxs = max(maxs, a);
	}
	
	if(maxs < 0) cout << maxs << endl;
	else cout << maxv << endl;

	return 0;
}
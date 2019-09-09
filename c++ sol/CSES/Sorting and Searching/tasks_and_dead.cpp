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
	
	pair<long long, long long> a[n];
	
	for(int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
	
	sort(a, a + n);
	
	long long t = 0, ret = 0;
	
	for(int i = 0; i < n; i++){
		t += a[i].first;
		ret += a[i].second - t;
	}
	
	cout << ret << endl;

	return 0;
}
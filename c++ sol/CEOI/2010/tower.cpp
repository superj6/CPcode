#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000009;
const int mxn = 1000000;
int n, k;
int a[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	sort(a, a + n);
	
	ll ret = 1;
	for(int i = 0, j = 0; i < n; i++){
		while(j < n && a[j] - a[i] <= k) j++;
		(ret *= j - i) %= mod;
	}
	
	cout << ret << endl;
	
	return 0;
}
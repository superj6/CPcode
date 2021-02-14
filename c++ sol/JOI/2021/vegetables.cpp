#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 200002;
int n;
ll a[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	ll ret = 0, l = 1, r = n;
	while(1){
		while(l <= n && a[l] > a[l - 1]) l++;
		while(r && a[r] > a[r + 1]) r--;
		if(l > r) break;
		ll x = min(a[l - 1] - a[l], a[r + 1] - a[r]) + 1;
		ret += x, a[l - 1] -= x, a[r + 1] -= x;
	}
	ret += l - 1 == r && a[l] == a[r];
	
	cout << ret << endl;
	
	return 0;
}
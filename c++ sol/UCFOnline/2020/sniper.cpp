#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100001;
int n, m;
ll a[mxn];

void answer(){
	cin >> n >> m;
	
	ll ret = 0;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		ret += a[i]; a[i] = a[i] / abs(a[i]) + a[i - 1];
	} 
	for(int i = 0; i < m; i++){
		int x;
		cin >> x;
		ret += max(0ll, a[x]);
	}
	
	cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}
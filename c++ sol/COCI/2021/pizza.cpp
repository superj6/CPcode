#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100;
int n, m;
int a[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	sort(a, a + n);
	
	cin >> m;
	
	int ret = 0;
	for(int i = 0; i < m; i++){
		int k, f = 1;
		cin >> k;
		for(int j = 0; j < k; j++){
			int x;
			cin >> x;
			int y = lower_bound(a, a + n, x) - a;
			f &= y == n || a[y] != x;
		}
		ret += f;
	}
	
	cout << ret << endl;
	
	return 0;
}
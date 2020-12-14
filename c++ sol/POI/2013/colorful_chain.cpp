#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 1000000;
int n, m;
int a[mxn], s[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++) cin >> a[i];
	for(int i = 0; i < m; i++){
		int x;
		cin >> x;
		s[--x] = a[i];
	}
	
	int ret = 0;
	for(int i = 0, j = 0; i < n; i ++){
		cin >> a[i];
		m -= !(--s[--a[i]]);
		while(!~s[a[i]]) m += !(s[a[j++]]++);
		ret += !m;
	}
	
	cout << ret << endl;

	return 0;
}
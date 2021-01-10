#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 200000;
int n;
int a[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	sort(a, a + n);
	
	ll ret = 1;
	for(int i = 0; i < n && a[i] <= ret; i++) ret += a[i];
	
	cout << ret << endl;

	return 0;
}
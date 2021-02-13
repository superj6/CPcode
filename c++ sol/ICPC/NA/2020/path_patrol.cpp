#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 500000;
int n;
ll a[mxn][2], b[mxn], d[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		cin >> a[i][0] >> a[i][1] >> b[i];
		for(int j = 0; j < 2; j++) d[--a[i][j]] += b[i];
	}
	
	ll ret = 1;
	for(int i = 0; i < n - 1; i++)
	for(int j = 0; j < 2; j++){
		ret += max(0ll, 2 * b[i] - d[a[i][j]]);
	}
	ret /= 2;
	
	cout << ret << endl;
	
	return 0;
}
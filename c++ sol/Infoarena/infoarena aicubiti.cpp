/*
  Realize problem is equivalent to finding all pairs such that the popcount of the xor is equal to 4. This means you can just use fast
walsh hadamard transform to find amount of pairs that xor to each value and only values to result if 4 bits are set.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int m = 1 << 20;
int n;
ll a[m];

void fwt(ll v[m], bool f = 0){
	for(int l = 1; l < m; l <<= 1)
	for(int i = 0; i < m; i += l << 1)
	for(int j = 0; j < l; j++){
		ll x = v[i + j], y = v[i + j + l];
		v[i + j] = x + y, v[i + j + l] = x - y;
	}
	if(f) for(int i = 0; i < m; i++) v[i] /= m;
}

int main(){
	freopen("aiacubiti.in", "r", stdin);
	freopen("aiacubiti.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		a[x]++;
	}
	
	fwt(a);
	for(int i = 0; i < m; i++) a[i] *= a[i];
	fwt(a, 1);
	
	ll ret = 0;
	for(int i = (1 << 4) - 1; i < m;){
		ret += a[i] / 2;
		int x = i & -i, y = i + x;
		i = y | ((i ^ y) / x >> 2);
	}
	
	cout << ret << endl;

	return 0;
}

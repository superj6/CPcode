#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 1 << 20;
int n, m, k;
ll a[maxn], b[maxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	b[0] = 1;
	for(int i = 1; i < n; i++) b[i] = b[i - 1] * k % m;
	
	//fft
	for(int i = 1, j = 0; i < n; i++){
		int l = n >> 1;
		for(; j & l; l >>= 1) j ^= l;
		j ^= l;
		if(i < j) swap(a[i], a[j]);
	}
	
	for(int l = 1; l < n; l <<= 1){
		ll wl = b[n / (l << 1)];
		for(int i = 0; i < n; i += l << 1){
			ll w = 1;
			for(int j = 0; j < l; j++){
				ll u = a[i + j], v = w * a[i + j + l] % m;
				a[i + j] = (u + v) % m, a[i + j + l] = (u + b[n / 2] * v % m) % m;
				w = w * wl % m;
			}
		}
	}
	//end fft
	
	ll ret = 0;
	for(int i = 0; i < n; i++) ret = (ret + a[i]) % m;
	
	cout << ret << endl;
	for(int i = 1; i < n; i++) cout << a[i] << " ";
	cout << a[0] << endl;

	return 0;
}
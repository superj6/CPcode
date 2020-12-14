#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007;
const int mxn = 1000000;
ll n, k;

ll ipow(ll x, ll y = mod - 2){
	ll ret = 1;
	for(; y; y >>= 1){
		if(y & 1) (ret *= x) %= mod;
		(x *= x) %= mod;
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	ll ret = 1, ik = ipow(k);
	for(int i = 0, j = k - 1; i < n; i++, j--) if(!j){
		(ret += ret * ik) %= mod;
		j = k - 1;
	} 
	
	cout << ret << endl;

	return 0;
}
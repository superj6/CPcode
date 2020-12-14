#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int mod = 1000000007;
const int maxk = 100000;
int n, m, k;
int a[maxk], b[maxk], c[maxk], it[maxk];

int solve(){
	sort(it, it + k, [&](int x, int y){
		return a[x] < a[y];
	});
	
	int p = n;
	for(int s = 0, e; s < k; p--, s = e){
		bool t[2] = {0, 0};
		for(e = s + 1; e < k && a[it[e]] == a[it[s]]; e++);
		for(int j = s, i; j < e; j++){
			i = it[j];
			t[(a[i] + b[i] + c[i]) & 1] = 1;
		}
		if(t[0] && t[1]) return 0;
	}
	long long ret = 1;
	for(long long b = 2; p; p >>= 1){
		if(p & 1) ret = (ret * b) % mod;
		b = (b * b) % mod;
	}
	return ret;
}

int solve2(){
	bool t[2] = {0, 0};
	for(int i = 0; i < k; i++){
		t[(a[i] + b[i] + c[i]) & 1] = 1;
	}
	return (mod - 1) * (t[0] != t[1]) + (mod - 2) * !k;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < k; i++){
		char x;
		cin >> x >> a[i] >> b[i];
		c[i] = x == '+';
		it[i] = i;
	}
	
	int ret = solve();
	swap(n, m);
	for(int i = 0; i < k; i++) swap(a[i], b[i]);
	ret += (solve() + solve2()) % mod;
	ret %= mod;
	
	cout << ret << endl;

	return 0;
}
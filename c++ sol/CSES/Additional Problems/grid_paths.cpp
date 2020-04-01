#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

const long long mod = 1000000007;
 
long long modpow(long long b, int e){
	long long ret = 1;
	for(int i = 0; (1 << i) <= e; i++){
		if((1 << i) & e) ret = (ret * b) % mod;
		b = (b * b) % mod;
	}
	return ret;
}

const int maxn = 2000000, maxm = 1001;
int n, m;
pi a[maxn];
long long f[maxn], rf[maxn], dp[maxn];

void init(){
	f[0] = rf[0] = 1;
	for(int i = 1; i < maxn; i++){
		f[i] = i * f[i - 1] % mod;
		rf[i] = modpow(f[i], mod - 2);
	}
}

long long C(int x, int y){
	return f[x] * rf[y] % mod * rf[x - y] % mod;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	init();
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		cin >> a[i].f >> a[i].s;
		a[i].f--, a[i].s--;
	}
	a[m++] = {n - 1, n - 1};
	
	sort(a, a + m, [&](pi x, pi y){
		return x.f + x.s < y.f + y.s;	
	});
	
	long long ret = 0;
	for(int i = 0; i < m; i++){
		dp[i] = C(a[i].f + a[i].s, a[i].f);
		for(int j = 0; j < i; j++){
			if(a[j].f <= a[i].f && a[j].s <= a[i].s){
				dp[i] += mod - dp[j] * C(a[i].f + a[i].s - a[j].f - a[j].s, a[i].f - a[j].f) % mod;
				dp[i] %= mod;
			}
		}
	}
	
	cout << dp[m - 1] << endl;

	return 0;
}
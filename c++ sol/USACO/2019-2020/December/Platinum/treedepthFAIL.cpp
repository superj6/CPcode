#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define vi vector<long long>

const int maxn = 301;
int n, k, m;
long long ans[maxn];
vi p[maxn], s[maxn];

vi operator *(vi a, vi b){
	vi ret = vi(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); i++)
	for(int j = 0; j < b.size(); j++){
		ret[i + j] += a[i] * b[j] % m;
		ret[i + j] %= m;
	}
	return ret;
}

int main(){
	freopen("treedepth.in", "r", stdin);
	freopen("treedepth.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k >> m;
	
	p[0] = vi(1, 1);
	for(int i = 1; i < n; i++) p[i] = vi(i + 1, 1) * p[i - 1];
	s[n] = vi(1, 1);
	for(int i = n - 1; i >= 0; i--) s[i] = vi(i + 1, 1) * s[i + 1];
	
	ans[0] += p[n - 1][k];
	ans[0] %= m;
	for(int i = 1; i < n; i++){
		ans[i] += p[n - 1][k];
		ans[i] %= m;
		vi cur = p[i - 1] * s[i + 1];
		for(int j = 0; j < n - i; j++){
			if(k - i >= 0) ans[j] += cur[k - i];
			ans[j] %= m;
			ans[j + i] += cur[k];
			ans[j + i] %= m;
		}
	}
	
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}
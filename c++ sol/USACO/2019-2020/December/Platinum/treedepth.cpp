#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define vi vector<int>

const int maxn = 300;
int n, k, m;
vi p;
long long ans[maxn];

void add(vi &a, int b){
	a.resize(a.size() + b - 1);
	for(int i = a.size() - 1; i >= 0; i--) a[i + b] = (m + a[i + b] - a[i]) % m;
	for(int i = 1; i < a.size(); i++) a[i] = (a[i] + a[i - 1]) % m; 
}

void sub(vi &a, int b){
	for(int i = a.size() - 1; i >= 1; i--) a[i] = (m + a[i] - a[i - 1]) % m;
	for(int i = 0; i < a.size() - b; i++) a[i + b] = (a[i + b] + a[i]) % m; 
	a.resize(a.size() - b + 1);
}

int main(){
	freopen("treedepth.in", "r", stdin); 
	freopen("treedepth.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k >> m;
	
	p = {1};
	for(int i = 1; i <= n; i++) add(p, i);
	
	ans[0] += p[k];
	ans[0] %= m;
	for(int i = 1; i < n; i++){
		ans[i] += p[k];
		ans[i] %= m;
		sub(p, i + 1);
		for(int j = 0; j < n - i; j++){
			if(k - i >= 0) ans[j] += p[k - i];
			ans[j] %= m;
			ans[j + i] += p[k];
			ans[j + i] %= m;
		}
		add(p, i + 1);
	}
	
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}
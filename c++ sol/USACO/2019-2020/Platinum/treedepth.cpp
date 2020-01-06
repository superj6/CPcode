#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 8;
long long n, k, m;
int a[maxn];
long long ans[maxn];

void recur(int l, int r, int d){
	if(l > r) return;
	int it = l;
	for(int i = l; i <= r; i++) if(a[i] < a[it]) it = i;
	ans[it] += d;
	recur(l, it - 1, d + 1);
	recur(it + 1, r, d + 1);
}

void solve(){
	int cnt = 0;
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			cnt += a[i] > a[j];
		}
	}
	if(cnt != k) return;
	recur(0, n - 1, 1);
}

int main(){
	freopen("treedepth.in", "r", stdin);
	freopen("treedepth.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k >> m;
	
	for(int i = 0; i < n; i++) a[i] = i;
	
	do{
		solve();
	}while(next_permutation(a, a + n));
	
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}
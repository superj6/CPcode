#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<int, pi>
#define f first
#define s second
#define sq(x) ((x) * (x))

const int mxn = 2000, mxm = 100000, k = 4;
int n, m, w[2];
int a[mxn][2], r[mxn];
int par[mxn + k], rnk[mxn + k];
vector<pii> v;
bool ans[mxm][k];

int fnd(int x){
	return x == par[x] ? x : par[x] = fnd(par[x]);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i = 0; i < 2; i++) cin >> w[i];
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 2; j++) cin >> a[i][j];
		cin >> r[i];
		par[i] = i;
		
		for(int j = 0; j < i; j++){
			ll d = 0;
			for(int l = 0; l < 2; l++) d += sq((ll)a[i][l] - a[j][l]);
			v.push_back({(int)sqrtl(d) - r[i] - r[j], {j, i}});
		}
		
		for(int j = 0; j < 2; j++)
		for(int l = 0; l < 2; l++){
			v.push_back({abs(l * w[j] - a[i][j]) - r[i], {i, n + j + 2 * l}});
		}
	}
	for(int i = 0; i < k; i++) par[n + i] = n + i;
	
	for(int i = 0; i < m; i++){
		int qr, x;
		cin >> qr >> x;
		v.push_back({2 * qr, {-x, i}});
	}
	
	sort(v.begin(), v.end());
	
	for(pii i : v){
		if(i.s.f < 0){
			for(int x[2] = {-i.s.f - 1, 0}; x[1] < k; x[1]++){
				ans[i.s.s][x[1]] = 1;
				if(x[0] == x[1]) continue;
				for(int j = 0; j < 2; j++){
					ans[i.s.s][x[1]] &= fnd(n + x[j]) != fnd(n + (x[j] + 1) % k);
					ans[i.s.s][x[1]] &= (k + x[1] - x[0]) % k == 1 + 2 * j || 
						fnd(n + (x[0] + j) % k) != fnd(n + (x[0] + j + 2) % k);
				}
			}
		}else{
			int x = fnd(i.s.f), y = fnd(i.s.s);
			if(x != y){
				if(rnk[x] < rnk[y]) swap(x, y);
				rnk[x] += rnk[x] == rnk[y];
				par[y] = x;
			}
		}
	}
	
	for(int i = 0; i < m; i++){
		string ret;
		for(int j = 0; j < k; j++) if(ans[i][j]) ret += '1' + j;
		cout << ret << endl;
	}

	return 0;
}
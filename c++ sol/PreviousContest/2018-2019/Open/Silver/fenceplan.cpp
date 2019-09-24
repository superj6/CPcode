#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n, m;
int rnk[maxn], par[maxn];
int mx[maxn], my[maxn], mX[maxn], mY[maxn];

int find(int x){
	return x == par[x] ? x : par[x] = find(par[x]);
}

void unionf(int x, int y){
	x = find(x), y = find(y);
	if(x == y) return;
	
	if(rnk[x] < rnk[y]) swap(x, y);
	if(rnk[x] == rnk[y]) rnk[x]++;
	par[y] = x;
	mx[x] = min(mx[x], mx[y]);
	my[x] = min(my[x], my[y]);
	mX[x] = max(mX[x], mX[y]);
	mY[x] = max(mY[x], mY[y]);
}

int main(){
	freopen("fenceplan.in", "r", stdin);
	freopen("fenceplan.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		cin >> mx[i] >> my[i];
		mX[i] = mx[i];
		mY[i] = my[i];
		par[i] = i;
	} 
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		unionf(a, b);
	}
	
	int best = 1e9;
	for(int i = 0; i < n; i++){
		int c = find(i);
		best = min(best, 2 * (mX[c] + mY[c] - mx[c] - my[c]));
	}
	
	cout << best << endl;

	return 0;
}
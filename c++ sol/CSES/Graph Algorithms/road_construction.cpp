#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const int maxn = 100000, maxm = 200000;
int n, m;
int par[maxn], rnk[maxn], sz[maxn];
pair<int, pair<int, int>> edges[maxm];

int find(int x){
	return par[x] == x ? x : find(par[x]);
}

void unionf(int x, int y){
	if(rnk[x] < rnk[y]) swap(x, y);
	if(rnk[x] == rnk[y]) rnk[x]++;
	par[y] = x;
	sz[x] += sz[y];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++) par[i] = i, sz[i] = 1;
	
	int amt = n, maxv = 1;
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		a = find(a), b = find(b);
		
		if(a != b){
			unionf(a, b);
			
			amt--;
			maxv = max(maxv, sz[find(a)]);
		}
		
		cout << amt << " " << maxv << endl;
	}

	return 0;
}
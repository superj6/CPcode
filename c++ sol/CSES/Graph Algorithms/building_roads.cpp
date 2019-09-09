#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 100000;
int par[maxn], rnk[maxn];
bool vis[maxn];
vector<int> road;

int find(int x){
	return par[x] == x ? x : find(par[x]);
}

void unionf(int x, int y){
	if(rnk[x] < rnk[y]) swap(x, y);
	else if(rnk[x] == rnk[y]) rnk[x]++;
	
	par[y] = x;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		par[i] = i;
		rnk[i] = 0;
		vis[i] = 0;
	}
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		a = find(a), b = find(b);
		
		if(a != b){
			unionf(a, b);
		}
	}
	
	for(int i = 0; i < n; i++) vis[find(i)] = 1;
	
	for(int i = 0; i < n; i++) if(vis[i]) road.push_back(i + 1);
	
	cout << road.size() - 1 << endl;
	
	for(int i = 1; i < road.size(); i++){
		cout << road[0] << " " << road[i] << endl;
	}

	return 0;
}
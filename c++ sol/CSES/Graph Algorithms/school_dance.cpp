#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'

const int maxn = 500;
int n, m, k;
int was[maxn];
int pa[maxn], pb[maxn];
vector<int> g[maxn];
int it = 0;

bool dfs(int c){
	was[c] = it;
	
	for(int i : g[c]){
		if(pb[i] == -1){
			pa[c] = i;
			pb[i] = c;
			return 1;
		}
	}
	
	for(int i : g[c]){
		if(was[pb[i]] != it && dfs(pb[i])){
			pa[c] = i;
			pb[i] = c;
			return 1;
		}
	}
	
	return 0;
}

int solve(){
	int ret = 0, add;
	memset(pa, -1, sizeof(pa));
	memset(pb, -1, sizeof(pb));
	
	do{
		add = 0;
		it++;
		
		for(int i = 0; i < n; i++){
			if(pa[i] == -1 && dfs(i)) add++;
		}
		
		ret += add;
	} while(add);
	
	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < k; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		g[a].push_back(b);
	}
	
	cout << solve() << endl;
	
	for(int i = 0; i < n; i++){
		if(pa[i] != -1) cout << i + 1 << " " << pa[i] + 1 << endl;	
	}
	
	return 0;
}
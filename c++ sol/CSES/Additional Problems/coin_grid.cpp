#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define f first
#define s second
 
const int maxn = 100;
int n;
int was[maxn], pa[maxn], pb[maxn];
bool h[2][maxn];
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

void dfs2(int c){
	h[0][c] = 1;
	for(int i : g[c]){
		if(!h[1][i]){
			h[1][i] = 1;
			dfs2(pb[i]);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		char c;
		cin >> c;
		if(c == 'o') g[i].push_back(j);
	}
	
	cout << solve() << endl;
	
	for(int i = 0; i < n; i++){
		if(pa[i] == -1 && !h[0][i]) dfs2(i);
	}
	
	for(int t = 0; t < 2; t++)
	for(int i = 0; i < n; i++){
		if(!t ^ h[t][i]) cout << t + 1 << " " << i + 1 << endl;
	}
	
	return 0;
}
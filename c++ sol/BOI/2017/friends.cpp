#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <set>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 2500;
int n, x, y;
int id[mxn], vis[mxn], in[mxn], ot[mxn], ud[mxn];
vector<int> g[mxn];
set<int> s[mxn];
stack<int> stk;
int k, kx, ky;

void die(){
	cout << "detention" << endl;
	exit(0);
}

//branch group
void spush(int c){
	ud[c] = 1;
	stk.push(c);
}

int spop(){
	int c = stk.top();
	stk.pop();
	ud[c] = 0;
	return c;
}

bool sol(), solin(), solout();

bool sol(){
	if(kx > x || ky > y || kx + ky + stk.size() > x + y) return 0;
	if(stk.empty()) return 1;
	return solin() || solout();
}

bool solin(){
	int c = spop();
	
	int m = 0;
	kx++, in[c] = 1;
	for(int i : g[c]){
		ky += ot[i];
		if(in[i] || ot[i] || ud[i]) continue;
		m++;
		spush(i);
	}
	
	bool ret = sol();
	
	kx--, in[c] = 0;
	for(int i : g[c]) ky -= ot[i];
	while(m--) spop();
	spush(c);
	
	if(ret){
		vis[c] = 1;
		s[k].insert(c);
	}
	
	return ret;
}

bool solout(){
	int c = spop();
	
	ot[c] = 1;
	for(int i : g[c]) ky += in[i];
	
	bool ret = sol();
	
	ot[c] = 0;
	for(int i : g[c]) ky -= in[i];
	spush(c);
	
	return ret;
}
//end branch group

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> x >> y;
	
	for(int i = 0; i < n; i++){
		int m;
		cin >> m;
		for(int j = 0; j < m; j++){
			int v;
			cin >> v;
			g[i].push_back(v);
		}
	}
	
	for(int i = 0; i < n; i++){
		sort(g[i].begin(), g[i].end());
		for(int j : g[i]){
			auto it = lower_bound(g[j].begin(), g[j].end(), i);
			if(it == g[j].end() || *it != i) die();
		}
	}
	
	memset(id, -1, sizeof(id));
	for(; k < n; k++){
		if(vis[k]) continue;
		
		spush(k);
		if(!solin()) die();
		spop();
		
		for(int i : s[k]){
			if(~id[i] && id[i] != k){
				vector<int> v;
				for(int j  : s[k]){
					if(id[j] == id[i]){
						v.push_back(j);
						s[k].erase(j);
						s[id[i]].erase(j);
						id[j] = -1;
					} 
				} 
				
				int w = 0, z = 0;
				for(int j : v)
				for(int l : g[j]){
					w += id[j] == k;
					z += id[j] == id[i];
				}
				
				for(int j : v){
					if(w > z){
						id[j] = k;
						s[k].insert(j);
					}else{
						id[j] = id[i];
						s[id[i]].insert(j);
					}
				}
			}else{
				id[i] = k;
			}
		}
	}
	
	cout << "home" << endl;
	
	int ret = 0;
	for(int i = 0; i < k; i++) ret += !s[i].empty();
	
	cout << ret << endl;
	for(int i = 0; i < k; i++){
		if(s[i].empty()) continue;
		cout << s[i].size();
		for(int j : s[i]) cout << " " << j;
		cout << endl;
	}
	

	return 0;
}
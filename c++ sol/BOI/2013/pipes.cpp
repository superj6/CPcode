#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 500000;
int n, m, k;
pi e[mxn];
int a[mxn], d[mxn], vis[mxn];
vector<int> s;
vector<int> g[mxn];
stack<int> stk;
int ans[mxn];

void die(){
	cout << 0 << endl;
	exit(0);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	if(m > n) die();
	
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < m; i++){
		cin >> e[i].f >> e[i].s;
		d[--e[i].f]++, d[--e[i].s]++;
		g[e[i].f].push_back(i);
		g[e[i].s].push_back(i);
	}
	
	for(int i = 0; i < n; i++) if(!~-d[i]) stk.push(i);
	
	while(!stk.empty()){
		int c = stk.top();
		stk.pop();
		for(int i : g[c]){
			if(!vis[i]){
				int v = c ^ e[i].f ^ e[i].s;
				d[v]--;
				a[v] -= a[c];
				vis[i] = 1;
				ans[i] = 2 * a[c];
				if(!~-d[v]) stk.push(v);
			}
		}
	}
	
	for(int i = 0; i < m; i++){
		if(!vis[i]){
			for(int j = e[i].f;;){
				bool t = 0;
				for(int l : g[j]){
					if(!vis[l]){
						t = vis[l] = 1;
						if(j != e[l].f) swap(e[l].f, e[l].s);
						j = e[l].s;
						s.push_back(l);
						break;
					}
				}
				if(!t) break;
			}
		}
	}
	
	k = s.size();
	if(k && !(k & 1)) die();
			
	for(int i = 0; i < k; i++) ans[s[0]] += (1 - 2 * (i & 1)) * a[e[s[i]].s];
	for(int i = 1; i < k; i++) ans[s[i]] = 2 * a[e[s[i]].f] - ans[s[i - 1]];
	
	for(int i = 0; i < m; i++) cout << ans[i] << endl;

	return 0;
}
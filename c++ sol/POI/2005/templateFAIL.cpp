#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 500001;
int n;
string t;
int p[mxn], f[mxn], vis[mxn];
set<int> s[mxn];
map<int, int> d[mxn];

void add(int x, int v){
	auto it = s[x].lower_bound(v);
	if(it != s[x].end()){
		if(*it == v) return;
		if(!(--d[x][*it - *prev(it)])) d[x].erase(*it - *prev(it));
		d[x][*it - v]++;
	}
	d[x][v - *prev(it)]++;
	s[x].insert(v);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
		
	cin >> t;
	n = t.size();
	
	f[0]++;
	for(int i = 1, j = 0; i < n; i++){
		while(j && t[i] != t[j]) j = p[j - 1];
		f[p[i] = (j += t[i] == t[j])]++;
	}
	
	vis[0] = 1;
	for(int i = n; i; i = p[i - 1]) vis[i] = f[p[i - 1]] > 1;
	
	for(int i = 0; i <= n; i++){
		if(vis[i]){
			s[i].insert(0);
			add(i, i);
		}else{
			if(!vis[p[i - 1]]) p[i - 1] = p[p[i - 1] - 1];
			add(p[i - 1], i);
		}
	}
	
	int ret = n;
	for(int i = vis[n] ? n : p[n - 1]; i; i = p[i - 1]){
		if(max(prev(d[i].end())->f, n + i - *prev(s[i].end())) <= i) ret = i;

		int x = p[i - 1];
		if(s[i].size() > s[x].size()) swap(s[i], s[x]), swap(d[i], d[x]);
		
		for(int j : s[i]) add(x, j);
		s[i].clear(), d[i].clear();
	}
	
	cout << ret << endl;

	return 0;
}
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
#include <unordered_map>
using namespace std;
#define endl '\n'

const int maxn = 200001;

struct BIT{
	long bit[maxn];
	
	BIT(){
		memset(bit, 0, sizeof(bit));
	}
	
	void add(int x, int v){
		for(; 0 < x && x < maxn; x += x & -x) bit[x] += v;
	}
 
	long qry(int x){
		long ret = 0;
		for(; x > 0; x -= x & -x) ret += bit[x];
		return ret;
	}
	
	long qry(int a, int b){
		return qry(b) - qry(a - 1);
	}
};

int n;
BIT bit;
int l[maxn], r[maxn], v[maxn], v2[maxn];
vector<int> graph[maxn], query[maxn];
unordered_map<int, int> used;
int ans[maxn];

int dfs(int c, int p){
	r[c] = l[c];
	v2[l[c] - 1] = v[c];
	for(int i : graph[c]){
		if(i == p) continue;
		l[i] = r[c] + 1;
		r[c] = dfs(i, c);
	}
	query[r[c] - 1].push_back(c);
	return r[c];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> v[i];
	
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	l[0] = 1;
	dfs(0, -1);
	
	for(int i = 0; i < n; i++){
		bit.add(used[v2[i]], -1);
		used[v2[i]] = i + 1;
		bit.add(used[v2[i]], 1);
		
		for(int j : query[i]){
			ans[j] = bit.qry(l[j], r[j]);
		}
	}
	
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}
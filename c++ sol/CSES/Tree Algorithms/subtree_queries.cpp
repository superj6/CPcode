#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'

const int maxn = 200001;

struct BIT{
	long bit[maxn];
	
	BIT(){
		memset(bit, 0, sizeof(bit));
	}
	
	void add(int x, int v){
		x++;
		for(; x < maxn; x += x & -x) bit[x] += v;
	}
 
	long qry(int x){
		long ret = 0;
		x++;
		for(; x > 0; x -= x & -x) ret += bit[x];
		return ret;
	}
	
	long qry(int a, int b){
		return qry(b) - qry(a - 1);
	}
};

int n, q;
BIT bit;
int l[maxn], r[maxn], v[maxn];
vector<int> graph[maxn];

int dfs(int c, int p){
	r[c] = l[c];
	bit.add(l[c], v[c]);
	for(int i : graph[c]){
		if(i == p) continue;
		l[i] = r[c] + 1;
		r[c] = dfs(i, c);
	}
	return r[c];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	
	for(int i = 0; i < n; i++) cin >> v[i];
	
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	dfs(0, -1);
	
	for(int i = 0; i < q; i++){
		int t, s;
		cin >> t >> s;
		s--;
		
		if(t == 1){
			int x;
			cin >> x;
			bit.add(l[s], x - v[s]);
			v[s] = x;
		}else{
			cout << bit.qry(l[s], r[s]) << endl;
		}
	}

	return 0;
}
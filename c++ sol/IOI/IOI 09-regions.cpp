/*
  Use sqrt decomp by precomputing queries where a region contains > sqrt(n) vertices. You can do this by doing a traversal of the tree
maintaining the number of nodes of the current region from the path to root and within the subtree and adding this to an an answer list
corresponding to each region with the current one. Finally, when answering queries, if both regions have <= sqrt(n) vertices, hold the
reindexed ranges each node corresponds to in a dfs traversal and put the second part of a query in a bit and query for each vertices
range belonging to the first part of the query.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
//#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 200001, mxk = 25000, m = 447;
int n, k, q, t;
int a[mxn], p[mxn], dp[mxn], l[mxn], r[mxn], bit[mxn], b[mxk];
ll f1[m][mxk], f2[m][mxk];
vector<int> g[mxn], w[mxk];

void add(int x, int v){
	for(x++; x <= n; x += x & -x) bit[x] += v;
}

int qry(int x){
	int ret = 0;
	for(x++; x; x -= x & -x) ret += bit[x];
	return ret;
}

int dfs(int c){
	r[c] = l[c];
	for(int i : g[c]) if(i != p[c]) l[i] = r[c] + 1, r[c] = dfs(i);
	return r[c];
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> q;
	
	for(int i = 0; i < n; i++){
		if(i){
			cin >> p[i];
			g[--p[i]].push_back(i);
		}else{
			p[i] = -1;
		}
		cin >> a[i];
		w[--a[i]].push_back(i);
	}
	
	for(int i = 0; i < k; i++){
		if(w[i].size() > m){
			for(int j = 0; j < n; j++){
				f1[t][a[j]] += (dp[j] = (a[j] == i) + (~p[j] ? dp[p[j]] : 0));
			}
			memset(dp, 0, sizeof(dp));
			for(int j = n - 1; ~j; j--){
				f2[t][a[j]] += (dp[j] += a[j] == i);
				if(~p[j]) dp[p[j]] += dp[j];
	 		}
	 		b[i] = t++;
		}else{
			b[i] = -1;
		}
	}
	
	dfs(0);
	
	while(q--){
		int x, y;
		cin >> x >> y;
		x--, y--;
		if(~b[x]){
			cout << f1[b[x]][y] << endl;
		}else if(~b[y]){
			cout << f2[b[y]][x] << endl;
		}else{
			ll ret = 0;
			for(int i : w[y]) add(l[i], 1);
			for(int i : w[x]) ret += qry(r[i]) - qry(l[i] - 1);
			for(int i : w[y]) add(l[i], -1);
			cout << ret << endl;
		}
	}

	return 0;
}

/*
  The optimal solution will use the largest dag possible out of a subset of the nodes because you can construct an order where first
all non-dag nodes give to next in order, then all dag nodes give to next in order, then all non-dag nodes again give to next in order.
This will use a total of 2 * k - [dag] - [groups], where [dag] is number of nodes in dags and [group] is number of connected components
because each node will give twice except those in a dag and the final node in the ordering. This means you need to find the largest
dag, and you do this by doing a sort of topological sort bitmask dp by adding a node to the mask if none of its edges go to a node
in the mask, as this will be the final node in topological order so far.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100000, k = 20;
int n;
int a[2][mxn];
int e[k], par[k], rnk[k];
int dp[1 << k];

int fnd(int x){
	return x == par[x] ? x : par[x] = fnd(par[x]);
}

void answer(){
	cin >> n;
	
	for(int i = 0; i < 2; i++)
	for(int j = 0; j < n; j++){
		char c;
		cin >> c;
		a[i][j] = c - 'a';
	}
	
	for(int i = 0; i < k; i++){
		e[i] = rnk[i] = 0;
		par[i] = i;
	}
	for(int i = 0; i < n; i++){
		e[a[0][i]] |= (1 << a[1][i]);
		int x = fnd(a[0][i]), y = fnd(a[1][i]);
		if(x != y){
			if(rnk[x] < rnk[y]) swap(rnk[x], rnk[y]);
			rnk[x] += rnk[x] == rnk[y];
			par[y] = x;
		}
	}
	
	int ret = 0;
	dp[0] = 1;
	for(int i = 1; i < (1 << k); i++){
		dp[i] = 0;
		for(int j = 0; j < k; j++){
			dp[i] |= ((i >> j) & 1) && !(e[j] & (i ^ (1 << j))) && dp[i ^ (1 << j)];
		}
		if(dp[i]) ret = max(ret, __builtin_popcount(i));
	}
	for(int i = 0; i < k; i++) ret += (par[i] == i);
	ret = 2 * k - ret;
	
	cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}

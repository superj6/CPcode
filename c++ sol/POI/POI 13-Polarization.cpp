/*
	First realize you always want to root a tree and have all edges either going toward the root or going away from the root.
This is because it is always better to multiply two numbers as large as possible than multiply combinations of different parts. Next
realize it is always best to root at a centroid node. You can prove this by analyzing the difference between a non-centroid node and
going to a node 1 closer to the centroid. This means the total answer will be the sum of all subtree sizes, since all edges going up
or going down either allows each node to reach the root or the root to reach each node of the subtree, plus the product of the best
partition of the subtree sizes of a centroid into two groups. You can find all possible partitions with knapsack in O(nsqrtn) by holding
the multiplicity of each size and making sure you never iterate adding in the knapsack over the same area twice. The sqrtn is because
there can be at most sqrtn distinct sizes that in total add to n. This means you can just try rerooting the tree and test for each node
if its a centroid, and if it is, do knapsack and try all the partition products plus the sum of subtree value. Because there are at most
2 centroids you only run the knapsack at most twice so the time complexity is O(nsqrtn) for computing the max value. Also, the min value
is always n - 1, as all tree are bipartite graphs and you can 2-color the tree and have all nodes of one color have edges going in while
all nodes of the other color have edges going out.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 250000;
int n;
ll a[mxn], b[mxn], sz[mxn], dp[mxn], dp2[mxn];
vector<int> g[mxn];

ll dfs(int c, int p){
	sz[c] = 1;
	for(int i : g[c]){
		if(i == p) continue;
		dp[c] += dfs(i, c);
		sz[c] += sz[i];
	}
	return dp[c] += sz[c] - 1;
}

ll dfs2(int c, int p){
	ll ret = dp[c], t = 1;
	for(int i : g[c]){
		t &= 2 * sz[i] <= sz[c];
		if(i == p) continue;
		sz[c] -= sz[i], dp[c] -= dp[i] + sz[i];
		sz[i] += sz[c], dp[i] += dp[c] + sz[c];
		ret = max(ret, dfs2(i, c));
		sz[i] -= sz[c], dp[i] -= dp[c] + sz[c];
		sz[c] += sz[i], dp[c] += dp[i] + sz[i];
	}
	
	if(t){
		memset(a, 0, sizeof(a));
		memset(dp2, 0, sizeof(dp2));
		dp2[0] = 1;
		for(int i : g[c]) a[sz[i]]++;
		
		for(int i = 0, k = 1; i < n; i++) if(a[i]){
			k += i * a[i];
			for(int j = 0; j < i; j++) b[j] = k;
			for(int j = k - 1; ~j; j--) if(dp2[j]){
				for(int l = 1; l <= a[i] && j + i * l < b[j % i]; l++){
					dp2[j + i * l] = 1;
				}
				b[j % i] = j;
			}
		}
		
		ll x = 0;
		for(int i = 0; i < n; i++){
			if(dp2[i]) x = max(x, (ll)i * (n - i - 1));
		} 
		ret = max(ret, x + dp[c]);
	}
	
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	dfs(0, -1);
	
	cout << n - 1 << " " << dfs2(0, -1) << endl;

	return 0;
}

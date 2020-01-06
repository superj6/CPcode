/*
	For this problem, observe that you just need to pick one edge in each connected graph such that the sum of their weights is
greater than y - x * groups. To do this, you can do dp for each group with a dfs and tree rerooting to find the lengths of every
edge in the tree and how many there are of each length. From there, it is pretty basic dp to add to the previous path lengths gathered
from other groups. However, some important optimizations to save runtime are are to use a map and to  compress all values greater
than y - x * groups, as adding more length to those does not add new answer. The runtime is around O(n^2logn).
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <string.h>
using namespace std;
#define endl '\n'

const int mx = 1500, my = 2501, mod = 1e9 + 7;
int n, m, x, y;
bool vis[mx];
long long amt[my], namt[my], sum[my], nsum[my];
map<int, long long> len, lsum;
vector<int> dist;
vector<pair<int, int>> graph[mx];
int k;

void dfs(int c){
	int f = dist.size() - 1;
	vis[c] = 1;
	for(pair<int, int> i : graph[c]){
		int nc = i.first, nd = i.second;
		if(vis[nc]) continue;
		int g = dist.size();
		dist.push_back(dist[f] + nd);
		dfs(nc);
		
		for(int j = f + 1; j < g; j++){
			for(int l = g; l < dist.size(); l++){
				int p = min(dist[j] + dist[l] - 2 * dist[f], y);
				len[p] = (len[p] + 1) % mod;
				lsum[p] = (lsum[p] + dist[j] + dist[l] - 2 * dist[f]) % mod;
			}
		}
	}
	
	for(int i = f + 1; i < dist.size(); i++){
		int p = min(dist[i] - dist[f], y);
		len[p] = (len[p] + 1) % mod;
		lsum[p] = (lsum[p] + dist[i] - dist[f]) % mod;
	}
}

int main(){
	freopen("mooriokart.in", "r", stdin);
	freopen("mooriokart.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> x >> y;

	for(int i = 0; i < m; i++){
		int a, b, d;
		cin >> a >> b >> d;
		a--, b--;
		graph[a].push_back({b, d});
		graph[b].push_back({a, d});
	}
	
	amt[0] = 1;
	for(int i = 0; i < n; i++){
		if(!vis[i]){
			dist.push_back(0);
			dfs(i);
			
			for(auto it = len.begin(), it2 = lsum.begin(); it != len.end(); it++, it2++){
				for(int j = 0; j <= y; j++){
					int p = min(j + it->first, y);
					namt[p] = (namt[p] + (amt[j] * it->second) % mod) % mod;
					nsum[p] = ((nsum[p] + (amt[j] * it2->second) % mod) % mod + (it->second * sum[j]) % mod) % mod;
				}
			}
			
			k++;
			len.clear();
			lsum.clear();
			memcpy(amt, namt, sizeof(amt));
			memset(namt, 0, sizeof(namt));
			memcpy(sum, nsum, sizeof(sum));
			memset(nsum, 0, sizeof(nsum));
		}
	}
	
	long ret = 0;
	for(int i = max(y - k * x, 0); i <= y; i++) ret = (ret + sum[i] + ((k * x) % mod * amt[i]) % mod) % mod;
	
	for(int i = 1; i <= k - 1; i++){
		ret = (ret * 2 * i) % mod;
	}
	
	cout << ret << endl;
	
	return 0;
}

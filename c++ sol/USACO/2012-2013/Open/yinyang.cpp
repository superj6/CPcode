#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n;
int sz[maxn], dp[maxn];
bool used[maxn];
vector<pi> graph[maxn];
int ans[maxn]

int dfs(int c, int p){
  sz[c] = 1;
  for(pi i : graph[c]){
    if(i.first == p || used[i.first]) continue;
    sz[c] += dfs(i.first, -1);
  }
  return sz[c];
}

int dfs2(int c){
  for(pi i : graph[c]){
    if(used[i.first]) continue;
    if(sz[c] < 2 * sz[i.first]){
      sz[i.first] = sz[c];
      return dfs2(i.first);
    }
  }
  return c;
}

void decomp(int c){
  dfs(c, -1);
  c = dfs2(c);

  for(pi i : graph[c]){
    dp[i.first] = i.second;
  }
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
  cin >> n;

  for(int i = 0; i < n - 1; i++){
    int a, b, t;
    cin >> a >> b >> t;
    a--, b--, t = 2 * t - 1;
  }

  decomp(0);

	return 0;
}

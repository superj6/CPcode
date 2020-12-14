#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const ll inf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 500;
int n, m;
ll h[maxn], x[maxn];
ll g[maxn][maxn], f[maxn][maxn];
vector<int> v;

void push(int u, int v){
  ll d = min(x[u], g[u][v] - f[u][v]);
  f[u][v] += d, f[v][u] -= d;
  x[u] -= d, x[v] += d;
}

ll flow(){
  h[0] = n, x[0] = inf;
  for(int i = 1; i < n; i++) push(0, i);

  do{
    //mxhv
    v.clear();
    for(int i = 1; i < n - 1; i++){
      if(x[i]){
        if(v.empty() || h[i] > h[v[0]]) v.assign(1, i);
        else if(h[i] == h[v[0]]) v.push_back(i);
      }
    }

    for(int i : v){
      bool t = 0;
      for(int j = 0; j < n && x[i]; j++){
        if(g[i][j] > f[i][j] && h[i] == h[j] + 1){
          push(i, j);
          t = 1;
        }
      }

      if(!t){
        //rlbl
        ll d = inf;
        for(int j = 0; j < n; j++){
          if(g[i][j] > f[i][j]) d = min(d, h[j]);
        }
        h[i] = d + (d != inf);

        break;
      }
    }
  } while(!v.empty());

  return x[n - 1];
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
  cin >> n >> m;

  for(int i = 0; i < m; i++){
    ll u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    g[u][v] += w;
  }

  cout << flow() << endl;

	return 0;
}
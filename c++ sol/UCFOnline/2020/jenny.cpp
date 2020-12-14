#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define i128 __int128
#define pi pair<int, int>
#define f first
#define s second

const int n = 10;
int q;
int vis[n];
vector<int> v[n];

int ipow(ll b, int e, int mod){
  int ret = 1;
  for(; e; e >>= 1){
    if(e & 1) ret = (i128)ret * b % mod;
    b = (i128)b * b % mod;
  }
  return ret;
}

const int ptst = 5;
int p[ptst] = {2, 3, 5, 7, 11};
bool ptest(ll x){
	if(x < p[0]) return 0;
	for(int i = 0; i < ptst; i++) if(x % p[i] == 0) return x == p[i];
	if(x < p[ptst - 1]) return 1;
	
	ll y = x - 1, e = __lg(y & -y);
	y >>= e;
	for(int i = 0; i < ptst; i++){
	  ll z = ipow(p[i] % x, y, x);
	  if(z == 1) continue;
	  for(int i = 0; i < e && z != x - 1; i++) z = z * z % x;
	  if(z != x - 1) return 0;
	}
	
	return 1;
}

void sol(ll x, int y){
	if(ptest(x) && ptest(x + 1 + (x & 1))) v[y - 1].push_back(x);
	for(int i = 0; i < n; i++) if(!vis[i] && (x + i)){
		vis[i] = 1;
		sol(10 * x + i, y + 1);
		vis[i] = 0;
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> q;
	
	sol(0, 0);
	
	for(int i = 0; i < n; i++) sort(v[i].begin(), v[i].end());
	
	while(q--){
		int x, y;
		cin >> x >> y;
		x--, y--;
		
		if(x >= n || y >= v[x].size()){
			cout << "Brice doesn't stand a chance!" << endl;
		}else{
			cout << v[x][y] << endl;
		}
	}

	return 0;
}
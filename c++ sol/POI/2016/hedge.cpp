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

const int maxn = 1000000;
int n, m;
int par[maxn], rnk[maxn];
vector<pi> v[2];
int ans[2][maxn];

int find(int x){
    return x == par[x] ? x : par[x] = find(par[x]);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int t = 0; t < 2; t++)
    for(int i = 0; i < n - t; i++)
    for(int j = 0; j < m - !t; j++){
        char c;
        cin >> c;
        v[c == 'C'].push_back({t, i * (m - !t) + j});
    }
	
	for(int i = 0; i < n * m; i++) par[i] = i;
	
	int ret1 = 2 * n * m - n - m, ret2 = v[1].size();
	for(int t = 0; t < 2; t++)
	for(pi i : v[t]){
	    int x = i.s / (m - !i.f) * m + i.s % (m - !i.f);
	    int y = x + 1 + i.f * (m - 1); 
	    x = find(x), y = find(y);
	    if(x != y){
	        if(rnk[x] < rnk[y]) swap(x, y);
	        rnk[x] += rnk[x] == rnk[y];
	        par[y] = x;
	        ret1--, ret2 -= t;
	        ans[i.f][i.s] = 1;
	    }
	}
	
	cout << ret1 << " " << ret2 << endl; 
	for(int t = 0; t < 2; t++)
	for(int i = 0; i < n - t; i++){
	    for(int j = 0; j < m - !t; j++){
	        cout << (ans[t][i * (m - !t) + j] ? '.' : 'Z');
	    }
	    cout << endl;
	}

	return 0;
}
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <array>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

typedef array<ll, 2> T;

T operator+(T a, T b){
    return {a[0] + b[0], a[1] + b[1]};
}

const int maxn = 100000, k = 22;
int n;
int a[maxn];
T dp[maxn][k];
vector<int> graph[maxn];

ll dfs(int c, int p){
    ll ret = a[c], cur = 0;
    for(int i : graph[c]){
        if(i == p) continue;
        ret += dfs(i, c);
        for(int j = 0; j < k; j++){
            dp[c][j] = dp[c][j] + dp[i][j];
        }
    }
    for(int i = 0; i < k; i++){
        int x = (a[c] >> i) & 1;
        if(x) swap(dp[c][i][0], dp[c][i][1]);
        dp[c][i][x]++;
    }
    for(int i : graph[c]){
        if(i == p) continue;
        for(int j = 0; j < k; j++)
        for(int t = 0; t < 2; t++){
            int x = (a[c] >> j) & 1;
            cur += (dp[i][j][t] * (dp[c][j][!t] - dp[i][j][!t ^ x] - (x == !t))) << j;
            ret += dp[i][j][t] * (x == !t) << j;
        }
    }
    ret += cur >> 1;
    return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
    
    cin >> n;
    
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    cout << dfs(0, -1) << endl;

	return 0;
}
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <stack>
#include <array>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, int>
#define f first
#define s second

const int mod = 1000000007;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const int mxn = 30000, mxm = 132, mxk = 6, t = 4;
int n, m, k;
int a[mxn][mxk], b[mxn][mxk];
int g[mxm][mxk][t];
pi dp[2][mxm];

//init
int c[mxk];
array<int, mxk> v;
array<int, mxk> f[mxm];
stack<int> stk;
stack<int> stk2[mxk];

void gen(int x, int y){
	if(x == k){
		f[m++] = v;
		return;
	}
	
	while(!stk.empty()){
		stk2[x].push(stk.top());
		stk.pop();
	}
	while(!stk2[x].empty()){
		stk.push(stk2[x].top());
		stk2[x].pop();
		v[x] = stk.top();
		gen(x + 1, y);
	}
	stk.push(y);
	v[x] = y;
	gen(x + 1, y + 1);
	stk.pop();
}

int id(){
	int x = 0;
	memset(c, -1, sizeof(c));
	for(int i = 0; i < k; i++){
		if(!~c[v[i]]) c[v[i]] = x++;
		v[i] = c[v[i]];
	}
	return lower_bound(f, f + m, v) - f;
}

void init(){
	gen(0, 0);
	for(int i = 0; i < m; i++){
		dp[0][i] = {inf, 0};
		for(int j = 0; j < k; j++){
			//0
				if(count(f[i].begin(), f[i].begin() + k, f[i][j]) > 1){
					v = f[i];
					v[j] = k - 1;
					g[i][j][0] = id();
				}else{
					g[i][j][0] = -1;
				}
			//0
			
			//1
				if(j && f[i][j] != f[i][j - 1] && ~g[i][j][0]){
					v = f[i];
					v[j] = v[j - 1];
					g[i][j][1] = id();
				}else{
					g[i][j][1] = j && ~g[i][j][0] ? i : -1;
				}
			//1
			
			//2
				g[i][j][2] = i;
			//2
			
			//3
				if(j && f[i][j] != f[i][j - 1]){
					v = f[i];
					for(int l = 0; l < k; l++) if(v[l] == f[i][j]) v[l] = f[i][j - 1];
					g[i][j][3] = id();
				}else{
					g[i][j][3] = j ? i : -1;
				}
			//3
		}
	}
}
//end init

int main(){
	freopen("escape.in", "r", stdin);
	freopen("escape.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	init();
	
	for(int i = 0; i < n; i++)
	for(int j = 1; j < k; j++) cin >> a[i][j];
	
	for(int j = 0; j < k; j++)
	for(int i = 1; i < n; i++) cin >> b[i][j];
	
	int r = 0;
	dp[0][m - 1] = {0, 1};
	for(int i = 0; i < n; i++)
	for(int j = 0; j < k; j++, r ^= 1){
		for(int l = 0; l < m; l++) dp[r ^ 1][l] = {inf, 0};
		for(int l = 0; l < m; l++)
		for(int p = 0; p < t; p++){
			if(!~g[l][j][p]) continue;
			pi cr = dp[r][l], &nx = dp[r ^ 1][g[l][j][p]];
			cr.f += a[i][j] * (p & 1) + b[i][j] * ((p >> 1) & 1);
			if(nx.f > cr.f) nx.s = 0;
			if(cr.f <= nx.f) nx.f = cr.f, nx.s = (nx.s + cr.s) % mod;
		}
	}
	
	cout << dp[r][0].s << endl;

	return 0;
}
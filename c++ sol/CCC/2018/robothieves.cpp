#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

pi operator+(pi a, pi b){
	return {a.f + b.f, a.s + b.s};
}

const int inf = 0x3f3f3f3f;
const int maxn = 100;
int n, m;
char a[maxn][maxn];
bool b[maxn][maxn];
int dp[maxn][maxn];
auto cmp = [](pi f, pi g){ return 
	dp[f.f][f.s] + (a[f.f][f.s] == '.') > 
	dp[g.f][g.s] + (a[g.f][g.s] == '.');};
priority_queue<pi, vector<pi>, decltype(cmp)> pq(cmp);
pi d[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
char ch[4] = {'D', 'U', 'R', 'L'};
vector<pi> cm;
pi s;

bool works(pi p){
	return p.f >= 0 && p.s >= 0 && p.f < n && p.s < m && a[p.f][p.s] != 'W';
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		cin >> a[i][j];
		if(a[i][j] == 'S') s = {i, j};
		if(a[i][j] == 'C') cm.push_back({i, j});
	}
	
	for(pi i : cm)
	for(int t = 0; t < 4; t++){
		pi c = i;
		do{
			b[c.f][c.s] = a[c.f][c.s] == '.' || 
				a[c.f][c.s] == 'C' || a[c.f][c.s] == 'S';
			c = c + d[t];
		} while(works(c));
	}
	
	memset(dp, inf, sizeof(dp));
	if(!b[s.f][s.s]){
		dp[s.f][s.s] = 0;
		pq.push(s);
	} 
	while(!pq.empty()){
		pi c = pq.top();
		pq.pop();
		for(int i = 0; i < 4; i++){
			pi p = c + d[i];
			if(works(p) && !b[p.f][p.s] && dp[p.f][p.s] == inf){
				if(a[c.f][c.s] == 'S' || a[c.f][c.s] == '.'){
					dp[p.f][p.s] = dp[c.f][c.s] + 1;
					pq.push(p);
				}else if(a[c.f][c.s] == ch[i]){
					dp[p.f][p.s] = dp[c.f][c.s];
					pq.push(p);
				}
			} 
		}
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		if(a[i][j] == '.') cout << (dp[i][j] == inf ? -1 : dp[i][j]) << endl;
	}

	return 0;
}
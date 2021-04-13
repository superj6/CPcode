#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 400000;
int n, m;
int a[mxn], b[mxn], v[mxn], d[mxn], dd[mxn];
int dp[5][1 << 15][10];
vector<int> g[mxn];
queue<int> q;

void sol(){
	memset(d, 0x3f, 2 * n * sizeof(int));
	d[0] = 0, q.push(0);
	while(!q.empty()){
		int c = q.front();
		q.pop();
		for(int i : g[c]) if(!v[i]){
			int x = c ^ a[i] ^ b[i];
			if(d[x] > d[c] + 1) d[x] = d[c] + 1, q.push(x);
		}
	}
}

void answer(){
	cin >> n >> m;
	
	for(int i = 0; i < 2 * n; i++) g[i].clear();
	for(int i = 0; i < m; i++){
		cin >> a[i] >> b[i];
		a[m + i] = --a[i], b[m + i] = --b[i];
		a[i] += n, b[m + i] += n;
		for(int j = 0; j < 2; j++){
			int x = j * m + i;
			v[x] = 0;
			g[a[x]].push_back(x);
			g[b[x]].push_back(x);
		}
	}
	
	sol();
	memcpy(dd, d, 2 * n * sizeof(int));
	
	if(m == n - 1){
		cout << m << endl;
		return;
	}
	if(m == n){
		cout << (m - (d[n] == 0x3f3f3f3f)) << endl;
		return;
	}
	
	int ret = m;
	if(n <= 5){
		m = n * (n - 1) / 2 + n;
		for(int i = 0; i < 2 * n; i++) g[i].clear();
		for(int i = 0, l = 0; i < n; i++)
		for(int j = i; j < n; j++, l++){
			a[l] = a[m + l] = i;
			b[l] = b[m + l] = j;
			a[l] += n, b[m + l] += n;
			for(int p = 0; p < 2; p++){
				int x = p * m + l;
				v[x] = 0;
				g[a[x]].push_back(x);
				g[b[x]].push_back(x);
			}
		}
		
		for(int i = 0; i < (1 << m); i++){
			if(!dp[n - 1][i][1]){
				for(int j = 0; j < m; j++) v[j] = v[m + j] = (i >> j) & 1;
				sol();
				memcpy(dp[n - 1][i], d, 2 * n * sizeof(int));
			}
			if(!memcmp(dp[n - 1][i], dd, 2 * n * sizeof(int))){
				ret = min(ret, m - __builtin_popcount(i));
			}
		}
	}else{
		for(int i = 0; i < m; i++){
			v[i] = v[m + i] = 1;
			sol();
			if(memcmp(d, dd, 2 * n * sizeof(int))) v[i] = v[m + i] = 0;
			else ret--;
		}
	}
	
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
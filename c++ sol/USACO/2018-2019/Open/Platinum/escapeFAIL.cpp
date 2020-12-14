#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<long long, long long>

const long long mod = 1000000007;
pi operator+(pi a, pi b){
	pi ret = {min(a.first, b.first), 0};
	if(a.first == ret.first) ret.second += a.second;
	if(b.first == ret.first) ret.second += b.second;
	ret.second %= mod;
	return ret;
}

const int maxn = 300001, maxk = 6;
int n, k;
int h[maxn][maxk], v[maxn][maxk];
map<vector<int>, pi> dp[maxn];

int main(){
	//freopen("escape.in", "r", stdin);
	//freopen("escape.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < k - 1; j++){
			cin >> h[i][j];
		}
	}
	
	for(int j = 0; j < k; j++){
		for(int i = 1; i < n; i++){
			cin >> v[i][j];
		}
	}
	
	pi p = {0, 1};
	vector<int> a(k);
	for(int i = 0; i < k; i++) a[i] = i;
	dp[0][a] = p;

	for(int i = 0; i < n; i++)
	for(auto it : dp[i]){
		a = it.first, p = it.second;
		
		
		cout << i << ":";
		for(int j : a) cout << " " << j;
		cout << endl;
		cout << p.first << " " << p.second << endl;
		
		
		for(int x = 0; x < (1 << k); x++){
			long long f = 0;
			
			bool used[k];
			memset(used, 0, sizeof(used));
			for(int j = 0; j < k; j++) used[a[j]] = 1;
			for(int j = 0; j < k; j++) if(x & (1 << j)) used[a[j]] = 0, f += v[i][j];
			for(int j = 0; j < k; j++) if(used[j]) f = -1;
			if(f == -1) continue;
			
			for(int y = 0; y < (1 << (k - 1)); y++){
				long long g = 0;
				vector<int> b(k);
				int col[k], col2[k], d[k];
				memset(col, -1, sizeof(col));
				memset(d, 0, sizeof(d));
				if(x & 1) col[0] = 0;
				for(int j = 0, c = 0; j < k - 1; j++){
					if(y & (1 << j)) g += h[i][j];
					else c++;
					if(x & (1 << (j + 1)) && col[a[j + 1]] == -1) col[a[j + 1]] = c;
					col2[c] = c;
				}
				for(int j = 0, c = 0; j < k - 1; j++){
					if(~y & (1 << j)) c++;
					if(x & (1 << (j + 1))) col2[c] = min(col2[c], col[a[j + 1]]);
					d[c] = (col2[c] != c);
				}
				for(int j = 1; j < k; j++) d[j] += d[j - 1];
				for(int j = 0, c = 0; j < k - 1; j++){
					if(~y & (1 << j)) c++;
					b[j + 1] = col2[c] - d[col2[c]];
				}
				
				if(dp[i + 1][b] == (pi){0, 0}) dp[i + 1][b] = (pi){p.first + f + g, p.second};
				else dp[i + 1][b] = dp[i + 1][b] + (pi){p.first + f + g, p.second};
			}
		}
	}
	
	for(int i = 0; i < k; i++) a[i] = 0;
	cout << dp[n][a].first << " ";
	cout << dp[n][a].second << endl;

	return 0;
}
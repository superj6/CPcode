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
 
const int mxn = 1000;
int n, m;
int dp[mxn][mxn][2], dp2[mxn][mxn][2];
vector<int> g[mxn], gr[mxn];
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0, x; i < n; i++)
	for(cin >> x; x; cin >> x)
	for(int j = 0; j < 2; j++)
	for(int l = 0; l < 2; l++){
		int u = j * n + i, v = l * n + x - 1;
		if(abs(u - v) < n){
			g[u].push_back(v);
			gr[v].push_back(u);
		} 
	}
	
	for(int i[2] = {0}; i[1] < 2 * n; i[1]++)
	for(i[0] = i[1]; ~i[0] && i[1] - i[0] < n; i[0]--)
	for(int j = 0; j < 2; j++){
		int &dpc = dp[i[0]][i[1]][j], dpc2 = dp2[i[0]][i[1]][j];
		if(i[0] != i[1]) dpc = max(dpc, dp[i[0] + j][i[1] - !j][j]);
		
		for(int k : gr[i[j]]) if(k != i[!j])
		for(int l = 0, ii[2]; l < 2; l++) if((k > i[l]) == l && abs(k - i[!l]) < n){
			ii[l] = k, ii[!l] = i[!l];
			int &dpx = dp[ii[0]][ii[1]][l], &dpx2 = dp2[ii[0]][ii[1]][l];
			dpx = max(dpx, dpc + 1);
			if(j == l && (i[0] == i[1] || dpc2)) dpx2 = max(dpx2, dpc2 + 1);
		}
	}
	
	int ret = 0, x = 0;
	for(int i[2] = {0}; i[1] < 2 * n; i[1]++)
	for(i[0] = i[1]; ~i[0] && i[1] - i[0] < n; i[0]--)
	for(int j = 0; j < 2; j++){
		int dpc = dp[i[0]][i[1]][j], dpc2 = dp2[i[0]][i[1]][j];
		if(dpc > ret) ret = dpc, x = i[j];
		
		if(m && (i[0] == i[1] || dpc2)){
			for(int p = 0, ii[2]; p < 2; p++){
				int d = 1 - 2 * (j ^ p), k = -1; 
				for(int l : gr[i[j]]){
					if(l != i[p] && (l > i[p]) == p && abs(l - i[!p]) < n && 
					(!~k || d * abs(l - i[!p]) > d * abs(k - i[!p]))){
						k = l;
					}
				} 
				
				if(~k) for(int l : g[i[!j]]){
					if(l != i[p] && (l > i[p]) == p && 
					abs(l - i[!p]) < n && l != k && (l < k) == j){
						ii[p] = l, ii[!p] = ~d ? i[j] : k;
						int c = dp[ii[0] + p][ii[1] - !p][p] + dpc2 + 2;
						if(c > ret) ret = c, x = k;
					}
				}
			}
		}
	}
	
	cout << ret << endl;
	cout << (x % n + 1) << endl;
	
	return 0;
}
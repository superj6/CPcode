#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
const int maxn = 100;
int n, m, sx, sy, k, nm;
ll a[maxn][maxn];
ll dp[maxn][maxn][2];
 
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
 
bool works(int x, int y){
    return x >= 0 && y >= 0 && x < n && y < m;
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> sx >> sy >> k;
	sx--, sy--;
    nm = min(n * m, k / 2);
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
	    cin >> a[i][j];
	}
	
	memset(dp, -1, sizeof(dp));
	dp[sx][sy][0] = 0;
	for(int l = 0; l < nm; l++){
    	for(int i = 0; i < n; i++)
    	for(int j = 0; j < m; j++){
    	    if(dp[i][j][l & 1] == -1) continue;
        	for(int f = 0; f < 4; f++){
        	    int x = i + dx[f], y = j + dy[f];
        	    if(works(x, y)){
        	        dp[x][y][(l & 1) ^ 1] = max(dp[x][y][(l & 1) ^ 1],
        	            dp[i][j][l & 1] + a[x][y]);
        	    }
        	}
    	}
	}
	
	ll ret = 0;
	for(int i  = 0; i < n; i++)
	for(int j = 0; j < m; j++){
	    if(dp[i][j][nm & 1] == -1) continue;
	    for(int f = 0; f < 4; f++){
	        int x = i + dx[f], y = j + dy[f];
	        if(works(x, y)){
	            ret = max(ret, 2 * dp[i][j][nm & 1] + 
	                (k / 2 - nm) * (a[i][j] + a[x][y]) - a[i][j]);
	        }
	    }
	}
	
	cout << ret << endl;
 
	return 0;
}
/*

*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
const int inf = 0x3f3f3f3f;
const int maxn = 401;
int n;
string s;
int a[3][maxn];
int dp[maxn][maxn][maxn][3];
vector<int> v[3];
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> s;
	
	for(int i = 0; i < n; i++){
	    int c = s[i] == 'R' ? 0 : 1 + (s[i] == 'G');
	    a[c][i + 1] = 1;
	    v[c].push_back(i + 1);
	}
	
	for(int t = 0; t < 3; t++)
	for(int i = 1; i <= n; i++){
	    a[t][i] += a[t][i - 1];
	}
	
	memset(dp, inf, sizeof(dp));
	for(int i[3] = {0}; i[0] <= a[0][n]; i[0]++)
	for(i[1] = 0; i[1] <= a[1][n]; i[1]++)
	for(i[2] = 0; i[2] <= a[2][n]; i[2]++)
	for(int p = 0; p < 3; p++){
	    if(i[0] + i[1] + i[2] == 0){
	        dp[0][0][0][p] = 0;
	    }
	    if(dp[i[0]][i[1]][i[2]][p] == inf) continue;
	    for(int j = 0; j < 3; j++){
	        if(j == p || i[j] == a[j][n]) continue;
	        int l[3] = {i[0], i[1], i[2]};
	        l[j]++;
	        int cp = 0;
	        for(int k = 0; k < 3; k++){
	            if(k == j) continue;
	            cp += max(a[k][v[j][i[j]]] - i[k], 0);
	        }
	        dp[l[0]][l[1]][l[2]][j] = min(dp[l[0]][l[1]][l[2]][j], 
	            dp[i[0]][i[1]][i[2]][p] + cp);
	    }
	}
	
    int ret = inf;
    for(int i = 0; i < 3; i++){
        ret = min(ret, dp[a[0][n]][a[1][n]][a[2][n]][i]);
    }
	
	cout << (ret == inf ? -1 : ret) << endl;
	
	return 0;
}

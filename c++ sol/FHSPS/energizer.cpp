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

const int mod = 10007;
const int n = 64, m = 8;
ll k;
int x, y, X, Y;
int a[n][n], b[n][n];
int dx[m] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[m] = {2, -2, 2, -2, 1, -1, 1, -1};

void mult(int f[n][n], int g[n][n]){
    int ret[n][n];
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++){
        ret[i][j] = 0;
        for(int l = 0; l < n; l++){
            (ret[i][j] += f[i][l] * g[l][j] % mod) %= mod; 
        }
    }
    
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++){
        f[i][j] = ret[i][j];
    }
}

void answer(){
	cin >> x >> y >> X >> Y >> k;
	x--, y--, X--, Y--;
	
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	
	for(int i = 0; i < n; i++) a[i][i] = 1;
	
	for(int x = 0; x < m; x++)
	for(int y = 0; y < m; y++)
	for(int i = 0; i < m; i++){
	    int nx = x + dx[i], ny = y + dy[i];
	    if(nx >= 0 && ny >= 0 && nx < m && ny < m){
	        b[x * m + y][nx * m + ny] = 1;
	    }
	}
	
	for(; k; k >>= 1){
	    if(k & 1) mult(a, b);
	    mult(b, b);
	}
	
	cout << a[x * m + y][X * m + Y] << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}
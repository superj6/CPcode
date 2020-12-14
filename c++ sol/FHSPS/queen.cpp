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

const int maxn = 2002, k = 4;
int n, m;
int a[2 * k][maxn][maxn];
int dx[k] = {1, -1, -1, 1};
int dy[k] = {1, 1, -1, -1};

void answer(){
    cin >> n >> m;
    
    memset(a, 0, sizeof(a));
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        for(int t = 0; t < 2 * k; t++) a[t][x][y] = 1;
    }
    
	for(int t = 0; t < k; t++){
	    for(int i = (1 - n) * (dx[t] - 1) / 2 + 1; 1 <= i && i <= n; i += dx[t])
		for(int j = (1 - n) * (dy[t] - 1) / 2 + 1; 1 <= j && j <= n; j += dy[t]){
			a[t][i][j] |= a[t][i - dx[t]][j - dy[t]];
			a[t + k][i][j] |= a[t + k][i - (t & 1) * dx[t]][j - ((t & 1) ^ 1) * dy[t]];
		}
	}
	
	int ret = 0;
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= n; j++){
	    int c = 0;
	    for(int t = 0; t < 2 * k; t++) c |= a[t][i][j];
	    ret += c;
	}
	
	cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}
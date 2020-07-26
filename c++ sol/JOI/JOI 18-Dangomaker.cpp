/*
  Because Dangos only go down and right, if you start drawing out the cases where they intersect, they can only intersect in cases
where they're middle is on the same diagonal. This means you just record if they exist and do dp on whether you should use it on
each diagonal.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 3002, k = 2, w = 3;
const char c[w] = {'R', 'G', 'W'};
const int dx[k << 1] = {-1, 0, 1, 0};
const int dy[k << 1] = {0, -1, 0, 1};
int n, m;
int a[mxn][mxn], b[mxn][mxn];
int dp[mxn][mxn][2];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m; j++){
		char x;
		cin >> x;
		a[i][j] = find(c, c + w, x) - c;
	}
	
	int ret = 0;
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m; j++){
		if(!~-a[i][j]){
			for(int p = 0; p < k; p++){
				b[i][j] ^= 1 << p;
				for(int l = 0; l < 2; l++){
					int x = i + dx[(p + l * k) % (2 * k)], y = j + dy[(p + l * k) % (2 * k)];
					if(x < 1 || y < 1 || x > n || y > m || a[x][y] != 2 * l){
						b[i][j] ^= 1 << p;
						break;
					}
				}
			}
		}
		for(int p = 0; p < 2; p++)
		for(int l = 0; l < 2; l++){
			int x = ((b[i][j] >> p) & 1), y = ((b[i - 1][j + 1] >> l) & 1);
			if(p == l || !x || !y){
				dp[i][j][p] = max(dp[i][j][p], dp[i - 1][j + 1][l] + x);
			}
		}
		if(i == n || !~-j) ret += max(dp[i][j][0], dp[i][j][1]);
	}
	
	cout << ret << endl;

	return 0;
}

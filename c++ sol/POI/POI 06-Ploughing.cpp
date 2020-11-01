/*
  You can do range dp on the rows that still need to be plowed while greedily the farthest mow vertically from both the left and
right as dp states. This assumes that a vertical row will be the last range ploughed, which is why you are trying to mow as many
verticle rows as a dp state. However, this means you have to rotate the square and do the dp a second time to account for a horizontal
range being the last ploughed. You can choose the best left and right range independently from the two transitions for each range,
though I am not sure of a proof why.
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

const int mxn = 2002;
int n, m, k;
int a[mxn][mxn], s[mxn][mxn], dpl[mxn][mxn], dpr[mxn][mxn];

int f(int x, int y, int X, int Y){
	if(x > X || y > Y) return 0;
	return s[X][Y] - s[X][y - 1] - s[x - 1][Y] + s[x - 1][y - 1];
}

int sol(){
	int ret = n + m - 1;
	for(int i = 1; i <= n; i++) dpr[0][i] = dpr[i][n + 1] = m + 1;
	dpl[0][n] = dpl[1][n + 1] = 1;
	dpr[0][n] = dpr[1][n + 1] = m;
	
	for(int i = 1; i <= n; i++)
	for(int j = n; j >= i; j--){
		dpl[i][j] = 0, dpr[i][j] = m + 1;
		if(f(i - 1, dpl[i - 1][j], i - 1, dpr[i - 1][j]) <= k){
			dpl[i][j] = max(dpl[i][j], dpl[i - 1][j]);
			dpr[i][j] = min(dpr[i][j], dpr[i - 1][j]);
		}
		if(f(j + 1, dpl[i][j + 1], j + 1, dpr[i][j + 1]) <= k){
			dpl[i][j] = max(dpl[i][j], dpl[i][j + 1]);
			dpr[i][j] = min(dpr[i][j], dpr[i][j + 1]);
		}
		if(!dpl[i][j] || dpr[i][j] > m) continue;
		
		while(dpl[i][j] <= dpr[i][j] && f(i, dpl[i][j], j, dpl[i][j]) <= k) dpl[i][j]++;
		while(dpl[i][j] <= dpr[i][j] && f(i, dpr[i][j], j, dpr[i][j]) <= k) dpr[i][j]--;
		if(dpl[i][j] > dpr[i][j]) ret = min(ret, m + n - (j - i + 1));
	}
	
	return ret;	
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> k >> m >> n;
	
	for(int i = 1; i <= n + 1; i++)
	for(int j = 1; j <= m + 1; j++){
		if(i <= n && j <= m) cin >> a[i][j];
		s[i][j] = a[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
	}
	
	int ret = sol();
	
	swap(n, m);
	for(int i = 1; i <= max(n, m) + 1; i++)
	for(int j = i; j <= max(n, m) + 1; j++){
		swap(a[i][j], a[j][i]);
		swap(s[i][j], s[j][i]);
	}
	
	ret = min(ret, sol());
	
	cout << ret << endl;

	return 0;
}

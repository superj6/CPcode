#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 2502;
int n, m;
int a[maxn][maxn], b[maxn][maxn];

bool solve(int x, int y){
	memset(b, 0, sizeof(b));
	for(int i = x; i <= n; i++){
		for(int j = y; j <= m; j++){
			if(a[i][j] - a[i - x][j] - a[i][j - y] + a[i - x][j - y] == x * y){
				b[i - x + 1][j - y + 1]++;
				b[i - x + 1][j + 1]--;
				b[i + 1][j - y + 1]--;
				b[i + 1][j + 1]++;
			}
		}
	}
	
	int amt = a[n][m];
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
			amt -= (b[i][j] > 0);
		}
	}
	return amt == 0;
}

int solveh(int x){
	int l = 0, r = n + 1;
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(solve(mid, x)) l = mid;
		else r = mid;
	}
	return l;
}

int solvew(int x){
	int l = 0, r = m + 1;
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(solve(x, mid)) l = mid;
		else r = mid;
	}
	return l;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			char c;
			cin >> c;
			a[i][j] = c - '0' + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
		}
	}
	
	int ret = 0;
	for(int i = 1; i <= n && solve(i, 1); i++){
		int x = solvew(i);
		i = solveh(x);
		ret = max(ret, x * i);
	}
	
	cout << ret << endl;

	return 0;
}
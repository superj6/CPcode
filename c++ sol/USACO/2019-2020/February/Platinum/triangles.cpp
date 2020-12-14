#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 901;
int n;
int a[maxn][maxn], s[maxn][maxn];
int dx[4] = {1, -1, -1, 1};
int dy[4] = {1, 1, -1, -1};

int main(){
	freopen("triangles.in", "r", stdin);
	freopen("triangles.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = n + 1; i <= 2 * n; i++)
	for(int j = n + 1; j <= 2 * n; j++){
		char c;
		cin >> c;
		a[i][j] = c == '*';
	}
	
	int ret = 0;
	for(int t = 0; t < 4; t++){
		memset(s, 0, sizeof(s));
		for(int i = (1 - 3 * n) * (dx[t] - 1) / 2 + 1; 1 <= i && i <= 3 * n; i += dx[t])
		for(int j = (1 - 3 * n) * (dy[t] - 1) / 2 + 1; 1 <= j && j <= 3 * n; j += dy[t]){
			s[i][j] = a[i][j];
			s[i][j] += s[i - dx[t]][j - dy[t]];
		}
		
		for(int k = 1; k < n; k++)
		for(int i = n + 1; i <= 2 * n; i++)
		for(int j = n + 1; j <= 2 * n; j++){
			if(a[i][j] && a[i + k * dx[t]][j + k * dy[t]]){
				ret += s[i + k * (dx[t] + dx[(t + 1) % 4])][j + k * (dy[t] + dy[(t + 1) % 4])];
				ret -= s[i + k * dx[(t + 1) % 4]][j + k * dy[(t + 1) % 4]];
			}
		}
	}
	
	cout << ret << endl;

	return 0;
}
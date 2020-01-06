#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iomanip>
#include <math.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

int cp(long long x, long long y, int X, int Y){
	return x * Y == X * y ? 0 : x * Y < X * y ? -1 : 1;
}

int il(int x1, int y1, int X1, int Y1, int x2, int y2, int X2, int Y2){
	int a = cp(X1 - x1, Y1 - y1, x2 - x1, y2 - y1);
	int b = cp(X1 - x1, Y1 - y1, X2 - x1, Y2 - y1);
	int c = cp(X2 - x2, Y2 - y2, x1 - x2, y1 - y2);
	int d = cp(X2 - x2, Y2 - y2, X1 - x2, Y1 - y2);
	return a && b && c && d && a != b && c != d;
}

const int maxn = 408, p = 1000000007;
int n, s, m;
int a[maxn], b[maxn];
double dp[maxn][maxn];

int gc(int x, int y, int X, int Y){
	return il(x, y, X, Y, 0, 0, p, 1) ? cp(x, y, p, 1) : 0;
}

void up(int i, int j, double d, int c){
	c &= 1;
	dp[i][j + c * m] = min(dp[i][j + c * m], d);
	dp[j + c * m][i] = min(dp[j + c * m][i], d);
	dp[i + m][j + (1 - c) * m] = min(dp[i + m][j + (1 - c) * m], d);
	dp[j + (1 - c) * m][i + m] = min(dp[j + (1 - c) * m][i + m], d);
}

void di(long long x, long long y, int X, int Y, int s, double &d){
	for(int i = 2 * n; i < 2 * n + 2; i++){
		if(il(x, y, X, Y, a[i] * s, b[i] * s, a[i + 2] * s, b[i + 2] * s)){
			return;
		}
	}
	d = sqrt((X - x) * (X - x) + (Y - y) * (Y - y)) / s;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(6);
	
	cin >> n >> s;
	m = 2 * n + 4;
	
	for(int i = 0; i < n; i++){
		cin >> a[2 * i] >> b[2 * i] >> a[2 * i + 1] >> b[2 * i + 1];
	}
	a[2 * n] = a[2 * n + 1] = b[2 * n] = b[2 * n + 3] = s;
	a[2 * n + 2] = a[2 * n + 3] = b[2 * n + 1] = b[2 * n + 2] = -s;
	
	for(int i = 0; i < 2 * m; i++)
	for(int j = 0; j < 2 * m; j++){
		dp[i][j] = 8 * s;
	}
	/*
	for(int i = 0; i < n; i++)
	for(int j = 0; j < i; j++){
		if(il(a[2 * i], b[2 * i], a[2 * i + 1], b[2 * i + 1], a[2 * j], b[2 * j], a[2 * j + 1], b[2 * j + 1])){
			for(int k = 0; k < 4; k++){
				up(2 * i + k % 2, 2 * j + k / 2, 0, gc(a[2 * i + k % 2], b[2 * i + k % 2], a[2 * j + k / 2], b[2 * j + k / 2]));
			}
		}
	}
	*/
	for(int i = 0; i < m; i++)
	for(int j = 0; 2 * j < m; j++){
		double d = 8 * s;
		for(int k = 2 * j; k < 2 * j + 2; k++, d = 8 * s){
			di(a[i], b[i], a[k], b[k], 1, d);
			if(d < 8 * s){
				up(i, k, d, gc(a[i], b[i], a[k], b[k]));
			}
		}
		if(j < n){
			int bx = a[2 * j + 1] - a[2 * j], by = b[2 * j + 1] - b[2 * j];
			int bm = bx * bx + by * by, adb = (a[i] - a[2 * j]) * bx + (b[i] - b[2 * j]) * by;
			if(0 <= adb && adb <= bm){
				int cx = adb * bx + a[2 * j] * bm, cy = adb * by + b[2 * j] * bm;
				di(a[i] * bm, b[i] * bm, cx, cy, bm, d);
				if(d < 8 * s){
					for(int k = 2 * j; k < 2 * j + 2; k++){
						up(i, k, d, gc(a[i] * bm, b[i] * bm, cx, cy) + gc(cx, cy, a[k] * bm, b[k] * bm));
					}
				}
			}
		}
	}
	
	for(int k = 0; k < 2 * m; k++)
	for(int i = 0; i < 2 * m; i++)
	for(int j = 0; j < 2 * m; j++){
		dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
	}
	
	double ret = 8 * s;
	for(int i = 0; i < m; i++){
		ret = min(ret, dp[i][i + m]);
	}
	
	cout << ret << endl;

	return 0;
}
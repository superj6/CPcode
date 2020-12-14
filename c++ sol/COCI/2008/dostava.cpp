#include <iostream>
#include <cstdio>
#include <algorithm>
#include <array>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

typedef array<array<int, 2>, 2> T;

T operator+(T x, T y){
	T ret;
	for(int i = 0; i < 2; i++)
	for(int j = 0; j < 2; j++){
		ret[i][j] = min(x[i][0] + y[0][j], x[i][1] + y[1][j]);
	}
	return ret;
}

const int inf = 0x3f3f3f3f;
const int mxn = 2001, mxm = 201, k = 11;
int n, m, q;
int a[mxn][mxm], s[mxn][2];
T d[k][mxn];

int f(int t, int x, int y){
	return t ? a[x][m - 1] - a[x][y - 1] : a[x][y] - a[x][1];
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> a[i][j];
			a[i][j] += a[i][j - 1];
		}
		for(int j = 0; j < 2; j++){
			int x = 1 + j * (m - 1);
			s[i][j] = (d[0][i][j][j] = a[i][x] - a[i][x - 1]) + s[i - 1][j];
		}
	}
	
	for(int i = 1; i <= n; i++){
		int dd = inf;
		for(int j = 1; j <= n; j++){
			int c = a[j][m - 1] - a[j][!!~-m];
			for(int l = 0; l < 2; l++) c += s[max(i, j)][l] - s[min(i, j) - 1][l];
			dd = min(dd, c);
		}
		for(int j = 0; j < 2; j++) d[0][i][j][!j] = dd;
	}
	
	for(int i = 1; i < k; i++)
	for(int j = 1; j + (1 << i) <= n + 1; j++){
		d[i][j] = d[i - 1][j] + d[i - 1][j + (1 << (i - 1))];
	}
	
	cin >> q;
	
	ll ret = a[1][1];
	for(int i = 0, x = 1, y = 1, fx, fy; i < q; i++, x = fx, y = fy){
		cin >> fx >> fy;
		int cur = x == fx ? a[x][max(y, fy)] - a[x][min(y, fy) - 1] : inf;
		
		T dd = {0, inf, inf, 0};
		for(int j = k - 1, l = min(x, fx); ~j; j--){
			if(l + (1 << j) - 1 <= max(x, fx)) dd = dd + d[j][l], l += (1 << j);
		}
		
		for(int j = 0; j < 2; j++)
		for(int l = 0; l < 2; l++){
			int t = j, ft = l;
			if(x > fx) swap(t, ft);
			cur = min(cur, dd[j][l] + f(t, x, y) + f(ft, fx, fy));
		}
		ret += cur - (a[x][y] - a[x][y - 1]);
	}
	
	cout << ret << endl;

	return 0;
}
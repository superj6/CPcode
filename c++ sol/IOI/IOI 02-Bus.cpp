/*

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

const int mxn = 500;
int n;
int x[mxn], y[mxn], it[mxn];
int d[mxn][mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> x[i] >> y[i];
		it[i] = i;
		for(int j = 0; j < i; j++){
			d[i][j] = d[j][i] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
		}
	}
	
	int ret = 0x3f3f3f3f;
	for(int i = 0; i < n; i++){
		sort(it, it + n, [&](int u, int v){
			return d[i][u] > d[i][v];
		});
		for(int j = 0; j < n; j++)
		for(int l = 0, k = 0; l < n; l++){
			if(d[j][it[k]] < d[j][it[l]]){
				ret = min(ret, d[i][j] + d[j][it[k]] + d[i][it[l]]);
				k = l;
			}
		}
	}
	
	cout << ret << endl;

	return 0;
}

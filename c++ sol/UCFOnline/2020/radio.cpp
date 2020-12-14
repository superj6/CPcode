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

const int mxn = 100;
int n, m, q;
int a[mxn];
int d[mxn][mxn];

int rd(){
	double x;
	cin >> x;
	return x * 10;
}

int id(int x){
	return lower_bound(a, a + n, x) - a;
}

void answer(){
	cin >> n >> m >> q;
	
	memset(d, 0x3f, sizeof(d));
	for(int i = 0; i < n; i++){
		a[i] = rd();
		d[i][i] = 0;
		d[i][(i + 1) % n] = 1;
		d[(i + 1) % n][i] = 1;
	} 
	
	for(int i = 0; i < m; i++){
		int x = id(rd());
		for(int j = 0; j < n; j++) if(x != j) d[j][x] = 1;
	}
	
	for(int l = 0; l < n; l++)
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		d[i][j] = min(d[i][j], d[i][l] + d[l][j]);
	}
	
	while(q--) cout << d[id(rd())][id(rd())] << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++){
		cout << "Day #" << (i + 1) << ":" << endl;
		answer();
		cout << endl;
	}

	return 0;
}
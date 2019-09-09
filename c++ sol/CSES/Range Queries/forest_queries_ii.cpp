#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

const int maxn = 1001;

struct BIT{
	int bit[maxn];
	
	BIT(){
		memset(bit, 0, sizeof(bit));
	}
	
	void add(int x, int v){
		for(; x < maxn; x += x & -x) bit[x] += v;
	}
 
	int qry(int x){
		int ret = 0;
		for(; x > 0; x -= x & -x) ret += bit[x];
		return ret;
	}
};

int n, q;
BIT bit[maxn];
char grid[maxn][maxn];
 
void add(int x, int y, int v){
	for(; x <= n; x += x & -x) bit[x].add(y, v);
}
 
int qry(int x, int y, int Y){
	int ret = 0;
	for(; x > 0; x -= x & -x) ret += bit[x].qry(Y) - bit[x].qry(y - 1);
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cin >> grid[i][j];
			if(grid[i][j] == '*') add(i, j, 1);
		}
	}
	
	for(int i = 0; i < q; i++){
		int t;
		cin >> t;
		if(t == 1){
			int x, y;
			cin >> x >> y;
			if(grid[x][y] == '*'){
				add(x, y, -1);
				grid[x][y] = '.';
			}else{
				add(x, y, 1);
				grid[x][y] = '*';
			}
		}else{
			int x, y, X, Y;
			cin >> x >> y >> X >> Y;
			cout << (qry(X, y, Y) - qry(x - 1, y, Y)) << endl;
		}
	}

	return 0;
}
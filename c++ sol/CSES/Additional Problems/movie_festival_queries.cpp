#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int m = 1000000, k = 20;
int n, q;
int st[k][m];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	
	for(int i = 0; i < m; i++) st[0][i] = m;
	for(int i = 0; i < n; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		st[0][a] = min(st[0][a], b);
	}
	
	for(int i = m - 2; i >= 0; i--){
		st[0][i] = min(st[0][i], st[0][i + 1]);
	}
	
	for(int i = 1; i < k; i++){
		for(int j = 0; j < m; j++){
			st[i][j] = (st[i - 1][j] < m ? st[i - 1][st[i - 1][j]] : m);
		}
	}
	
	for(int i = 0; i < q; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		int ret = 0;
		for(int j = k - 1; j >= 0; j--){
			if(st[j][a] <= b){
				ret += (1 << j);
				a = st[j][a];
			}
		}
		cout << ret << endl;
	}

	return 0;
}
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'

const long inf = 10000000000007;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, q;
	cin >> n >> m >> q;
	
	long dist[n][n];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			dist[i][j] = (i == j ? 0 : inf);
		}
	}
	
	for(int i = 0; i < m; i++){
		long a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		
		dist[a][b] = dist[b][a] = min(dist[a][b], c);
	}
	
	for(int k = 0; k < n; k++){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	
	for(int i = 0; i < q; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		cout << (dist[a][b] == inf ? -1 : dist[a][b]) << endl;
	}

	return 0;
}
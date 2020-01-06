#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	freopen("fortmoo.in", "r", stdin);
	freopen("fortmoo.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	int grid[n][m];
	
	for(int i = 0; i < n; i++){
		char line[m];
		cin >> line;
		
		for(int j = 0; j < m; j++){
			if(line[j] == 'X'){
				grid[i][j] = -1;
			}else{
				grid[i][j] = 1 + (j > 0 ? grid[i][j - 1] : -1);
			}
		}
	}
	
	int maxv = 0;
	
	for(int j = 0; j < m; j++){
		for(int k = j; k < m; k++){
			int lastrow = -1;
			
			for(int i = 0; i < n; i++){
				if(grid[i][j] == -1 || grid[i][k] == -1) lastrow = -1;
				
				if(j + grid[i][k] >= k){
					if(lastrow == -1){
						lastrow = i;
					}
					
					maxv = max(maxv, (k - j + 1) * (i - lastrow + 1));
				}
			}
		}
	}
	

	cout << maxv << endl;

	return 0;
}
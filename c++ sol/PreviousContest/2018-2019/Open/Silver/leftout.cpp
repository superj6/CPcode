#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

int main(){
	freopen("leftout.in", "r", stdin);
	freopen("leftout.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	int grid[n][n];
	for(int i = 0; i < n; i++){
		cin.ignore();
		for(int j = 0; j < n; j++){
			grid[i][j] = (cin.get() == 'R');
		}
	}
	
	for(int i = 0; i < n; i++){
		if(grid[0][i]){
			for(int j = 0; j < n; j++) grid[j][i] ^= 1;
		}
	}
	for(int i = 0; i < n; i++){
		if(grid[i][0]){
			for(int j = 0; j < n; j++) grid[i][j] ^= 1;
		}
	}
	
	int cnt = 0;
	for(int i = 1; i < n; i++){
		for(int j = 1; j < n; j++){
			cnt += grid[i][j];
		}
	}
	
	if(cnt == (n - 1) * (n - 1)){
		cout << 1 << " " << 1 << endl;
		return 0;
	}else if(cnt == 1){
		for(int i = 1; i < n; i++){
			for(int j = 1; j < n; j++){
				if(grid[i][j]){
					cout << i + 1 << " " << j + 1 << endl;
					return 0;
				}
			}
		}
	}else{
		for(int i = 1; i < n; i++){
			bool test = 1;
			for(int j = 1; j < n; j++){
				test &= grid[i][j];
			}
			if(test){
				cout << i + 1 << " " << 1 << endl;
				return 0;
			}
		}
		for(int i = 1; i < n; i++){
			bool test = 1;
			for(int j = 1; j < n; j++){
				test &= grid[j][i];
			}
			if(test){
				cout << 1 << " " << i + 1 << endl;
				return 0;
			}
		}
	}
	
	cout << -1 << endl;

	return 0;
}
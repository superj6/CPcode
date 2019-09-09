#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const int mod = 1000000007;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	int amt[n][n];
	
	for(int i = 0; i < n; i++){
		char grid[n];
		cin >> grid;
		
		for(int j = 0; j < n; j++){
			if(grid[j] == '*'){
				amt[i][j] = 0;
			}else if(i + j == 0){
				amt[i][j] = 1;
			}else{
				amt[i][j] = 0;
				if(i > 0) amt[i][j] += amt[i - 1][j];
				if(j > 0) amt[i][j] += amt[i][j - 1];
				amt[i][j] %= mod;
			}
		}
	}
	
	cout << amt[n - 1][n - 1] << endl;;

	return 0;
}
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int mod = 1000000007;

int main(){
	ifstream fin ("hopscotch.in");
	ofstream fout ("hopscotch.out");
	
	int r, c, k;
	fin >> r >> c >> k;
	int num[r][c], dp[r][c];
	
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			fin >> num[i][j];
			dp[i][j] = 0;
		} 
	}
	
	dp[0][0] = 1;
	
	
	for(int i = 0; i < r - 1; i++){
		for(int j = 0; j < c - 1; j++){
			if(dp[i][j] == 0) continue;
			for(int in = i + 1; in < r; in++){
				for(int jn = j + 1; jn < c; jn++){
					if(num[in][jn] != num[i][j]) dp[in][jn] = (dp[in][jn] + dp[i][j]) % mod;
				}
			}
		}
	}
	
	fout << dp[r - 1][c - 1] << endl;

	return 0;
}
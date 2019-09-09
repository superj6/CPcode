#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main(){
	ifstream fin ("taming.in");
	ofstream fout ("taming.out");
	
	int n;
	fin >> n;
	int a[n];
	for(int i = 0; i < n; i++){
		fin >> a[i];
	}
	
	int dp[n][n][n + 1];
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= i; j++){
			for(int k = 0; k <= n; k++){
				dp[i][j][k] = 100000;
			}
		}
	}
	
	if(a[0] == 0){
		dp[0][0][1] = 0;
	}else{
		dp[0][0][1] = 1;
	}
	
	for(int i = 1; i < n; i++){
		for(int j = 0; j <= i; j++){
			for(int k = 1; k <= i + 1; k++){
				if(j < i){
					dp[i][j][k] = dp[i - 1][j][k];
				}else{
					for(int h = 0; h < j; h++){
						dp[i][j][k] = min(dp[i][j][k], dp[i - 1][h][k - 1]);
					}
				}
				if(a[i] != i - j) dp[i][j][k]++;
			}
		}
	}
	
	for(int k = 1; k <= n; k++){
		int low = 100000;
		for(int j = 0; j < n; j++){
			low = min(low, dp[n - 1][j][k]);
		}
		fout << low << endl;
	}

	return 0;
}
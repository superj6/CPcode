#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

struct point{
	int x, y;
	
	point(int x, int y){
		this->x = x;
		this->y = y;
	}
};

int main() {
	ifstream fin ("marathon.in");
	ofstream fout ("marathon.out");
	
	int n, k;
	fin >> n >> k;
	
	vector<point> points;
	int dp[n][k + 1];
	dp[0][0] = 0;
	
	
	
	for(int i = 0; i < n; i++){
		int a, b;
		fin >> a >> b;
		
		points.push_back(point(a, b));
		
		if(i == 0) continue;
		
		dp[i][0] = dp[i - 1][0] + abs(points[i].x - points[i - 1].x) + abs(points[i].y - points[i - 1].y); 

		if(i == 1){
			for(int j = 1; j <= k; j++){
				for(int q = 0; q <= j; q++){
					if(q == j){
						dp[q][j] = dp[q][j - 1];
					}else{
						dp[q][j] = 10000000;
					}
				}
			}
			
			continue;
		}

		for(int j = 1; j <= k; j++){
			dp[i][j] = min(dp[i - 2][j - 1] + abs(points[i].x - points[i - 2].x) + abs(points[i].y - points[i - 2].y), dp[i - 1][j] + abs(points[i].x - points[i - 1].x) + abs(points[i].y - points[i - 1].y));
		}
	}
	
	
	int minv = 10000000;
	
	for(int j = 0; j <= k; j++) minv = min(minv, dp[n - 1][j]);
	
	fout << minv << endl;
	
	return 0;
}
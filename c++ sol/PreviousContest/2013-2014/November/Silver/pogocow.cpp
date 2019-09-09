#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int dp[1010][1010];

int main(){
	
  	ifstream fin ("pogocow.in");
	ofstream fout ("pogocow.out");

	int n;
	fin >> n;
	
	vector<pair<int, int>> points(n);
	
	for(int i = 0; i < n; i++){
		fin >> points[i].first >> points[i].second;
	}
	
	sort(points.begin(), points.end());
	
	int maxv = 0;
	

	for(int t = 0; t < 2; t++){
		for(int i = n - 1; i >= 0; i--){
			int val = 0;
			int k = n;
			
			for(int j = 0; j <= i; j++){
				while(k - 1 > i && points[k - 1].first - points[i].first >= points[i].first - points[j].first){
					k--;
					val = max(val, points[k].second + dp[k][i]);
				}
				
				dp[i][j] = val;
			}

			maxv = max(maxv, points[i].second + dp[i][i]);
			
		}
		
		for(int i = 0; i < n; i++) {
    			points[i].first = -points[i].first;
    		}

		reverse(points.begin(), points.end());
	}
	
	fout << maxv << endl;

	return 0;
}
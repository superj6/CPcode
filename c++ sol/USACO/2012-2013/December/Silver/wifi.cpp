#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main(){
	ifstream fin ("wifi.in");
	ofstream fout ("wifi.out");
	
	int n, a, b;
	fin >> n >> a >> b;
	int dist[n], dp[n];
	
	for(int i = 0; i < n; i++){
		fin >> dist[i];
	}
	
	sort(dist, dist+n);
	
	for(int i = 0; i < n; i++){
		dp[i] = 2 * a + b * (dist[i] - dist[0]);
		
		for(int j = 0; j < i; j++){
			dp[i] = min(dp[i], dp[j] + 2 * a + b * (dist[i] - dist[j + 1]));
		}
	}
	
	fout << dp[n - 1] / 2 << (dp[n - 1] % 2 == 1 ? ".5" : "") << endl;

	return 0;
}
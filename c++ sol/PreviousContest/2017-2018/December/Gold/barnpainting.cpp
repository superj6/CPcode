#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int mod = 1000000007;

int n, k;
vector<vector<int>> graph;
vector<int> colored;
vector<bool> visited;
vector<vector<int>> dp;

long long recurse(int barn, int color){
	if(dp[barn][color] >= 0) return dp[barn][color];
	
	visited[barn] = true;
	
	//cout << barn << " " << color << endl;
	
	long long output = 1;
	
	for(int i = 0; i < graph[barn].size(); i++){
		
		if(visited[graph[barn][i]]) continue;
		
		if(colored[graph[barn][i]] == -1){
			long long sum = 0;
			for(int j = 0; j < 3; j++){
				if(color == j) continue;
				sum = (sum + recurse(graph[barn][i], j)) % mod;
			}
			
			output = (output * sum) % mod;
			
		}else if(colored[graph[barn][i]] == color){
			
			output = 0;
		
		}else{
			
			output = (output * recurse(graph[barn][i], colored[graph[barn][i]])) % mod;
			
		}	
		
		if(output == 0) break;
	}
	
	visited[barn] = false;
	
	dp[barn][color] = output;
	
	return output;
}

int main(){
	ifstream fin ("barnpainting.in");
	ofstream fout ("barnpainting.out");
	
	fin >> n >> k;
	graph.resize(n);
	colored.resize(n);
	visited.resize(n);
	dp.resize(n);
	
	colored[0] = -1;
	visited[0] = false;
	
	dp[0].resize(3);
	dp[0][0] = -1, dp[0][1] = -1, dp[0][2] = -1;
	
	for(int i = 1; i < n; i++){
		colored[i] = -1;
		visited[i] = false;
		
		dp[i].resize(3);
		dp[i][0] = -1, dp[i][1] = -1, dp[i][2] = -1;
		
		int a, b;
		fin >> a >> b;
		a--, b--;
		graph[a].push_back(b), graph[b].push_back(a);
	}
	
	for(int i = 0; i < k; i++){
		int a, b;
		fin >> a >> b;
		a--, b--;
		colored[a] = b;
	}
	
	long long total;
	
	if(colored[0] == -1){
		total = (recurse(0, 0) + recurse(0, 1) + recurse(0, 2)) % mod;
	}else{
		total = recurse(0, colored[0]) % mod;
	}
	
	fout << total << endl;

	return 0;
}
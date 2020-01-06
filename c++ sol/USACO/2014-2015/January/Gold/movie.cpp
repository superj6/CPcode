#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <iterator>
using namespace std;

int bitset(int num){
	int ans = 0;
	while(num > 0){
		ans += num & 1;
		num = num >> 1;
	}
	
	return ans;
}

int main(){
	ifstream fin ("movie.in");
	ofstream fout ("movie.out");
	
	int n, l;
	fin >> n >> l;
	
	int dur[n], dp[1 << n];
	vector<int> start[n];
	
	for(int i = 0; i < n; i++){
		fin >> dur[i];
		
		int m;
		fin >> m;
		
		for(int j = 0; j < m; j++){
			int st;
			fin >> st;
			
			start[i].push_back(-st);
		}
		
		reverse(start[i].begin(), start[i].end());
	}
	
	for(int i = 0; i < 1 << n; i++) dp[i] = -1;
	dp[0] = 0;
	
	queue<pair<int, int>> q;
	q.push(make_pair(0, 0));
	
	while(!q.empty()){
		int cur = q.front().first, t = q.front().second;
		q.pop();
		
		if(dp[cur] >= l){
			fout << bitset(cur) << endl;
			return 0;
		}
		
		if(dp[cur] != t) continue;
		
		for(int i = 0; i < n; i++){
			int next = cur | (1 << i);
			if(next == cur) continue;
			
			vector<int>::iterator itr = lower_bound(start[i].begin(), start[i].end(), -t);
			if(itr == start[i].end() || -(*itr) + dur[i] < t) continue;
			
			int tn = -(*itr) + dur[i];
			
			if(tn > dp[next]){
				dp[next] = tn;
				q.push(make_pair(next, tn));
			}
		}
	}
	
	fout << -1 << endl;

	return 0;
}
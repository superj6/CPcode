#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, long long>
 
map<int, int, greater<int>> dp[2];
vector<pi> a[2];
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, x;
	cin >> n >> x;
 
	dp[0][0] = dp[1][0] = 1;
	for(int i = 0; i < n; i++){
		int a, t;
		cin >> a;
		t = 2 * i < n ? 0 : 1;
		
		for(auto it = dp[t].begin(); it != dp[t].end(); it++){
			if(it->first + a <= x) dp[t][it->first + a] += it->second;
		}
	}
	
	for(int i = 0; i < 2; i++){
		for(auto it = dp[i].begin(); it != dp[i].end(); it++){
			a[i].push_back({it->first, it->second});
		}
	}
	
	reverse(a[0].begin(), a[0].end());
	
	long long ret = 0;
	for(int i = 0, j = 0; i < a[0].size(); i++){
		while(j < a[1].size() && a[0][i].first + a[1][j].first > x) j++;
		if(j == a[1].size()) break;
		if(a[0][i].first + a[1][j].first == x) ret += a[0][i].second * a[1][j].second;
	}
	
	cout << ret << endl;
 
	return 0;
}
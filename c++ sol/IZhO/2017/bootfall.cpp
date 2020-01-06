#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 500, m = 250001;
int n;
int a[maxn], dp[m];
set<int> cur;
int s;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	dp[0] = 1;
	for(int i = 0; i < n; i++){
		cin >> a[i];
		s += a[i];
		
		for(int j = m - a[i] - 1; j >= 0; j--){
			dp[j + a[i]] += dp[j];
		}
	}
	
	if(s % 2 || !dp[s / 2]){
		cout << 0 << endl;
		cout << endl;
		return 0;
	}
	
	for(int i = 1; i < m; i++) cur.insert(i);
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m - a[i]; j++){
			dp[j + a[i]] -= dp[j];
		}
		
		for(auto it = cur.begin(); it != cur.end();){
			int x = *it;
			it++;
			if((s - a[i] + x) % 2 || !dp[(s - a[i] + x) / 2]) cur.erase(x);
		}
		
		for(int j = m - a[i] - 1; j >= 0; j--){
			dp[j + a[i]] += dp[j];
		}
	}
	
	vector<int> ans;
	for(auto it = cur.begin(); it != cur.end(); it++) ans.push_back(*it);
	
	cout << ans.size() << endl;
	if(!ans.empty()){
		cout << ans[0];
		for(int i = 1; i < ans.size(); i++) cout << " " << ans[i];
	}
	cout << endl;

	return 0;
}
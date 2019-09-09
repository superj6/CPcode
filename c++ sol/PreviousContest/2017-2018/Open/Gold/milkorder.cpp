#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
#define endl '\n'

const int maxn = 100000, maxm = 50000;
int n, m;
vector<int> graph[maxn], order[maxm];

vector<int> works(int x){
	int cnt[n];
	vector<int> rules[n];
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i < x; i++){
		for(int j = 0; j < order[i].size() - 1; j++){
			
			rules[order[i][j]].push_back(order[i][j + 1]);
			cnt[order[i][j + 1]]++;
		}
	}
	
	priority_queue<int, vector<int>, greater<int>> pq;
	for(int i = 0; i < n; i++){
		if(cnt[i] == 0) pq.push(i);
	}
	
	vector<int> ans;
	while(!pq.empty()){
		int c = pq.top();
		pq.pop();
		
		ans.push_back(c + 1);
		
		for(int j : rules[c]){
			cnt[j]--;
			if(!cnt[j]) pq.push(j);
		}
	}
	
	return ans;
}

int main(){
	freopen("milkorder.in", "r", stdin);
	freopen("milkorder.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int k;
		cin >> k;
		order[i].resize(k);
		for(int j = 0; j < k; j++){
			cin >> order[i][j];
			order[i][j]--;
		}
	}
	
	int l = 0, r = m + 1;
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(works(mid).size() == n) l = mid;
		else r = mid;
	}
	
	vector<int> ans = works(l);
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}
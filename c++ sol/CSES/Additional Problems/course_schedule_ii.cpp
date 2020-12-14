#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
 
const int maxn = 100000;
int n, m;
priority_queue<int> pq;
int cnt[maxn];
vector<int> graph[maxn];
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
 
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		graph[b].push_back(a);
		cnt[a]++;
	}
	
	for(int i = 0; i < n; i++){
		if(cnt[i] == 0) pq.push(i);
	} 
	
	vector<int> ans;
	for(int i = 0; i < n; i++){
		int c = pq.top();
		pq.pop();
		
		ans.push_back(c + 1);
		
		for(int x : graph[c]){
			cnt[x]--;
			if(cnt[x] == 0) pq.push(x);
		}
	}
	
	reverse(ans.begin(), ans.end());
	
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << " " << ans[i];
	cout << endl;
 
	return 0;
}
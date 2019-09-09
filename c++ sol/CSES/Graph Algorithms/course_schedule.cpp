#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'

const int maxn = 100000;
int n, m;
queue<int> q;
int cnt[maxn];
vector<int> ans;
vector<int> graph[maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		graph[a].push_back(b);
		cnt[b]++;
	}
	
	for(int i = 0; i < n; i++) if(cnt[i] == 0) q.push(i);
	
	for(int i = 0; i < n; i++){
		if(q.empty()){
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
		
		int c = q.front();
		q.pop();
		
		ans.push_back(c + 1);
		
		for(int x : graph[c]){
			cnt[x]--;
			if(cnt[x] == 0) q.push(x);
		}
	}
	
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 100000;
int cnt[maxn], works[maxn], rules[maxn];
vector<int> edges[maxn], after[maxn];

void dfs(int cur){
	works[cur] = 0;
	
	for(int i = 0; i < edges[cur].size(); i++){
		int next = edges[cur][i];
		
		if(works[next] && after[next].size() == 0) dfs(next);
	}
}

int main(){
	freopen("gathering.in", "r", stdin);
	freopen("gathering.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		cnt[i] = 0, works[i] = 0, rules[i] = 0;
	}
	
	for(int i = 0; i < n - 1; i++){
		int x, y;
		cin >> x >> y;
		x--, y--;
		
		cnt[x]++, cnt[y]++;
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		after[a].push_back(b);
		rules[b]++;
	}
	
	queue<int> q;
	
	for(int i = 0; i < n; i++){
		if(!rules[i] && cnt[i] <= 1){
			works[i] = 1;
			q.push(i);
		}
	}
	
	for(int i = 0; i < n - 1; i++){
		if(q.empty()){
			for(int i = 0; i < n; i++) cout << 0 << endl;
			return 0;
		}
		
		int cur = q.front();
		q.pop();
		
		for(int i = 0; i < edges[cur].size(); i++){
			int next = edges[cur][i];
			cnt[next]--;
			
			if(cnt[next] <= 1 && rules[next] == 0 && !works[next]){
				works[next] = 1;
				q.push(next);
			}
		}
		
		for(int i = 0; i < after[cur].size(); i++){
			int next = after[cur][i];
			rules[next]--;
			
			if(cnt[next] <= 1 && rules[next] == 0 && !works[next]){
				works[next] = 1;
				q.push(next);
			}
		}
	}
	
	int final = q.front();
	q.pop();
	
	dfs(final);
	
	for(int i = 0; i < n; i++) cout << !works[i] << endl;

	return 0;
}
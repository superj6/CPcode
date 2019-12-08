/*
	The problem can be simplified to given a tree in which you have to remove nodes such that the tree stays connected and 
there are constraints such that you must remove one node before the other, compute which nodes could be the final node left on
the tree. A key thing to notice is that all nodes that are a solution form a connected group in a tree as once you have an
unconstrained group you can take them off in any order, and none of them in the group can be a constraint on another node.
This means if you can find one node that is a solution you can dfs and find the others. To find one solution, you can do
something very similar to topological sort where you insert edges with no constraints and are leaves of the current tree into
a queue. Then, as you pop nodes off of the queue remove the a constraint from each of the nodes it is constraining and an edge
from each of the node that neighbors it. Any node that now works after removing such and hasn't been visited can be added to the 
queue. The complexity of that is O(n).
*/

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

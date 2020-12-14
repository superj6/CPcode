#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n;
vector<int> graph[maxn];

int dfs(int c, int p, int x){
	if(n == 1) return 0;
	multiset<int> cur;
	for(int i : graph[c]){
		if(i == p) continue;
		int v = dfs(i, c, x);
		if(!v) return 0;
		cur.insert(v);
	}
	while(!cur.empty()){
		int v = *cur.begin();
		cur.erase(cur.begin());
		if(!c && v >= x) return 1;
		if(c && (cur.empty() || (cur.size() == 1 && *cur.begin() >= x))) return v + 1;
		auto it = cur.lower_bound(x - v);
		if(it == cur.end()) return 0;
		cur.erase(it);
	}
	return 1;
}

int main(){
	freopen("deleg.in", "r", stdin);
	freopen("deleg.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	int l = 0, r = n + 1;
	
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(dfs(0, -1, mid)) l = mid;
		else r = mid;
	}
	
	cout << l << endl;

	return 0;
}
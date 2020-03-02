#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n;
vector<int> graph[maxn];

bool works(vector<int> &a, int z, int x){
	for(int l = 0, r = a.size() - 1; l < r; l++, r--){
		if(a[l += (l == z)] + a[r -= (r == z)] < x) return 0;
	}
	return 1;
}

int dfs(int c, int p, int x){
	if(n == 1) return 0;
	vector<int> cur;
	for(int i : graph[c]){
		if(i == p) continue;
		int v = dfs(i, c, x);
		if(!v) return 0;
		cur.push_back(v);
	}
	sort(cur.begin(), cur.end());
	if(cur.size() & 1){
		if(!works(cur, 0, x)) return 0;
	}else{
		if(cur.empty()) return 1;
		if(!works(cur, -1, x)) return 0;
		int ret = cur[0];
		cur.erase(cur.begin());
		if(!works(cur, 0, x)) return 1;
	}
	int l = 0, r = cur.size();
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(works(cur, mid, x)) l = mid;
		else r = mid;
	}
	return cur[l] + 1;
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
	
	int l = 0, r = n;
	
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(dfs(0, -1, mid)) l = mid;
		else r = mid;
	}
	
	cout << l << endl;

	return 0;
}

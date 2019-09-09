#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 100000;
int n, m;
int t[maxn], p[maxn];
vector<int> graph[maxn];

void dfs(int c){
	for(int i : graph[c]){
		if(t[i] <= t[c]){
			t[i] = t[c] + 1;
			p[i] = c;
			dfs(i);
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
	}
	
	t[0] = 1;
	p[0] = -1;
	dfs(0);
	
	if(t[n - 1] == 0){
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}
	
	vector<int> ans;
	
	for(int i = n - 1; i != -1; i = p[i]) ans.push_back(i + 1);
	reverse(ans.begin(), ans.end());
	
	cout << t[n - 1] << endl;
	cout << ans[0];
	for(int i = 1; i < t[n - 1]; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}
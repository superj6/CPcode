#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 200000;
int n, m;
bool used[maxn];
int din[maxn], dout[maxn];
vector<pair<int, int>> graph[maxn];
vector<int> ans;

void path(int c){
	for(pair<int, int> i : graph[c]){
		if(used[i.second]) continue;
		used[i.second] = 1;
		path(i.first);
	}
	ans.push_back(c + 1);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		din[b]++, dout[a]++;
		graph[a].push_back({b, i});
	}
	
	if(din[0] + 1 != dout[0] || din[n - 1] != dout[n - 1] + 1){
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}
	for(int i = 1; i < n - 1; i++){
		if(din[i] != dout[i]){
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
	}
	
	path(0);
	reverse(ans.begin(), ans.end());
	if(ans.size() != m + 1 || ans[0] != 1 || ans[m] != n){
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}
	
	cout << ans[0];
	for(int i = 1; i <= m; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}
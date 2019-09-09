#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <string.h>
using namespace std;
#define endl '\n'

const int maxn = 200000;
int n, m;
int scc[maxn];
char ans[maxn];
bool used[maxn];
stack<int> stk;
vector<int> graph[2][maxn];
int s;

void dfs(int c, int x){
	used[c] = 1;
	
	for(int i : graph[x][c]){
		if(!used[i]) dfs(i, x);
	}
	
	if(!x){
		stk.push(c);
	}else{
		scc[c] = s;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		int a, b;
		char c, d;
		cin >> c >> a >> d >> b;
		a--, b--;
		if(c == '-') a += m;
		if(d == '-') b += m;
		
		graph[0][(a + m) % (2 * m)].push_back(b);
		graph[0][(b + m) % (2 * m)].push_back(a);
		
		graph[1][b].push_back((a + m) % (2 * m));
		graph[1][a].push_back((b + m) % (2 * m));
	}
	
	for(int i = 0; i < 2 * m; i++){
		if(!used[i]) dfs(i, 0);
	}
	
	memset(used, 0, sizeof(used));
	
	while(!stk.empty()){
		int c = stk.top();
		stk.pop();
		
		if(used[c]) continue;
		dfs(c, 1);
		s++;
	}
	
	for(int i = 0; i < m; i++){
		if(scc[i + m] < scc[i]){
			ans[i] = '+';
		}else if(scc[i] < scc[i + m]){
			ans[i] = '-';
		}else{
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
	}
	
	cout << ans[0];
	for(int i = 1; i < m; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}
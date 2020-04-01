#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
 
const int maxn = 100000;
int n, m;
priority_queue<int, vector<int>, greater<int>> pq;
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
		
		graph[a].push_back(b);
		cnt[b]++;
	}
	
	for(int i = 0; i < n; i++){
		if(cnt[i] == 0) pq.push(i);
	} 
	
	for(int i = 0; i < n; i++){
		int c = pq.top();
		pq.pop();
		
		cout << c + 1;
		if(i != n - 1) cout << " ";
		
		for(int x : graph[c]){
			cnt[x]--;
			if(cnt[x] == 0) pq.push(x);
		}
	}
	cout << endl;
 
	return 0;
}
//#include "Anthony.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define vi vector<int>

const int maxn = 20000, k = 6;
int d[maxn];
vi graph[maxn];
queue<int> q;
int s[k] = {0, 0, 1, 0, 1, 1};
vi ans;

vi Mark(int n, int m, int a, int b, vi u, vi v){
	ans.resize(m);
	for(int i = 0; i < m; i++){
		graph[u[i]].push_back(i);
		graph[v[i]].push_back(i);
	}
	d[0] = 1;
	if(a > 2){
		q.push(0);
		while(!q.empty()){
			int c = q.front();
			q.pop();
			for(int i : graph[c]){
				int j = u[i] ^ v[i] ^ c; 
				if(!d[j]){
					d[j] = d[c] + 1;
					q.push(j);
				}
				if(d[j] == d[c] || d[j] == d[c] + 1){
					ans[i] = d[c] % 3;
				}
			}
		}
	}else{
		function<void(int, int)> dfs = [&](int c, int p){
			for(int i : graph[c]){
				int j = u[i] ^ v[i] ^ c;
				if(j != p){
					ans[i] = s[d[c]];
					d[j] = graph[j].size() > 2 ? (ans[i] ^ 1) << 1 : (d[c] + 1) % k;
					dfs(j, c);
				}
			}
		};
		dfs(0, -1);
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	

	return 0;
}
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<long long, long long>

const int maxn = 50;
int n, m;
int deg[maxn];
int used1[maxn], used2[maxn], used3[maxn], used4[maxn];
vector<int> graph[maxn];

bool works(int c, int p){
	used4[c] = 1;
	bool ret = 0;
	for(int i : graph[c]){
		if(i == p || used1[i] || used2[i]) continue;
		if(used4[i] || works(i, c)){
			ret = 1;
			break;
		}
	}
	used4[c] = 0;
	return ret;
}

int dfs(int c){
	int ret = c;
	for(int i : graph[c]){
		if(used1[i] || used2[i] || used3[i] == used3[c]) continue;
		used3[i] = used3[c];
		int nc = dfs(i);
		if(deg[nc] > deg[ret]) ret = nc; 
	}
	return ret;
}

pi solve2(int c){
	pi ret = {1, 1};
	used2[c]++;
	for(int i : graph[c]){
		if(used1[i] || used2[i]) continue;
		used1[i] = used1[c];
		pi cur = solve2(i);
		ret.first *= cur.second;
		ret.second *= cur.first + cur.second;
	}
	used2[c]--;
	//cout << (c + 1) << ": " << ret.first << " " << ret.second << endl;
	return ret;
}

long long solve(int c){
	/*
	cout << c + 1 << endl;
	for(int i = 0; i < n; i++) cout << used1[i] << " ";
	cout << endl;
	for(int i = 0; i < n; i++) cout << used2[i] << " ";
	cout << endl;
	for(int i = 0; i < n; i++) cout << used3[i] << " ";
	cout << endl;
	*/
	
	long long ret1 = 1, ret2 = 1;
	for(int i : graph[c]){
		deg[i]--;
		used2[i]++;
		if(used1[i] || used2[i] > 1) continue;
		for(int j : graph[i]){
			deg[j]--;
		}
	}
	for(int i : graph[c]){
		if(used1[i] || used2[i] > 1) continue;
		for(int j : graph[i]){
			if(used1[j] || used2[j] || used3[j] != used3[c]) continue;
			used3[j] = !used3[c];
			int nc = dfs(j);
			if(works(nc, -1)){
				used2[nc] = 2;
				ret2 *= solve(nc);
				used2[nc] = 0;
			}else{
				pi cur = solve2(nc);
				ret2 *= cur.first + cur.second;
			}
		}
	}
	for(int i : graph[c]){
		used2[i]--;
		if(used1[i] || used2[i]) continue;
		for(int j : graph[i]){
			deg[j]++;
			if(!used1[j] && !used2[j] && used3[j] != used3[c]){
				used3[j] = used3[c];
				dfs(j);
			}
		}
	}
	//cout << (c + 1) << " ----------" << endl;
	for(int i : graph[c]){
		if(used1[i] || used2[i] || used3[i] != used3[c]) continue;
		used3[i] = !used3[c];
		int nc = dfs(i);
		if(works(nc, -1)){
			used1[nc] = used1[c];
			used2[nc] = 2;
			ret1 *= solve(nc);
			used2[nc] = 0;
		}else{
			used1[nc] = used1[c];
			pi cur = solve2(nc);
			ret1 *= cur.first + cur.second;
		}
	}
	for(int i : graph[c]){
		deg[i]++;
		if(!used1[i] && !used2[i] && used3[i] != used3[c]){
			used3[i] = used3[c];
			dfs(i);
		}
	}
	
	/*
	cout << (c + 1) << ": " << ret1 << " " << ret2 << endl;
	for(int i = 0; i < n; i++) cout << used1[i] << " ";
	cout << endl;
	for(int i = 0; i < n; i++) cout << used2[i] << " ";
	cout << endl;
	for(int i = 0; i < n; i++) cout << used3[i] << " ";
	cout << endl;
	*/
	return ret1 + ret2;
}



int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int x, y;
		cin >> x >> y;
		x--, y--;
		
		deg[x]++, deg[y]++;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	
	long long ret = 1;
	for(int i = 0; i < n; i++){
		if(!used1[i]){
			if(works(i, -1)){
				int nc = dfs(i);
				dfs(i);
				used1[nc] = 1;
				ret *= solve(nc);
				//cout << "x" << endl;
			}else{
				used1[i] = 1;
				pi cur = solve2(i);
				ret *= cur.first + cur.second - 1;
				//cout << "y" << endl;
			}
		}
	}
	
	cout << ret << endl;

	return 0;
}
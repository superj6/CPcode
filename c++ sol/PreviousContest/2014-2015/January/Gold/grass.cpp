#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include <set>
#include <iterator>
using namespace std;

const int maxn = 100010;
int n, m, s = 0, st;
int rscc[maxn];
vector<int> graph[maxn], rgraph[maxn], scc[maxn], sgraph[maxn], rsgraph[maxn];
bool visited[maxn];
int stk = 0;
int stack[maxn];

void fdfs(int cur){
	visited[cur] = true;
	
	for(int i = 0; i < graph[cur].size(); i++){
		if(!visited[graph[cur][i]]) fdfs(graph[cur][i]);
	}
	
	stack[stk] = cur;
	stk++;
}

void rdfs(int cur){
	visited[cur] = true;
	
	for(int i = 0; i < rgraph[cur].size(); i++){
		if(!visited[rgraph[cur][i]]) rdfs(rgraph[cur][i]);
	}
	
	rscc[cur] = s;
	scc[s].push_back(cur);
}

int fmemo[maxn];
int fsdfs(int cur){
	if(cur == st) return 0;
	
	int& res = fmemo[cur];
	if(res != -1) return res;
	
	res = -2;
	
	for(int i = 0; i < sgraph[cur].size(); i++){
		res = max(res, fsdfs(sgraph[cur][i]));
	}
	
	if(res >= 0) res += (int)scc[cur].size();
	
	return res;
}

int rmemo[maxn];
int rsdfs(int cur){
	if(cur == st) return 0;
	
	int& res = rmemo[cur];
	if(res != -1) return res;
	
	res = -2;
	
	for(int i = 0; i < rsgraph[cur].size(); i++){
		res = max(res, rsdfs(rsgraph[cur][i]));
	}
	
	if(res >= 0) res += (int)scc[cur].size();
	
	return res;
}

int main(){
	ifstream fin ("grass.in");
	ofstream fout ("grass.out");
	
	fin >> n >> m;

	for(int i = 0; i < n; i++) visited[i] = false;

	for(int i = 0; i < m; i++){
		int a, b;
		fin >> a >> b;
		a--, b--;
		
		graph[a].push_back(b);
		rgraph[b].push_back(a);
	}
	
	for(int i = 0; i < n; i++){
		if(!visited[i]) fdfs(i);
	}
	
	for(int i = 0; i < n; i++) visited[i] = false;
	
	for(int i = n - 1; i >= 0; i--){
		int cur = stack[i];
		
		if(!visited[cur]){
			rdfs(cur);
			s++;
		}
	}
	
	st = rscc[0];
	
	for(int i = 0; i < s; i++){
		fmemo[i] = -1;
		rmemo[i] = -1;
		set<int> f, r;
		
		for(int j = 0; j < scc[i].size(); j++){
			int cur = scc[i][j];
			
			for(int k = 0; k < graph[cur].size(); k++){
				if(rscc[graph[cur][k]] != i) f.insert(rscc[graph[cur][k]]);
			}
			
			for(int k = 0; k < rgraph[cur].size(); k++){
				if(rscc[rgraph[cur][k]] != i) r.insert(rscc[rgraph[cur][k]]);
			}
		}
		
		if(f.size() > 0) for(set<int>::iterator itr = f.begin(); itr != f.end(); itr++){
			sgraph[i].push_back(*itr);
		}
		
		if(r.size() > 0) for(set<int>::iterator itr = r.begin(); itr != r.end(); itr++){
			rsgraph[i].push_back(*itr);
		}
	}
	
	int ans = scc[st].size();
	
	for(int i = 0; i < s; i++){
		int res1 = fsdfs(i), res2 = -2;
		
		if(res1 < 0) continue;
		
		for(int j = 0; j < sgraph[i].size(); j++){
			res2 = max(res2, rsdfs(sgraph[i][j]));
		}
		
		if(res2 < 0) continue;
		
		ans = max(ans, (int)scc[st].size() + res1 + res2);
		
	}
	
	fout << ans << endl;

	return 0;
}
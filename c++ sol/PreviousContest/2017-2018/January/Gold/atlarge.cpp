#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n, k;
vector<vector<int>> graph;
vector<int> leaves, distN, distL, par;
queue<int> q;

void recur(int curr){
	
	if(graph[curr].size() == 1 && curr != k){
		q.push(curr);
		distL[curr] = 0;
	}
	
	for(int i = 0; i < graph[curr].size(); i++){
		if(distN[graph[curr][i]] == -1){
			distN[graph[curr][i]] = distN[curr] + 1;
			par[graph[curr][i]] = curr;
			recur(graph[curr][i]);
		}
	}
	
}

int main(){
	ifstream fin ("atlarge.in");
	ofstream fout ("atlarge.out");
	
	fin >> n >> k;
	k--;
	graph.resize(n), distN.resize(n), distL.resize(n), par.resize(n);
	
	for(int i = 0; i < n; i++){
		distN[i] = -1;
		distL[i] = -1;
		par[i] = -1;
		
		if(i == n - 1) break;
		
		int a, b;
		fin >> a >> b;
		a--, b--;
		
		graph[a].push_back(b), graph[b].push_back(a);
	}
	
	par[k] = k;
	distN[k] = 0;
	recur(k);
	
	while(!q.empty()){
		int curr = q.front();
		q.pop();
		
		for(int i = 0; i < graph[curr].size(); i++){
			if(distL[graph[curr][i]] == -1){
				distL[graph[curr][i]] = distL[curr] + 1;
				q.push(graph[curr][i]);
			}
		}
	}
	
	int answer = 0;
	
	for(int i = 0; i < n; i++){
		if(distL[i] <= distN[i] && distL[par[i]] > distN[par[i]]) answer++;
	}
	
	fout << answer;

	return 0;
}
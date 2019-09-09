#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n, e;
int inf = 1000007;
vector<vector<int>> graph;
vector<int> quality, order;

int main(){
	ifstream fin ("buffet.in");
	ofstream fout ("buffet.out");

	
	fin >> n >> e;
	
	graph.resize(n);
	quality.resize(n);
	order.resize(n);
	
	for(int i = 0; i < n; i++){
		int q, d;
		fin >> quality[i] >> d;
		order[i] = i;
		
		for(int j = 0; j < d; j++){
			int p;
			fin >> p;
			graph[i].push_back(--p);
		}
	}
	
	struct{
		bool operator()(int a, int b){
			return quality[a] < quality[b];
		}
	} cmp;
	
	for(int i = 0; i < n; i++){
		sort(graph[i].begin(), graph[i].end(), cmp);
	}
	sort(order.begin(), order.end(), cmp);
	
	int maxv[n];
	int output = 0;
	for(int i = 0; i < n; i++) maxv[i] = 0;
	
	for(int i = 0; i < n; i++){
		int patch = order[i];
		int dist[n];
		for(int j = 0; j < n; j++) dist[j] = inf;
		
		dist[patch] = 0;
		queue<int> q;
		q.push(patch);
		
		while(!q.empty()){
			int curr = q.front();
			q.pop();
			
			for(int j = 0; j < graph[curr].size(); j++){
				int next = graph[curr][j];
				if(dist[next] == inf){
					dist[next] = dist[curr] + 1;
					q.push(next);
				}
			}
		}
		
		maxv[patch] = quality[patch];
		
		for(int j = 0; j < n; j++){
			int next = order[j];
			if(quality[next] >= quality[patch]) continue;
			
			if(dist[next] != inf) maxv[patch] = max(maxv[patch], quality[patch] + maxv[next] - dist[next] * e);
		}

		output = max(output, maxv[patch]);
	}
	
	fout << output << endl;

	return 0;
}
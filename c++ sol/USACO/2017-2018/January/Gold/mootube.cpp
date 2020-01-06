#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

vector<int> sz, par;

struct edge{
	int a, b, w;
	
	edge(int a, int b, int w){
		this->a = a;
		this->b = b;
		this->w = w;
	}
	
	friend bool operator<(edge x, edge y){
		return x.w < y.w;
	}
};

struct query{
	int k, v, i;
	
	query(int k, int v, int i){
		this->k = k;
		this->v = v;
		this->i = i;
	}
	
	friend bool operator<(query x, query y){
		return x.k < y.k;
	}
};

int find(int x){
	if(par[x] == x) return x;
	return find(par[x]);
}

void merge(int x, int y){
	int fx = find(x);
	int fy = find(y);
	par[fx] = fy;
	sz[fy] += sz[fx];
}

int main(){
	ifstream fin ("mootube.in");
	ofstream fout ("mootube.out");

	int n, q;
	fin >> n >> q;
	
	sz.resize(n), par.resize(n);
	
	priority_queue<edge> pqE;
	
	for(int i = 0; i < n; i++){
		sz[i] = 1;
		par[i] = i;
		
		if(i == n - 1) break;
		
		int a, b, w;
		fin >> a >> b >> w;
		pqE.push(edge(--a, --b, w));
	}
	
	priority_queue<query> pqQ;
	vector<int> answer;
	answer.resize(q);
	
	for(int i = 0; i < q; i++){
		int k, v;
		fin >> k >> v;
		pqQ.push(query(k, --v, i));
	}
	
	while(!pqQ.empty()){
		query q = pqQ.top();
		pqQ.pop();
		
		while(!pqE.empty()){
			edge e = pqE.top();
			
			if(e.w >= q.k){
				pqE.pop();
				
				merge(e.a, e.b);
			}else{
				break;
			}
			
		}
		
		answer[q.i] = sz[find(q.v)] - 1;
		
	}

	for(int i = 0; i < q; i++){
		fout << answer[i] << endl;
	}

	return 0;
}
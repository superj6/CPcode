/*
	For this problem, one way to overkill this is to use hld. First relable the nodes with hld traversal and hold the values
of the nodes in a segment tree, and for every change query just change the value in the segment tree. For the path query you need
to use hld by iterating up the path before the lca xoring the result with the xor of the path on a range. This works in O(nlog^2n),
however, this is largely overcomplicated and i'm not sure why I did this. Instead, just relable the nodes with a dfs traversle and
store a fenwick tree with the xor value of the path from the node to the root. To do a change query just use the fenwick tree to
xor every node in the subtree with the nodes current value and xor every node in the subtree with the new value. This will change
all the ranges in the subtree to now instead use the new value as the value of the xor path from node too root. Then to query for
a path, just find the lca and have the result as the fenwick tree value of the 2 enpoints xor'd with the lca. The complexity of this
is O(nlogn).
*/	

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 100000;
int n, q;
int it = 0;
int e[maxn], id[maxn], parent[maxn], heavy[maxn], head[maxn], tstart[maxn];
vector<int> graph[maxn];
vector<pair<int, int>> tour;

struct segTree{
	int l, r;
	segTree *left, *right;
	int xorv = 0;
	pair<int, int> vertex = make_pair(10000000, 10000000);
	
	segTree(int a, int b){
		l = a;
		r = b;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	void addv(int index, pair<int, int> val){
		if(l > index || r < index) return;
		if(l == r){
			vertex = val;
			return;
		}
		
		left->addv(index, val);
		right->addv(index, val);
		
		vertex = min(left->vertex, right->vertex);
	}
	
	pair<int, int> getvertex(int a, int b){
		if(l > b || r < a) return make_pair(10000000, 10000000);
		if(l >= a && r <= b) return vertex;
		
		return min(left->getvertex(a, b), right->getvertex(a, b));
	}
	
	void add(int index, int val){
		if(l > index || r < index) return;
		if(l == r){
			xorv = val;
			return;
		}
		
		left->add(index, val);
		right->add(index, val);
		
		xorv = left->xorv ^ right->xorv;
	}
	
	int getxor(int a, int b){
		if(l > b || r < a) return 0;
		if(l >= a && r <= b) return xorv;
		
		return left->getxor(a, b) ^ right->getxor(a, b);
	}
};

int dfs(int cur){
	int size = 1;
	int maxv = 0;
	
	for(int i = 0; i < graph[cur].size(); i++){
		int next = graph[cur][i];
		if(parent[cur] == next) continue;
		
		parent[next] = cur;
		int nsize = dfs(next);
		size += nsize;
		
		if(nsize > maxv){
			maxv = nsize;
			heavy[cur] = next;
		}
	}
	
	return size;
	
}

void dec(int cur, int h){
	head[cur] = h;
	id[cur] = it;
	it++;
	
	if(heavy[cur] != -1){
		dec(heavy[cur], h);
	}
	
	for(int i = 0; i < graph[cur].size(); i++){
		int next = graph[cur][i];
		if(parent[cur] == next || heavy[cur] == next) continue;
		
		dec(next, next);
	}
}

void prelca(int cur, int height){
	tstart[cur] = tour.size();
	tour.push_back(make_pair(height, cur));
	
	for(int i = 0; i < graph[cur].size(); i++){
		int next = graph[cur][i];
		if(parent[cur] == next) continue;
		
		prelca(next, height + 1);
		
		tour.push_back(make_pair(height, cur));
	}
}

int lca(int a, int b, segTree *tree){
	int st = min(tstart[a], tstart[b]), en = max(tstart[a], tstart[b]);
	return (tree->getvertex(st, en)).second;
}

int main(){
	freopen("cowland.in", "r", stdin);
	freopen("cowland.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	
	for(int i = 0; i < n; i++){
		cin >> e[i];
		parent[i] = -1;
		heavy[i] = -1;
		tstart[i] = -1;
	} 
	
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	
	dfs(0);
	dec(0, 0);
	prelca(0, 0);
	
	segTree *tree = new segTree(0, n - 1);
	segTree *lcatree = new segTree(0, tour.size() - 1);
	
	for(int i = 0; i < tour.size(); i++) lcatree->addv(i, tour[i]);
	for(int i = 0; i < n; i++) tree->add(id[i], e[i]);
	
	for(int q0 = 0; q0 < q; q0++){
		int t;
		cin >> t;
		
		if(t == 1){
			int i, v;
			cin >> i >> v;
			i--;
			
			tree->add(id[i], v);
		}else{
			int i, j;
			cin >> i >> j;
			i--, j--;
			
			int l = lca(i, j, lcatree);
			
			int res = tree->getxor(id[l], id[l]);
			
			while (i != l){
				if(head[i] == head[l]){
					res ^= tree->getxor(id[l] + 1, id[i]);
					i = l;
				}else{
					res ^= tree->getxor(id[head[i]], id[i]);
					i = parent[head[i]];
				}
			}
			
			while(j != l){
				if(head[j] == head[l]){
					res ^= tree->getxor(id[l] + 1, id[j]);
					j = l;
				}else{
					res ^= tree->getxor(id[head[j]], id[j]);
					j = parent[head[j]];
				}
			}
			
			cout << res << endl;
		}
	}

	return 0;
}

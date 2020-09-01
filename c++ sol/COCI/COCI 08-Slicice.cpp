/*
  First assume all edges subtract one from both nodes. This may make some nodes have negative value, so we have to change some of the edges orientations so that they can transfer
a card from a positive node to a negative node, which is equivalent to directing some of the edges in paths from negative to positive nodes and making the head of the directed
edges get all the cards. Creating paths for each negative card value can be turned into a multi-source/sink maxflow problem, where you connect all negative nodes to the source
with edge absolute value of their weight, and all positive nodes to sink with edges the value of their weight. Now just run maxflow, I use push-relabel, use the residual graph to
change the orientation of the edges accordingly, and greedily assign new edges to the rest of the nodes.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 102, mxm = 1000;
int n, m;
int a[mxn], b[mxn], h[mxn];
int u[mxm], v[mxm], d[mxm];
int g[mxn][mxn], f[mxn][mxn];
vector<int> s;

void push(int u, int v){
	int x = min(b[u], g[u][v] - f[u][v]);
	f[u][v] += x, f[v][u] -= x;
	b[u] -= x, b[v] += x;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < m; i++){
		cin >> u[i] >> v[i];
		a[--u[i]]--, a[--v[i]]--;
		g[u[i]][v[i]]++, g[v[i]][u[i]]++;
	}
	
	for(int i = 0; i < n; i++){
		if(a[i] < 0) g[n][i] = -a[i];
		if(a[i] > 0) g[i][n + 1] = a[i];
	}
	
	//flow
	h[n] = n + 2, b[n] = 0x3f3f3f3f;
	for(int i = 0; i < n; i++) push(n, i);
	
	do{
		s.clear();
		for(int i = 0; i < n; i++) if(b[i]){
			if(s.empty() || h[i] > h[s[0]]) s.assign(1, i);
			else if(h[i] == h[s[0]]) s.push_back(i);
		}

		for(int i : s){
			bool t = 0;
			for(int j = 0; j < n + 2; j++){
				if(g[i][j] > f[i][j] && h[i] == h[j] + 1){
					push(i, j);
					t = 1;
				}
			}
			
			if(!t){
				h[i] = 2 * n + 1;
				for(int j = 0; j < n + 2; j++){
					if(g[i][j] > f[i][j]) h[i] = min(h[i], h[j]);
				}
				h[i]++;
				break;
			}
		}
	} while(!s.empty());
	//end flow
	
	for(int i = 0; i < m; i++){
		if(f[u[i]][v[i]] > 0) d[i] = -1, f[u[i]][v[i]]--, a[u[i]]++, a[v[i]]--;
		if(f[v[i]][u[i]] > 0) d[i] = 1, f[v[i]][u[i]]--, a[u[i]]--, a[v[i]]++;
	}
	
	for(int i = 0, j = -1; i < n; i++) if(a[i] & 1){
		if(!~j) j = i;
		else u[m] = i, v[m] = j, a[i]--, a[j]--, j = -1, m++;
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 0; 2 * j < a[i]; j++, m++){
		u[m] = i, v[m] = !i, d[m] = 1;
	}
	
	cout << m << endl;
	for(int i = 0; i < m; i++){
		cout << u[i] + 1 << " " << v[i] + 1 << " " << d[i] + 1 << endl;
	} 

	return 0;
}

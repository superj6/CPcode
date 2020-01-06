#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define pi pair<double, double>
#define pii pair<int, pi>
#define pd pair<int, double>

const int inf = 1000000007;
const int maxn = 1000;
int n, m;
double x[maxn], y[maxn];
vector<pii> graph[maxn];

void dijkstra(){
	set<pd> pq;
	x[0] = 0, y[0] = inf;
	for(int i = 1; i < n; i++){
		x[i] = inf, y[i] = 0;
	}
	pq.insert({inf, 0});
	
	while(!pq.empty()){
		int c = (*pq.begin()).second;
		double d = (*pq.begin()).first;
		pq.erase(pq.begin());
		
		for(pii i : graph[c]){
			double nd = min(y[c], i.second.second) / (x[c] + i.second.first);
			if(nd > y[i.first] / x[i.first]){
				pq.erase({y[i.first] / x[i.first], i.first});
				pq.insert({nd, i.first});
				y[i.first] = min(y[c], i.second.second);
				x[i.first] = x[c] + i.second.first;
			}
		}
	}
}

int main(){
	freopen("pump.in", "r", stdin);
	freopen("pump.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int a, b, c, f;
		cin >> a >> b >> c >> f;
		a--, b--;
		graph[a].push_back({b, {c, f}});
		graph[b].push_back({a, {c, f}});
	}
	
	dijkstra();
	
	cout << ((int)((y[n - 1] / x[n - 1]) * 1000000)) << endl;

	return 0;
}
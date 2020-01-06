/*
	For this problem, because n is small, we can first generate every edge. Now, to split the the cows into k groups with
minimum distance between to, you should be using the k smallest edges to connect groups that are not already connected, as otherwise
those edges could be used as the minimum between to groups. This should immediatly remind you of spanning tree, as the spanning
tree uses minimum edges to connect all nodes, and the idea of using the smallest edges to connect unconnected groups sounds just
like kruskals. However, this problem is dumb and enforces you to use prims to calculate the spanning tree and sort the edges.
After doing so you can just pick the n - k + 1 smallest edge from the spanning tree, as this is the next smallest edge not already
used to connect two of the k groups. The time complexity is O(n^2) as you have to iterate over every edge in prim's.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define endl '\n'

const long long a = 2019201913, b = 2019201949, mod = 2019201997;

long long length(int x, int y){
	if(x > y){
		x = x + y;
		y = x - y;
		x = x - y;
	}
	
	return (a * (x + 1) + b * (y + 1)) % mod;
}

int main(){
	freopen("walk.in", "r", stdin);
	freopen("walk.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	long long dist[n];
	bool visited[n];
	
	for(int i = 0; i < n; i++){
		dist[i] = mod;
		visited[i] = 0;
	} 
	
	int best = 0;
	dist[0] = 0;
	
	while(best != -1){
		visited[best] = true;
		int nbest = -1;
		
		for(int i = 0; i < n; i++){
			if(visited[i]) continue;
			
			dist[i] = min(dist[i], length(best, i));
			
			if(nbest == -1 || dist[i] < dist[nbest]) nbest = i;
		}
		
		best = nbest;
	}
	
	sort(dist, dist + n);
	
	cout << dist[n - k + 1] << endl;

	return 0;
}

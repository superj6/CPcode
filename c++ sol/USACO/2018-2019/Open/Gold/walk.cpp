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
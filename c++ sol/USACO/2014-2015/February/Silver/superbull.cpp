#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n;
long inf = 1000000007;
long cows[2000];
long graph[2000][2000];

long mintree(){
	bool intree[n];
	long dist[n];
	long total = 0;
	
	for(int i = 0; i < n; i++){
		dist[i] = inf;
		intree[i] = false;
	}
	
	dist[0] = 0;
	
	while(true){
		int minval = inf, minindex = -1;
		
		for(int i = 0; i < n; i++){
			if(dist[i] < minval && !intree[i]){
				minindex = i;
				minval = dist[i];
			}
		}
		
		if(minindex == -1) break;
		
		total += minval;
		intree[minindex] = true;
		
		for(int i = 0; i < n; i++){
			dist[i] = min(dist[i], graph[minindex][i]);
		}
	}
	
	return -total;
}

int main(){
	ifstream fin ("superbull.in");
	ofstream fout ("superbull.out");

	fin >> n;
	
	for(int i = 0; i < n; i++){
		long curr;
		fin >> cows[i];
		
		for(int j = 0; j < i; j++){
			graph[i][j] = -(cows[i] ^ cows[j]);
			graph[j][i] = -(cows[i] ^ cows[j]);
		}
	}
	
	long dist = mintree();
	
	fout << dist;	

	return 0;
}
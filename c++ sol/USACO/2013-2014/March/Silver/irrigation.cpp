#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;

long inf = 2147483600;
int n;
long c;
pair<long, long> points[2000];

long distl(int a, int b){
	long outnum = pow(points[a].first - points[b].first, 2) + pow(points[a].second - points[b].second, 2);
	if (outnum < c) return inf;
	return outnum;
}

long minspan(){
	long total = 0;
	long dist[2000];
	bool visited[2000];
	
	
	for(int i = 0; i < n; i++){
		dist[i] = inf;
		visited[i] = false;
	}
	
	dist[0] = 0;
	
	for(int i = 0; i < n; i++){
		int minindex = -1;
		long mindist = inf;
		
		for(int i = 0; i < n; i++){
			if(!visited[i] && dist[i] < mindist){
				mindist = dist[i];
				minindex = i;
			}
		}
		
		if(minindex == -1){
			total = -1;
			break;
		}
		visited[minindex] = true;
		total += dist[minindex];
		
		for(int i = 0; i < n; i++){
			dist[i] = min(dist[i], distl(minindex, i));
		}
		
	}
	
	return total;
}

int main(){
	ifstream fin ("irrigation.in");
	ofstream fout ("irrigation.out");
	
	fin >> n >> c;
	
	for(int i = 0; i < n; i++){
		fin >> points[i].first >> points[i].second;
	}
	
	fout << minspan() << endl;

	return 0;
}
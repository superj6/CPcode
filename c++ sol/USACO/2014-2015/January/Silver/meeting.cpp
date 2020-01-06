#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <iterator>
using namespace std;

int main(){
	ifstream fin ("meeting.in");
	ofstream fout ("meeting.out");

	vector<vector<int>> graphb, graphe;
	vector<unordered_set<int>> timeb, timee;
	
	int n, m;
	fin >> n >> m;
	
	timeb.resize(n), timee.resize(n), graphb.resize(n), graphe.resize(n);
	
	for(int i = 0; i < n; i++){
		graphb[i].resize(n), graphe[i].resize(n);
		
		for(int j = 0; j < n; j++) graphb[i][j] = -1, graphe[i][j] = -1;
	}
	
	for(int i = 0; i < m; i++){
		int a, b, c, d;
		fin >> a >> b >> c >> d;
		a--, b--;
		
		graphb[a][b] = c, graphe[a][b] = d;
	}
	
	timeb[0].insert(0), timee[0].insert(0);
	
	for(int i = 0; i < n; i++){
		
		for(int j = i + 1; j < n; j++){
			if(graphb[i][j] == -1) continue;
			unordered_set<int>::iterator itr;
			
			for(itr = timeb[i].begin(); itr != timeb[i].end(); ++itr){
				timeb[j].insert(*itr + graphb[i][j]);
			}
			
			for(itr = timee[i].begin(); itr != timee[i].end(); ++itr){
				timee[j].insert(*itr + graphe[i][j]);
			}
		}
	}
	
	for(int i = 1; i < 10001; i++){
		if(timeb[n-1].find(i) != timeb[n-1].end() && timee[n-1].find(i) != timee[n-1].end()){
			fout << i << endl;
			return 0;
		}
	}
	
	fout << "IMPOSSIBLE" << endl;

	return 0;
}
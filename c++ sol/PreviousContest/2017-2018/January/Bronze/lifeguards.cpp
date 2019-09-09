#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("lifeguards.in");
	ofstream fout ("lifeguards.out");
	
	int n, highest = 0;
	fin >> n;
	int start[n], end[n];
	
	for(int i = 0; i < n; i++){
		fin >> start[i] >> end[i];
	}
	
	for(int i = 0; i < n; i++){
		int curr = 0;
		bool time[1001];
		
		for(int j = 0; j < 1001; j++) time[j] = false;
		
		for(int j = 0; j < n; j++){
			if(j == i) continue;
			
			for(int a = start[j]; a < end[j]; a++){
				if(!time[a]){
					time[a] = true;
					curr++;
				}
			}
		}
		
		highest = max(highest, curr);
	}
	
	fout << highest;
	
	return 0;
}
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	ifstream fin ("cowqueue.in");
	ofstream fout ("cowqueue.out");
	
	int n;
	fin >> n;
	vector<pair<int, int> > cow;
	cow.resize(n);
	
	for(int i = 0; i < n; i++){
		fin >> cow[i].first >> cow[i].second;
	}
	
	sort(cow.begin(), cow.end());
	
	int time = 0;
	
	for(int i = 0; i < n; i++){
		int a = cow[i].first, b = cow[i].second;
		
		if(a > time){
			time = a + b;
		}else{
			time += b;
		}
	}
	
	fout << time;
	
	return 0;
}
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
int t[10000], total[10000];
vector<int> before[10000];

int ttime(int cur){
	if(total[cur] != -1) return total[cur];
	
	int maxt = 0;
	
	for(int i = 0; i < before[cur].size(); i++){
		maxt = max(maxt, ttime(before[cur][i]));
	}
	
	total[cur] = t[cur] + maxt;
	
	return total[cur];
}

int main(){
	ifstream fin ("msched.in");
	ofstream fout ("msched.out");
	
	fin >> n >> m;

	for(int i = 0; i < n; i++){
		fin >> t[i];
		total[i] = -1;
	}
	
	for(int i = 0; i < m; i++){
		int a, b;
		fin >> a >> b;
		a--, b--;
		before[b].push_back(a);
	}
	
	int maxv = 0;
	
	for(int i = 0; i < n; i++){
		maxv = max(maxv, ttime(i));
	}
	
	fout << maxv << endl;

	return 0;
}

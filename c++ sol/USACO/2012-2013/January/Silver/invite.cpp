#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
using namespace std;

int main(){
	ifstream fin ("invite.in");
	ofstream fout ("invite.out");
	
	int n, g;
	fin >> n >> g;
	
	set<int> groups[g];
	vector<int> cows[n];
	bool used[n];
	
	for(int i = 0; i < g; i++){
		int s;
		fin >> s;
		
		for(int j = 0; j < s; j++){
			int c;
			fin >> c;
			c--;
			
			used[c] = false;
			
			groups[i].insert(c);
			cows[c].push_back(i);
		}
	}
	
	queue<int> q;
	q.push(0);
	int amt = 0;
	
	while(!q.empty()){
		int cur = q.front();
		q.pop();
		
		if(used[cur]) continue;
		used[cur] = true;
		amt++;
		
		for(int i = 0; i < cows[cur].size(); i++){
			groups[cows[cur][i]].erase(cur);
			if(groups[cows[cur][i]].size() == 1) q.push(*groups[cows[cur][i]].begin());
		}
	}
	
	fout << amt << endl;

	return 0;
}
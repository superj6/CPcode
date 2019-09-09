#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
	ifstream fin ("shuffle.in");
	ofstream fout ("shuffle.out");
	
	int n;
	fin >> n;
	int to[n], from[n];
	for(int i = 0; i < n; i++) from[i] = 0;
	
	for(int i = 0; i < n; i++){
		fin >> to[i];
		to[i]--;
		
		from[to[i]]++; 
	}
	
	queue<int> q;
	int amount = n;
	
	for(int i = 0; i < n; i++){
		if(from[i] == 0){
			q.push(i);
			amount--;
		}
	}
	
	while(!q.empty()){
		int curr = q.front();
		q.pop();
		
		from[to[curr]]--;
		
		if(from[to[curr]] == 0){
			q.push(to[curr]);
			amount--;
		}
	}
	
	fout << amount;
	
	return 0;
}
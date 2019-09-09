#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
vector<pair<int, int>> answer;

bool ingraph(int x, int y){
	if(x < 0 || y < 0 || x >= n || y >= m) return false;
	return true;
} 

int main(){
	ifstream fin ("crosswords.in");
	ofstream fout ("crosswords.out");

	fin >> n >> m;
	char graph[n][m];
	
	for(int i = 0; i < n; i++){
		fin >> graph[i];
	}
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			
			if(graph[i][j] == '.'){
					
				if((!ingraph(i - 1, j) || (ingraph(i - 1, j) && graph[i - 1][j] == '#')) && ingraph(i + 2, j) && graph[i + 1][j] == '.' && graph[i + 2][j] == '.'){
					answer.push_back(make_pair(i + 1, j + 1));
					continue;
				}
				
				if((!ingraph(i, j - 1) || (ingraph(i, j - 1) && graph[i][j - 1] == '#')) && ingraph(i, j + 2) && graph[i][j + 1] == '.' && graph[i][j + 2] == '.'){
					answer.push_back(make_pair(i + 1, j + 1));
					continue;
				}
			}
			
		}
	}
	
	fout << answer.size() << endl;
	
	for(int i = 0; i < answer.size(); i++){
		fout << answer[i].first << " " << answer[i].second << endl;
	}

	return 0;
}
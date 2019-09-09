#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("speeding.in");
	ofstream fout ("speeding.out");
	int n, m;
	fin >> n >> m;
	int road[100];
	
	int index = 0;
	
	for(int i = 0; i < n; i++){
		int a, b;
		fin >> a >> b;
		
		for(int j = 0; j < a; j++){
			road[index] = b;
			index++;
		}
	}
	
	int output = 0;
	index = 0;
	
	for(int i = 0; i < m; i++){
		int a, b;
		fin >> a >> b;
		
		for(int j = 0; j < a; j++){
			output = max(b - road[index], output);
			index++;
		}
	}
	
	fout << output;
	
	return 0;
}
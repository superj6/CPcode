#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("shuffle.in");
	ofstream fout ("shuffle.out");
	
	int n;
	fin >> n;
	int order[n], id[n], output[n];
	
	for(int i = 0; i < n; i++){
		int a;
		fin >> a;
		order[a - 1] = i;
	}
	
	for(int i = 0; i < n; i++){
		fin >> id[i];
	}
	
	for(int j = 0; j < 3; j++){
		for(int i = 0; i < n; i++){
			output[order[i]] = id[i];
		}
	
		for(int i = 0; i < n; i++){
			id[i] = output[i];
		}
	}
		
	for(int i = 0; i < n; i++){
		fout << output[i] << endl;
	}
	return 0;
}
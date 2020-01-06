#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("cbarn.in");
	ofstream fout ("cbarn.out");
	
	int n, maxv = 2147483647;
	fin >> n;
	int array[n];
	
	for(int i = 0; i < n; i++){
		fin >> array[i];
	}
	
	for(int i = 0; i < n; i++){
		int val = 0;
		
		for(int j = 1; j < n; j++){
			val += j * array[(i + j) % n];
		}
		
		maxv = min(maxv, val);
	}
	
	fout << maxv;
	return 0;
}
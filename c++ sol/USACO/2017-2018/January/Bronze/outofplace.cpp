#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("outofplace.in");
	ofstream fout ("outofplace.out");
	
	int n;
	fin >> n;
	int array[n], sorted[n];
	
	for(int i = 0; i < n; i++){
		fin >> array[i];
		sorted[i] = array[i];
	}
	
	sort(sorted, sorted+n);
	
	int answer = -1;
	
	for(int i = 0; i < n; i++){
		if(sorted[i] != array[i]) answer++;
	}
	
	fout << answer;
	
	return 0;
}
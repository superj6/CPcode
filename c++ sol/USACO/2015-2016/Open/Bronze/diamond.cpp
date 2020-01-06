#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("diamond.in");
	ofstream fout ("diamond.out");
	
	int n, k;
	fin >> n >> k;
	int array[n];
	
	for(int i = 0; i < n; i++){
		fin >> array[i];
	}
	
	sort(array, array+n);
	
	int maxv = 1;
	
	for(int i = 0; i < n; i++){
		int curr = 1;
		while(curr < n - i){
			if(array[curr + i] - array[i] > k)break;
			curr++;
		}

		maxv = max(maxv, curr);
	}
	
	fout << maxv;
	
	return 0;
}
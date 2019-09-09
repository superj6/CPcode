#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("homework.in");
	ofstream fout ("homework.out");
	
	int n;
	fin >> n;
	float array[n];
	float answer[n];
	for(int i = 0; i < n; i++){
		fin >> array[i];
		answer[i] = 0;
	} 
	answer[0] = -1;
	answer[n - 1] = -1;
	
	float maxv = 0, sum = array[n - 1], minv = array[n - 1]; 
	
	
	for(int i = n - 2; i > 0; i--){
		minv = min(array[i], minv);
		sum += array[i];
		
		answer[i] = (sum - minv) / (n - i - 1);
		maxv = max(answer[i], maxv);
	}
	
	for(int i = 0; i < n; i++){
		if(answer[i] == maxv) fout << i << endl;
	}
	
	return 0;
}
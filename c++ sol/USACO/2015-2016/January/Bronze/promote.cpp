#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("promote.in");
	ofstream fout ("promote.out");
	
	int before[4], after[4], diff[3];
	
	for(int i = 0; i < 4; i++){
		fin >> before[i] >> after[i];
	}
	
	diff[2] = after[3] - before[3];
	
	for(int i = 1; i >= 0; i--){
		diff[i] =  after[i + 1] - before[i + 1] + diff[i + 1];
	}
	
	for(int i = 0; i < 3; i++){
		fout << diff[i] << endl;
	}
	
	
	return 0;
}
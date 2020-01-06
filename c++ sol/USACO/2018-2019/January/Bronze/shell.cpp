#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("shell.in");
	ofstream fout ("shell.out");
	
	int n;
	int amount[3], current[3];
	fin >> n;
	
	for(int i = 0; i < 3; i++){
		current[i] = i;
		amount[i] = 0;
	}
	
	for(int i = 0; i < n; i++){
		int a, b, c;
		fin >> a >> b >> c;
		a--;
		b--;
		c--;
		
		int temp = current[b];
		current[b] = current[a];
		current[a] = temp;
		
		amount[current[c]]++;
	}
	
	fout << max(amount[0], max(amount[1], amount[2]));
	
	return 0;
}
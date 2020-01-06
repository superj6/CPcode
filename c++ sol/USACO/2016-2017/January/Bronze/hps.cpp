#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("hps.in");
	ofstream fout ("hps.out");
	
	int n;
	fin >> n;
	int amount = 0;
	int ties = 0;
	
	for(int i = 0; i < n; i++){
		int a, b, c;
		fin >> a >> b;
		a--;
		b--;
		c = a * 3 + b;
		
		if(c == 1 || c == 5 || c == 6) amount++;
		if(c == 0 || c == 4 || c == 8) ties++;
	}
	
	fout << max(amount, n - amount - ties);
	
	return 0;
}
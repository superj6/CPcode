#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
	ofstream fout ("paint.out");
        ifstream fin ("paint.in");

	int a, b, c, d;
	
	fin >> a >> b;
	fin >> c >> d;
	
	if( d > a && b > c){
		fout << (max(b, d) - min(a, c)) << endl;
	}else{
		fout << (b + d - c - a) << endl;
	}
	
	return 0;
}
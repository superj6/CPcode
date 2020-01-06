#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

int main(){
	ifstream fin ("clumsy.in");
	ofstream fout ("clumsy.out");
	
	string par;
	fin >> par;
	int depth = 0, amt = 0;
	
	for(int i = 0; i < par.size(); i++){
		depth += par[i] == '(' ? 1 : -1;
		
		if(depth < 0){
			depth += 2;
			amt++;
		}
	}
	
	amt += depth / 2;
	
	fout << amt << endl;

	return 0;
}
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {

	ifstream fin ("pails.in");
	ofstream fout ("pails.out");
	
	int x, y, m;
	fin >> x >> y >> m;
	bool array[m + 1];
	int max = 0;
	
	for(int i = 0; i <= m; i++) array[i] = false;
	array[0] = true;
	
	
	for(int i = 0; i <= m; i++){
		if(i >= x){
			if(array[i - x] == true){
				array[i] = true;
				max = i;
			}
		}
		
		if(i >= y){
			if(array[i - y] == true){
				array[i] = true;
				max = i;
			}
		}
	}
	
	fout << max;
	
	return 0;

}
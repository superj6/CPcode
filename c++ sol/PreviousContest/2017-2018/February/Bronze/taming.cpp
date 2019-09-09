
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("taming.in");
	ofstream fout ("taming.out");
	
	int n;
	fin >> n;
	int array[n];
	
	for(int i = 0; i < n; i++){
		fin >> array[i];
	}
	
	if(array[0] == -1){
		array[0] = 0;
	}else if(array[0] != 0){
		fout << -1;
		return 0;
	}
	
	for(int i = 1; i < n; i++){
		if(array[i] != -1){
			
			for(int j = array[i] - 1; j >= 0; j--){
				if(array[i - array[i] + j] != -1 && array[i - array[i] + j] != j){
					fout << -1;
					return 0;
				}
				
				array[i - array[i] + j] = j;
			}
			
		}
	}
	
	int min = 0, max = 0;
	
	for(int i = 0; i < n; i++){
		if(array[i] == -1) max++;
		if(array[i] == 0){
			min++;
			max++;
		}
	}
	
	fout << min << " " << max;
	
	return 0;
}
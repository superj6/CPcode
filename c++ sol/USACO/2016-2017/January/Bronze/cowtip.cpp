#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("cowtip.in");
	ofstream fout ("cowtip.out");
	
	int n, amount = 0;
	fin >> n;
	int array[n][n];
	
	for(int i = 0; i < n; i++){
		char num[n];
		fin >> num;
		
		for(int j = 0; j < n; j++){
			array[i][j] = (int)(num[j] - '0');
		}
	}
	
	while(true){
		int farx = -1, fary = -1;
		
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				
				if(array[i][j] == 1){
					
					if(farx == -1){
						farx = i;
						fary = j;
					}else if(i * i + j * j > farx * farx + fary * fary){
						farx = i;
						fary = j;
					}
					
				}
				
			}
		}
		
		if(farx == -1) break;
		
		amount++;
		
		for(int i = 0; i <= farx; i++){
			for(int j = 0; j <= fary; j++){
				if(array[i][j] == 1){
					array[i][j] = 0;
				}else{
					array[i][j] = 1;
				}
			}
		}
	}
	
	fout << amount;
	
	return 0;
}
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("cowsignal.in");
	ofstream fout ("cowsignal.out");
	
	int m, n, k;
	fin >> m >> n >> k;
	char array[m][n], scaled[m*k][n*k];
	
	for(int i = 0; i < m; i++){
		fin >> array[i];
	}
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			char curr = array[i][j];
			
			for(int a = i * k; a < k * (i + 1); a++){
				for(int b = j * k; b < k * (j + 1); b++){
					scaled[a][b] = curr;
				}
			}
		}
	}
	
	for(int i = 0; i < m * k; i++){
		for(int j = 0; j < n * k; j++){
			fout << scaled[i][j];
		}	
		fout << endl;
	}
	
	
	return 0;
}
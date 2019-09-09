#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int dx[] = {1, 1, -1, -1};
int dy[] = {1, -1, -1, 1};

int main() {
	ifstream fin ("balancing.in");
	ofstream fout ("balancing.out");
	
	int n, bruh;
	fin >> n >> bruh;
	
	int x[n], y[n];
	int out = n;
	
	for(int i = 0; i < n; i++){
		fin >> x[i] >> y[i];
	}
	
	for(int i = 0; i < n; i++){
		for(int i2 = 0; i2 < n; i2++){
		for(int j = 0; j < 4; j++){
			int a = x[i] + dx[j];
			int b = y[i2] + dy[j];
			int quad1 = 0, quad2 = 0, quad3 = 0, quad4 = 0;
			
			for(int k = 0; k < n; k++){
				if(x[k] > a && y[k] > b){
					quad1 += 1;;
				}
				if(x[k] < a && y[k] > b){
					quad2 += 1;
				}
				if(x[k] < a && y[k] < b){
					quad3 += 1;
				}
				if(x[k] > a && y[k] < b){
					quad4 += 1;
				}
				
			}
			
			int maxregion = max(quad1, max(quad2, max(quad3, quad4)));
			out = min(maxregion, out);
		}
		}
	}
	
	fout << out;
	
	return 0;
}
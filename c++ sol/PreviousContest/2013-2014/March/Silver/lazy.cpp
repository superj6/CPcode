#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, k, r;
int grid[799][799], amount[799][799];

int square(int x, int y){
	int total = amount[min(x + k, r - 1)][min(y + k, r - 1)];
	if(x - k - 1 >= 0) total -= amount[x - k - 1][min(y + k, r - 1)];
	if(y - k - 1 >= 0) total -= amount[min(x + k, r - 1)][y - k - 1];
	if(x - k - 1 >= 0 && y - k - 1 >= 0) total += amount[x - k - 1][y - k - 1];
	
	return total;
}

int main(){
	ifstream fin ("lazy.in");
	ofstream fout ("lazy.out");
	
	fin >> n >> k;
	r = 2 * n - 1;
	
	for(int i = 0; i < r; i++) for(int j = 0; j < r; j++) grid[i][j] = 0;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			fin >> grid[i - j + n - 1][i + j];
		}
	}
	
	for(int i = 0; i < r; i++){
		for(int j = 0; j < r; j++){
			if(i == 0 && j == 0) amount[i][j] = grid[i][j];
			else if(i == 0) amount[i][j] = amount[i][j - 1] + grid[i][j];
			else if(j == 0) amount[i][j] = amount[i - 1][j] + grid[i][j];
			else amount[i][j] = amount[i][j - 1] + amount[i - 1][j] - amount[i - 1][j - 1] + grid[i][j];

		}
	}
	
	int maxv = 0;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			maxv = max(maxv, square(i - j + n - 1, i + j));
		}
	}
	
	fout << maxv << endl;

	return 0;
}
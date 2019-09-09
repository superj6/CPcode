#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

int xdir[] = {0, 1, 0, -1};
int ydir[] = {1, 0, -1, 0};
map<char, int> dir;

int main(){
	dir['N'] = 0;
	dir['E'] = 1;
	dir['S'] = 2;
	dir['W'] = 3;

	ifstream fin ("mowing.in");
	ofstream fout ("mowing.out");
	
	int n;
	fin >> n;
	int x = 1000, y = 1000, out = 1000000, time = 0;
	int lastvisit[2001][2001];
	int highestval[2001][2001];
	
	for(int i = 0; i < 2001; i++){
		for(int j = 0; j < 2001; j++){
			lastvisit[i][j] = -1000000;
			highestval[i][j] = 1000000;
		}
	}
	
	lastvisit[x][y] = time;
	
	
	for(int i = 0; i < n; i++){
		char a;
		int b;
		fin >> a >> b;
		int val = dir.find(a)->second;
		
		for(int j = 0; j < b; j++){
			time++;
			x += xdir[val];
			y += ydir[val];
			
			
			cout << time << " " << lastvisit[x][y] << endl;
			highestval[x][y] = min(highestval[x][y], time - lastvisit[x][y]);
			lastvisit[x][y] = time;
			
			out = min(out, highestval[x][y]);
		}
	}
	
	if(out == 1000000) out = -1;
	
	fout << out;
	
	return 0;
}
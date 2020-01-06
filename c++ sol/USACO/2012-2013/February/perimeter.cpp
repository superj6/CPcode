#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int main(){
	ifstream fin ("perimeter.in");
	ofstream fout ("perimeter.out");
	
	int n; 
	fin >> n;
	
	map<int, map<int, int>> mat;
	int bx = 100000000, by = 100000000;
	
	for(int i = 0; i < n; i++){
		int x, y;
		fin >> x >> y;
		mat[x][y] = 1;
		
		
		if(x < bx || (x == bx && y < by)){
			bx = x;
			by = y;
		}
	}
	int x = bx, y = by, d = 0, p = 0;
	
	do{
		x += dx[d], y += dy[d];
		p++;
		
		for(d = (d + 3) % 4; ; d = (d + 1) % 4){
			if ((d==0 && mat[x][y]) || (d==1 && mat[x-1][y]) ||
			(d==2 && mat[x-1][y-1]) || (d==3 && mat[x][y-1])) 
				break;
		}
	}while(x != bx|| y != by);

	fout << p << endl;

	return 0;
}
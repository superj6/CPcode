#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("reduce.in");
	ofstream fout ("reduce.out");
	
	int n;
	fin >> n;
	
	int x[n], y[n];
	
	int maxx = 0, maxy = 0, minx = 40001, miny = 40001;
	int max2x = 0, max2y = 0, min2x = 40001, min2y = 40001;
	
	for(int i = 0; i < n; i++){
		fin >> x[i] >> y[i];
		
		if(x[i] > maxx){
			max2x = maxx;
			maxx = x[i];
		}else if(x[i] > max2x){
			max2x = x[i];
		} 
		
		if(x[i] < minx){
			min2x = minx;
			minx = x[i];
		}else if(x[i] < min2x){
			min2x = x[i];
		} 
		
		if(y[i] > maxy){
			max2y = maxy;
			maxy = y[i];
		}else if(y[i] > max2y){
			max2y = y[i];
		} 
		
		if(y[i] < miny){
			min2y = miny;
			miny = y[i];
		}else if(y[i] < min2y){
			min2y = y[i];
		}
	}
	
	int area = 2147483647;
	
	for(int i = 0; i < n; i++){
		int maxcurx = maxx, maxcury = maxy, mincurx = minx, mincury = miny;
		
		if(x[i] == maxx) maxcurx = max2x;
		if(x[i] == minx) mincurx = min2x;
		if(y[i] == maxy) maxcury = max2y;
		if(y[i] == miny) mincury = min2y;
		
		area = min(area, (maxcurx - mincurx) * (maxcury - mincury));
	}
	
	
	fout << area;
	
	return 0;
}
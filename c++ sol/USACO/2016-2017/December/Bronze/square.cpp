#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;

int main() {
	ifstream fin ("square.in");
	ofstream fout ("square.out");
	
	int ax1, ay1, ax2, ay2;
	fin >> ax1 >> ay1 >> ax2 >> ay2;
	int bx1, by1, bx2, by2;
	fin >> bx1 >> by1 >> bx2 >> by2;
	
	int maxv = 0;
	
	maxv = max(max(ax2, bx2) - min(ax1, bx1), max(ay2, by2) - min(ay1, by1));
	
	fout << pow(maxv, 2);
	
	return 0;
}
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int intersect(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2){
	if(ax1 > bx2 || bx1 > ax2 || ay1 > by2 || by1 > ay2) return 0;
	
	return (min(ax2, bx2) - max(ax1, bx1)) * (min(ay2, by2) - max(ay1, by1));
}

int main() {
	ifstream fin ("billboard.in");
	ofstream fout ("billboard.out");
	
	int b1x1, b1y1, b1x2, b1y2;
	int b2x1, b2y1, b2x2, b2y2;
	int tx1, ty1, tx2, ty2;
	fin >> b1x1 >> b1y1 >> b1x2 >> b1y2;
	fin >> b2x1 >> b2y1 >> b2x2 >> b2y2;
	fin >> tx1 >> ty1 >> tx2 >> ty2;
	
	int total = (b1x2 - b1x1) * (b1y2 - b1y1) + (b2x2 - b2x1) * (b2y2 - b2y1);
	
	total -= intersect(b1x1, b1y1, b1x2, b1y2, tx1, ty1, tx2, ty2) + intersect(b2x1, b2y1, b2x2, b2y2, tx1, ty1, tx2, ty2);
	
	fout << total;	

	return 0;
}


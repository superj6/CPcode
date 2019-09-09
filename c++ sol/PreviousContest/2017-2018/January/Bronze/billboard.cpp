#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int maxcoord(int x1, int y1, int x2, int y2, int m1, int m2, int n1, int n2){
	if(m2 >= x1 && m2 <= x2 && n2 <= y2 && n1 >= y1){
		if(m1 >= x1 && m1 <= x2 && n2 <= y2 && n1 >= y1){
			return 0;
		}
		
		return x1;
	}
	
	return m2;
}

int mincoord(int x1, int y1, int x2, int y2, int m1, int m2, int n1, int n2){
	if(m1 >= x1 && m1 <= x2 && n2 <= y2 && n1 >= y1){
		if(m2 >= x1 && m2 <= x2 && n2 <= y2 && n1 >= y1){
			return 0;
		}
		
		return x2;
	}
	
	return m1;
}

int main() {
	ifstream fin ("billboard.in");
	ofstream fout ("billboard.out");
	
	int ax1, ay1, ax2, ay2;
	int bx1, by1, bx2, by2;
	fin >> ax1 >> ay1 >> ax2 >> ay2;
	fin >> bx1 >> by1 >> bx2 >> by2;
	
	int total = (maxcoord(bx1, by1, bx2, by2, ax1, ax2, ay1, ay2) - mincoord(bx1, by1, bx2, by2, ax1, ax2, ay1, ay2)) * (maxcoord(by1, bx1, by2, bx2, ay1, ay2, ax1, ax2) - mincoord(by1, bx1, by2, bx2, ay1, ay2, ax1, ax2));
	
	fout << total;
	
	return 0;
}
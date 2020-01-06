#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
	ifstream fin ("lostcow.in");
	ofstream fout ("lostcow.out");
	
	int x, y, total = 0;
	fin >> x >> y;
	int curr = x, last = x;
	
	while(true){
		
		if((y >= last && y <= curr) || (y <= last && y >= curr)){
			total += abs(y - last);
			fout << total;
			return 0;
		}
		
		int temp = curr - last;
		total += abs(temp);
		
		if(temp == 0){
			curr++;
		}else{
			last = curr;
			curr = x - 2 * (curr - x);
		}
	}
	
	return 0;
}
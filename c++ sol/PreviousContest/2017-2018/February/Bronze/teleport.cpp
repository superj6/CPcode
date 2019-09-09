#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
	ifstream fin ("teleport.in");
	ofstream fout ("teleport.out");
	
	int a, b, x, y;
	fin >> a >> b >> x >> y;
	
	int answer = abs(b - a);
	answer = min(answer, abs(a-x) + abs(b-y));
	answer = min(answer, abs(b-x) + abs(a-y));
	
	fout << answer;
	
	return 0;
}
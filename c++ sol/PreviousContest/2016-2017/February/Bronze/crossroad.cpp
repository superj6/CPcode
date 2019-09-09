#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("crossroad.in");
	ofstream fout ("crossroad.out");
	
	int n, amount = 0;
	fin >> n;
	int state[10];
	for(int i = 0; i < 10; i++) state[i] = -1;
	
	
	for(int i = 0; i < n; i++){
		int a, b;
		fin >> a >> b;
		a--;
		
		if(state[a] == -1){
			state[a] = b;
		}else if(state[a] != b){
			state[a] = b;
			amount++;
		}
	}
	
	fout << amount;
	
	return 0;
}
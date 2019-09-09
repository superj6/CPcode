#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int n, h, best = -1;
vector<int> strength, weight, height;

int recurse(int bits){
	if(strength[bits] != -1) return strength[bits];
	
	for(int i = 0; i < n; i++){
		int newbits = bits & ~( 1 << i);
		if(newbits == bits) continue;
		
		strength[bits] = max(strength[bits], min(recurse(newbits) - weight[i], strength[1 << i]));
		if(height[bits] == -1) height[bits] = height[newbits] + height[1 << i];
	}
	
	if(strength[bits] != -1){
		if(height[bits] >= h) best = max(best, strength[bits]);
	}else{
		strength[bits] = 0;
	}
	
	return strength[bits];
}

int main(){
	ifstream fin ("guard.in");
	ofstream fout ("guard.out");

	fin >> n >> h;
	weight.resize(n), strength.resize(1 << n), height.resize(1 << n);
	
	for(int i = 0; i < 1 << n; i++) strength[i] = -1, height[i] = -1;
	
	for(int i = 0; i < n; i++){
		fin >> height[1 << i] >> weight[i] >> strength[1 << i];
	}
	
	int temp = recurse((1 << n) - 1);

	if(best == -1){
		fout << "Mark is too tall" << endl;
	}else{
		fout << best << endl;
	}

	return 0;
}
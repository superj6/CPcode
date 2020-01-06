#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;


int main() {
	ifstream fin ("hoofball.in");
	ofstream fout ("hoofball.out");
	
	int n;
	fin >> n;
	int dist[n];
	int pass[n];
	
	for(int i = 0; i < n; i++){
		fin >> dist[i];
	}
	
	sort(dist, dist+n);
	
	for(int i = 0; i < n; i++){
		
		if(i == 0){
			pass[i] = 1;
			continue;
		}
		if( i == n - 1){
			pass[i] = n-2;
			continue;
		}
		
		if(abs(dist[i + 1] - dist[i]) >= abs(dist[i - 1] - dist[i])){
			pass[i] = i - 1;
		}else{
			pass[i] = i + 1;
		}
	}
	
	int amount = 0;
	int passto[n];
	for(int i = 0; i < n; i++) passto[i] = 0;
 
	for(int i = 0; i < n; i++){
		passto[pass[i]]++;
	}
 
	for(int i = 0; i < n; i++){
		if(passto[i] == 0) amount++;
 
		if(i > 0){
			if(passto[i-1] == 1 && passto[i] == 1 && pass[i-1] == i && pass[i] == i-1) amount++;
		}
	}
	
	fout << amount;
	
	return 0;
}
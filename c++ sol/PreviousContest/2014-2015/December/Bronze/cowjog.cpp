#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

struct cow{
	long long p, s;
	
	cow(long long p, long long s){
		this->p = p;
		this->s = s;
	}
	
	friend bool operator<(cow a, cow b){
		return a.p > b.p;
	}
	
};

int main(){
	ifstream fin ("cowjog.in");
	ofstream fout ("cowjog.out");

	long long n, t;
	fin >> n >> t;
	vector<cow> cows;
	
	for(int i = 0; i < n; i++){
		long long p, s;
		fin >> p >> s;
		
		cows.push_back(cow(p, s));
	}
	
	sort(cows.begin(), cows.end());
	
	long long groups = 1, currpos = cows[0].p + cows[0].s * t;
	
	for(int i = 1; i < n; i++){
		
		if(cows[i].p + cows[i].s * t < currpos){
			groups++;
			currpos = cows[i].p + cows[i].s * t;
		}
		
	}

	fout << groups << endl;

	return 0;
}
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

int main() {
	ifstream fin ("badmilk.in");
	ofstream fout ("badmilk.out");
	
	int n, m, d, s;
	fin >> n >> m >> d >> s;
	
	int pmt[n][m];
	int milkmax[m];
	
	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) pmt[i][j] = 101;
	for(int i = 0; i < m; i++) milkmax[i] = 0;
	
	for(int i = 0; i < d; i++){
		int p, mi, t;
		fin >> p >> mi >> t;
		p--;
		mi--;
		
		pmt[p][mi] = min(pmt[p][mi], t);
	}
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(pmt[i][j] != 101) milkmax[j]++;
		}
	}
	
	for(int i = 0; i < s; i++){
		int a, b;
		fin >> a >> b;
		a--;
		
		for(int i = 0; i < m; i++){
			if(pmt[a][i] >= b) milkmax[i] = 0;
		}
	}
	
	int out = 0;
	for(int i = 0; i < m; i++) out = max(out, milkmax[i]);
	
	fout << out;
	
	return 0;
}
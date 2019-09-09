#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

int main(){
	ifstream fin ("bgm.in");
	ofstream fout ("bgm.out"); 
	
	map<char, int> letter;
	letter['B'] = 0;
	letter['E'] = 1;
	letter['S'] = 2;
	letter['I'] = 3;
	letter['G'] = 4;
	letter['O'] = 5;
	letter['M'] = 6;

	int n;
	fin >> n;
	long long amount[7][7];
	
	for(int i = 0; i < 7; i++) for(int j = 0; j < 7; j++) amount[i][j] = 0;
	
	for(int i = 0; i < n; i++){
		char c;
		int l, val;
		fin >> c >> val;
		l = letter.find(c)->second;
		
		amount[l][(val + 700000) % 7]++;
	}
	
	long long result = 0;
	
	for(int b = 0; b < 7; b++)
	for(int e = 0; e < 7; e++)
	for(int s = 0; s < 7; s++)
	for(int i = 0; i < 7; i++)
	for(int g = 0; g < 7; g++)
	for(int o = 0; o < 7; o++)
	for(int m = 0; m < 7; m++){
		if(((((b + e + s + s + i + e) % 7) * ((g + o + e + s) % 7) % 7) * ((m + o + o) % 7)) % 7 == 0){
			result += amount[0][b] * amount[1][e] * amount[2][s] * amount[3][i] * amount[4][g] * amount[5][o] * amount[6][m];
		}
	}
	
	fout << result << endl;

	return 0;
}
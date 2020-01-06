#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	ifstream fin ("blocks.in");
	ofstream fout ("blocks.out");
	
	int n;
	fin >> n;
	int totalcount[26];
	for(int i = 0; i < 26; i++) totalcount[i] = 0;
	
	for(int i = 0; i < n; i++){
		string one, two;
		fin >> one >> two;
		
		int countone[26], counttwo[26];
		
		for(int j = 0; j < 26; j++){
			countone[j] = 0;
			counttwo[j] = 0;
		} 
		
		for(int j = 0; j < one.length(); j++){
			countone[(int)(one[j] - 'a')]++;
		}
		
		for(int j = 0; j < two.length(); j++){
			counttwo[(int)(two[j] - 'a')]++;
		}
		
		for(int j = 0; j < 26; j++){
			totalcount[j] += max(countone[j], counttwo[j]);
		}
	}
	
	for(int i = 0; i < 26; i++){
		fout << totalcount[i] << endl;
	}
	
	return 0;
}
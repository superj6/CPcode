#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("circlecross.in");
	ofstream fout ("circlecross.out");
	
	int begin[26], end[26], total = 0;
	
	for(int i = 0; i < 26; i++) begin[i] = -1;
	
	char array[52];
	fin >> array;
	
	for(int i = 0; i < 52; i++){
		int index = array[i] - 'A';
		
		if(begin[index] == -1){
			begin[index] = i;
		}else{
			end[index] = i;
		}
	}
	
	for(int i = 0; i < 26; i++){
		for(int j = i + 1; j < 26; j++){
			if((end[j] > end[i] && begin[j] < end[i] && begin[j] > begin[i]) || (end[i] > end[j] && begin[i] < end[j] && begin[i] > begin[j])) total++;
		}
	}
	
	fout << total;
	
	return 0;
}
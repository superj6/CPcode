#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

int mod = 2014;
unordered_map<string, int> memo;

int recurse(string code){
	if(memo.find(code) != memo.end()) return memo[code];
	
	int answer = 1;
	int l = code.size();
	
	for(int i = 1; i * 2 < l; i++){
		if(code.substr(0, i) == code.substr(i, i)) answer += recurse(code.substr(i, l - i));
		
		if(code.substr(0, i) == code.substr(l - i, i)) answer += recurse(code.substr(i, l - i));
		
		if(code.substr(l - i, i) == code.substr(0, i)) answer += recurse(code.substr(0, l - i));
		
		if(code.substr(l - i, i) == code.substr(l - 2 * i, i)) answer += recurse(code.substr(0, l - i));
	}
	
	answer %= mod;
	memo[code] = answer;
	return answer;
}

int main(){
	ifstream fin ("scode.in");
	ofstream fout ("scode.out");
	
	string code;
	fin >> code;
	
	fout << (recurse(code) - 1 + mod) % mod << endl;

	return 0;
}
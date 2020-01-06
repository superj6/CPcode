#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main(){
	ifstream fin ("censor.in");
	ofstream fout ("censor.out");

	string s, t;
	fin >> s >> t;
	
	vector<int> tval(t.size() + 1, -1);
	int cnd = 0;
	
	for(int i = 1; i < t.size(); i++){
		if(t[i] == t[cnd]){
			tval[i] = tval[cnd];
		}else{
			tval[i] = cnd;
			cnd = tval[cnd];
			
			while(cnd >= 0 && t[i] != t[cnd]){
				cnd = tval[cnd];
			}
		}
		cnd++;
	}
	tval[t.size()] = cnd;
	
	string r;
	int j = 0, k = 0;
	vector<int> rval(1, -1);
	
	while(j < s.length()){
		if(t[k] == s[j]){
			r += s[j];
			rval.push_back(k);
			j++;
			k++;
			if(k == t.length()){
				r.resize(r.size() - t.size());
				rval.resize(rval.size() - t.size());
				k = rval.back();
				k++;
			}
		}else{
			k = tval[k];
			if(k < 0){
				r += s[j];
				rval.push_back(k);
				j++;
				k++;
			}
		}
	}

	fout << r;

	return 0;
}
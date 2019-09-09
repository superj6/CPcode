#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

t.s

long hext(long h, long ch){
	return (h * HA + ch + HB) % HM;
}

int main(){
	ifstream fin ("censor.in");
	ofstream fout ("censor.out");

	string s, t;
	fin >> s >> t;
	
	long thsh = 0;
	for(int i = 0; i < t.size(); i++) thsh = hext(thsh, t[i] - 'a');
	
	string r;
	vector<long> rhsh(1, 0);
	vector<long> HApow(1, 1);
	for(int i = 0; i < s.size(); i++){
		r += s[i];
		
		rhsh.push_back(hext(rhsh.back(), s[i] - 'a'));
		HApow.push_back((HApow.back() * HA) % HM);
		
		if(r.size() >= t.size()){
			long hsub = (rhsh[r.size() - t.size()] * HApow[t.size()]) % HM;
			long hsh = (HM + rhsh.back() - hsub) % HM;
			
			if(hsh == thsh){
				rhsh.resize(rhsh.size() - t.size());
				HApow.resize(HApow.size() - t.size());
				r.resize(r.size() - t.size());
			}
		}
	}
	
	fout << r;

	return 0;
}
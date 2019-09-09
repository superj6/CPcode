#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
#define endl '\n'

long HM = 1000000007;
long HA = 10000007;
long HB = 101;

long hext(long h, long ch){
	return (h * HA + ch + HB) % HM;
}

int main(){
	freopen("censor.in", "r", stdin);
	freopen("censor.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string s;
	cin >> s;
	
	int n;
	cin >> n;
	
	unordered_map<int, unordered_map<long, int>> t;
	for(int i = 0; i < n; i++){
		string ti;
		cin >> ti;
		
		long thsh = 0;
		for(int j = 0; j < ti.size(); j++) thsh = hext(thsh, ti[j] - 'a');
		
		t[ti.size()][thsh] = 1;
	}
	
	string r;
	vector<long> rhsh(1, 0);
	vector<long> HApow(1, 1);
	
	for(int i = 0; i < s.size(); i++){
		r += s[i];
		
		rhsh.push_back(hext(rhsh.back(), s[i] - 'a'));
		HApow.push_back((HApow.back() * HA) % HM);
		
		for(const auto& it : t){
			if(r.size() < it.first) continue;
			
			long hsub = (rhsh[r.size() - it.first] * HApow[it.first]) % HM;
			long hsh = (HM + rhsh.back() - hsub) % HM;
			
			if(it.second.find(hsh) != it.second.end()){
				rhsh.resize(rhsh.size() - it.first);
				HApow.resize(HApow.size() - it.first);
				r.resize(r.size() - it.first);
				break;
			}
			
		}
	}
	
	cout << r << endl;

	return 0;
}
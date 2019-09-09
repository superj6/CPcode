#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

void gen(string out, string left){
	int k = left.size();
	if(k == 0){
		cout << out << endl;
		return;
	}
	
	for(int i = 0; i < k; i++){
		if(i > 0 && left[i] == left[i - 1]) continue;
		gen(out + left[i], left.substr(0, i) + left.substr(i + 1, k - i - 1));
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int f[9];
	f[0] = 1;
	for(int i = 1; i <= 8; i++) f[i] = f[i - 1] * i;
	
	string s;
	cin >> s;
	
	sort(s.begin(), s.end());
	
	int n = f[s.size()];
	
	for(int i = 0, amt = 1; i < s.size(); i++){
		if(i + 1 == s.size() || s[i] != s[i + 1]){
			n /= f[amt];
			amt = 1;
		}else{
			amt++;
		}
	}
	
	cout << n << endl;
	gen("", s);
	
	return 0;
}
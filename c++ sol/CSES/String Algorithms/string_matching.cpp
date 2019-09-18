#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string s, t;
	cin >> s >> t;
	
	int r[t.size() + 1];
	r[0] = -1;
	
	int p = 1, c = 0;
	while(p < t.size()){
		if(t[p] == t[c]){
			r[p] = r[c];
		}else{
			r[p] = c;
			c = r[c];
			while(c >= 0 && t[p] != t[c]) c = r[c];
		}
		p++, c++;
	}
	r[p] = c;
	
	int j = 0, k = 0, ret = 0;
	while(j < s.size()){
		if(s[j] == t[k]){
			j++, k++;
			if(k == t.size()){
				ret++;
				k = r[k];
			}
		}else{
			k = r[k];
			if(k < 0) j++, k++;
		}
	}
	
	cout << ret << endl;

	return 0;
}
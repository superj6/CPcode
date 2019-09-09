#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string s;
	cin >> s;
	
	int amt[s.size()];
	amt[0] = 1;
	int best = 1;
	
	for(int i = 1; i < s.size(); i++){
		amt[i] = 1 + (s[i - 1] == s[i] ? amt[i - 1] : 0);
		best = max(best, amt[i]);
	} 
	
	cout << best << endl;

	return 0;
}
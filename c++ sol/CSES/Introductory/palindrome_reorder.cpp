#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string s;
	cin >> s;
	
	int amt[26];
	memset(amt, 0, sizeof(amt));
	
	for(int i = 0; i < s.size(); i++) amt[s[i] - 'A']++;
	
	string t;
	int mid = -1;
	
	for(int i = 0; i < 26; i++){
		if(amt[i] % 2 == 0){
			for(int j = 0; j < amt[i] / 2; j++) t += (i + 'A');
		}else if(mid == -1){
			mid = i;
		}else{
			cout << "NO SOLUTION" << endl;
			return 0;
		}
	}
	
	if(mid != -1){
		for(int i = 0; i < amt[mid]; i++) t += (mid + 'A');
	}
	
	for(int i = 25; i >= 0; i--){
		if(i == mid) continue;
		for(int j = 0; j < amt[i] / 2; j++) t += (i + 'A');
	}
	
	cout << t << endl;

	return 0;
}
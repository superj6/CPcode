#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	string s;
	cin >> s;
	n = s.size();
	
	int r[n + 1];
	r[0] = 0;
	
	for(int i = 1; i < n; i++){
		int j = r[i - 1];
		while(j > 0 && s[i] != s[j]) j = r[j - 1];
		if(s[i] == s[j]) j++;
		r[i] = j;
	}
	
	vector<int> ans;
	for(int i = r[n - 1]; i > 0; i = r[i - 1]) ans.push_back(i);
	reverse(ans.begin(), ans.end());
	
	if(ans.size()) cout << ans[0];
	for(int i = 1; i < ans.size(); i++) cout << " " << ans[i];
	cout << endl;
	return 0;
}
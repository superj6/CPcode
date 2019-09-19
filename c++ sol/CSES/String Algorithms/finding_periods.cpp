/*
This is code of SuperJ6 for Codeforces.
Don't copy my code during f*kin' contests.

2.71828182845904523536
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const long long hm = 1e9 + 7;
const long long ha = 1e8 + 7;

long long hsh(long long c, long long d){
	return (c * ha + d) % hm;
}

const int maxn = 1e6 + 1;
int n;
string s;
long long h[maxn], p[maxn];
vector<int> ans;

bool works(int x){
	for(int i = x; i < n + x; i += x){
		int l = min(x, n + x - i);
		if(((h[min(i, n)] - (p[l] * h[min(i, n) - l]) % hm + hm) % hm) != h[l]) return 0;
	}
	return 1;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> s;
	n = s.size();
	
	p[0] = 1;
	
	for(int i = 0; i < n; i++){
		h[i + 1] = hsh(h[i], s[i]);
		p[i + 1] = (p[i] * ha) % hm;
	}
	
	for(int i = 1; i <= n; i++) if(works(i)) ans.push_back(i);
	
	cout << ans[0];
	for(int i = 1; i < ans.size(); i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}
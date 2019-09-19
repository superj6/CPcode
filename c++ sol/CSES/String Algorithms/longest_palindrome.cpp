#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	string s;
	cin >> s;
	n = s.size();
	
	int d1[n], d2[n];
	int p1 = 0, p2 = 0;
	
	for(int i = 0, l = 0, r = -1; i < n; i++){
		int k = i > r ? 1 : min(d1[l + r - i], r - i + 1);
		while(0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
		d1[i] = k--;
		if(i + k > r) l = i - k, r = i + k;
		if(d1[i] > d1[p1]) p1 = i;
	}
	
	for(int i = 0, l = 0, r = -1; i < n; i++){
		int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
		while(0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
		d2[i] = k--;
		if(i + k > r) l = i - k - 1, r = i + k;
		if(d2[i] > d2[p2]) p2 = i;
	}
	
	cout << (2 * d1[p1] - 1 > 2 * d2[p2] ? s.substr(p1 - d1[p1] + 1, 2 * d1[p1] - 1) : s.substr(p2 - d2[p2], 2 * d2[p2])) << endl;
	
	return 0;
}
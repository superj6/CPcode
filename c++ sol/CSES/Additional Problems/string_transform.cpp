#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 1000000, k = 27;
int n;
string s;
vector<int> t;
vector<int> a[k];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> s;
	n = s.size();
	
	for(int i = 0; i < n; i++){
		a[max(0, s[i] - 'a' + 1)].push_back(i);
	}
	
	for(int i = 0; i < k; i++){
		for(int j : a[i]) t.push_back(j);
	}
	
	for(int i = t[a[0][0]]; i != a[0][0]; i = t[i]) cout << s[i];
	cout << endl;

	return 0;
}
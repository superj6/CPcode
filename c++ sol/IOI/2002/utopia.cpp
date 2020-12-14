#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 10000;
int n;
int a[2][mxn], s[2][mxn];
int l[2], r[2];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int t = 0; t < 2; t++){
		for(int i = 0; i < n; i++) cin >> a[t][i];
		sort(a[t], a[t] + n);
	}
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		for(int t = 0; t < 2; t++){
			s[t][i] = 2 * (!~-x || x == (1 << (2 - t))) - 1;
			l[t] += (i && s[t][i] == s[t][i - 1]);
		}
	}
	
	for(int t = 0; t < 2; t++) r[t] = l[t]--;
	
	for(int i = 0; i < n; i++)
	for(int t = 0; t < 2; t++){
		int x;
		if(!i || s[t][i] != s[t][i - 1]) x = (a[t][r[t]] *= s[t][i]), r[t]++;
		else x = (a[t][l[t]] *= (2 * (a[t][l[t] + 1] < 0) - 1)), l[t]--;
		cout << (x > 0 ? '+' : '-') << abs(x) << (t ? endl : ' ');
	}

	return 0;
}
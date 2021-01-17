#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int n = 10000001;
int m;
int a, b, c, d;
int f[n], lp[n];
vector<int> p;

void answer(){
	cin >> a >> b >> c >> d;
	
	bool ret = 0;
	for(int i = 0; i < m; i++){
		f[i] = 0;
		for(int j = p[i]; j < n; j *= p[i])
		for(int l = j; l < n; l += j){
			f[i] += (l >= a && l <= b) - (l >= c && l <= d);
		}
		ret |= f[i] > 0;
	}
	
	cout << (ret ? "NE" : "DA") << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	for(int i = 2; i < n; i++){
		if(!lp[i]) p.push_back(lp[i] = i), m++;
		for(int j = 0; j < m && p[j] <= lp[i] && i * p[j] < n; j++){
			lp[i * p[j]] = p[j];
		}
	}
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}
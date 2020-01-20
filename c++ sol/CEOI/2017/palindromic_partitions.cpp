#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const long long hm = 1000000007;
const long long ha = 100000007;
const long long hb = 101;

int hsh(int c, int d){
	return (ha * c + d + hb) % hm;
}

const int maxn = 1000001;
int n;
string s;
long long a[maxn], p[maxn];

int h(int l, int r){
	return (hm + a[r] - a[l - 1] * p[r - l + 1] % hm) % hm;
}

void answer(){
	cin >> s;
	n = s.size();
	
	p[0] = 1;
	for(int i = 0; i < n; i++){
		a[i + 1] = hsh(a[i], s[i]);
		p[i + 1] = p[i] * ha % hm;
	}
	
	int ret = 1;
	for(int i = 0, l = 0; i < n / 2; i++){
		if(h(l + 1, i + 1) == h(n - i, n - l)){
			ret += 2 - (2 * i + 2 == n);
			l = i + 1;
		}
	}
	
	cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}
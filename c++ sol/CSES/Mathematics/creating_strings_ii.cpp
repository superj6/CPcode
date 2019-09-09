#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 1e6 + 1, mod = 1e9 + 7;
long long f[maxn], rf[maxn];
int cnt[26];

void gen(){
	f[0] = rf[0] = 1;
	
	for(int i = 1; i < maxn; i++){
		f[i] = (f[i - 1] * i) % mod;
		rf[i] = 1;
		
		for(long long j = 0, k = f[i]; (1 << j) <= mod - 2; j++){
			if((1 << j) & (mod - 2)) rf[i] = (rf[i] * k) % mod;
			k = (k * k) % mod;
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	gen();
	
	string s;
	cin >> s;
	
	for(int i = 0; i < s.size(); i++) cnt[s[i] - 'a']++;
	
	long long ret = f[s.size()];
	for(int i = 0; i < 26; i++) ret = (ret * rf[cnt[i]]) % mod;
	
	cout << ret << endl;

	return 0;
}
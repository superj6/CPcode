#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <unordered_map>
using namespace std;
#define endl '\n'

const int maxn = 501;
int n, m;
long long s[maxn << 1][maxn];
long long p[maxn];

long long mod = 1000000007;
long long ha = 100000007;
long long hsh(int c, int d){
	return (ha * c + d) % mod;
}

bool works(int x){
	for(int j = x; j <= m; j++){
		bool t = 1;
		unordered_map<int, bool> used;
		for(int i = 0; i < 2 * n; i++){
			int cur = (mod + s[i][j] - (p[x] * s[i][j - x]) % mod) % mod;
			if(i < n) used[cur] = 1;
			else if(used[cur]){
				t = 0;
				break;
			}
		}
		
		if(t) return 1;
	}
	return 0;
}

int main(){
	freopen("cownomics.in", "r", stdin);
	freopen("cownomics.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < 2 * n; i++){
		string t;
		cin >> t;
		for(int j = 0; j < m; j++){
			s[i][j + 1] = hsh(s[i][j], t[j]);
		}
	}
	
	p[0] = 1;
	for(int i = 0; i < m; i++) p[i + 1] = (ha * p[i]) % mod;
	
	int l = 0, r = m;
	while(r - l > 1){
		int mid = (l + r + 1) / 2;
		if(works(mid)) r = mid;
		else l = mid;
	}
	
	cout << r << endl;

	return 0;
}
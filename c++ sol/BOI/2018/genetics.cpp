#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
#include <bitset>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 4100;
int n, m, k;
bitset<maxn> a[maxn];
bool works[maxn];

void solve(){
	string s[n];
	for(int i = 0; i < n; i++){
		cin >> s[i];
		works[i] = 1;
		for(int j = 0; j < i; j++){
			int x = 0;
			for(int l = 0; l < m; l++){
				x += (s[i][l] != s[j][l]);
			}
			works[i] &= (x == k);
			works[j] &= (x == k);
		}
	}
	for(int i = 0; i < n; i++) if(works[i]) cout << (i + 1) << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k;
	
	if(n <= 100){
		solve();
		return 0;
	}
	
	for(int i = 0; i < n; i++){
		cin.ignore();
		for(int j = 0; j < m; j++){
			a[i][j] = (cin.get() == 'A');
		}
		works[i] = 1;
		for(int j = 0; j < i; j++){
			int s = (a[i] ^ a[j]).count();
			works[i] &= (s == k);
			works[j] &= (s == k);
		}
	}
	
	for(int i = 0; i < n; i++) if(works[i]) cout << (i + 1) << endl;

	return 0;
}
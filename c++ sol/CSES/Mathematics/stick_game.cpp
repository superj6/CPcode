#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'

const int maxn = 1000001, maxk = 100;
int n, k;
int p[maxk];
int dp[maxn];

void precomp(){
	for(int i = 1; i <= n; i++){
		set<int> used;
		for(int j = 0; j < k; j++){
			if(i - p[j] >= 0) used.insert(dp[i - p[j]]);
		}
		
		int j = 0;
		for(auto it = used.begin(); it != used.end(); it++, j++) if(j != *it) break;
		
		dp[i] = j;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 0; i < k; i++) cin >> p[i];
	
	precomp();
	
	for(int i = 1; i <= n; i++) cout << (dp[i] ? 'W' : 'L');
	cout << endl;
	
	return 0;
}
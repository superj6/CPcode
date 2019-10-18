#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;

const int maxn = 1501;
int r, c, k, h, v;
int cuth[maxn], cutv[maxn];
int dp[maxn][maxn];

bool works(int x){
	int jt[h + 1];
	memset(jt, 0, sizeof(jt));
	
	for(int i = 0, it = 0; i <= h; i++){
		for(int j = 0; j <= v; j++){
			if(cuth[i] * cutv[j] <= x){
				dp[i][j] = 0;
				continue;
			}
			dp[i][j] = k + 1;
			
			while(cuth[it] < cuth[i] - x / cutv[j]) it++;
			if(it < i) dp[i][j] = min(dp[i][j], dp[it][j] + 1);
			
			while(cutv[jt[i]] < cutv[j] - x / cuth[i]) jt[i]++;
			if(jt[i] < j) dp[i][j] = min(dp[i][j], dp[i][jt[i]] + 1);
			
			if(dp[i][j] > k) return 0;
		}
	}
	
	return 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> r >> c >> k >> h >> v;
	
	for(int i = 0; i < h; i++) cin >> cuth[i];
	cuth[h] = r;
	for(int i = 0; i < v; i++) cin >> cutv[i];
	cutv[v] = c;
	
	int lo = 1, hi = r * c;
	while(hi - lo > 1){
		int mid = (lo + hi) / 2;
		if(works(mid)) hi = mid;
		else lo = mid;
	}
	
	cout << hi << endl;
	
	return 0;
}
/*
This is code of SuperJ6 for Codeforces.
Don't copy my code during f*kin' contests.

2.71828182845904523536
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>	

const int maxn = 400000, k = 20;
int n;
int a[maxn];
int m[k];
int cost[k][maxn];

void solve(int x){
	if(!m[x]) return;
	
	cost[x][0] -= m[x] * (m[x] - 1) / 2;
	
	for(int i = 1, l = 0; i + m[x] <= n; i++){
		cost[x][i] = cost[x][i - 1];
		
		while(a[i - 1 + l] == x) l++;
		cost[x][i] += l;
		cost[x][i] -= m[x] - l;
	}
}

int dp[1 << k];
int recur(int c, int x){
	if(c == n) return 0;
	if(dp[x] != -1) return dp[x];
	
	int ret = 1000000007;
	
	for(int i = 0; i < k; i++){
		if(!m[i] || x & (1 << i) || cost[i][c] >= ret) continue;
		
		ret = min(ret, recur(c + m[i], x | (1 << i)) + cost[i][c]);
	}
	
	return dp[x] = ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i]--;
		m[a[i]]++;
		cost[a[i]][0] += i;
	}
	
	for(int i = 0; i < k; i++) solve(i);
	
	memset(dp, -1, sizeof(dp));
	
	cout << recur(0, 0) / 2 << endl;
	
	for(int i = 0; i < k; i++){
		if(!m[i]) continue;
		cout << i + 1 << " : ";
		for(int j = 0; j < n; j++) cout << cost[i][j] << " ";
		cout << endl;
	}

	return 0;
}
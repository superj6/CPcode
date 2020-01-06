#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 10001, maxq = 101;

int n, m, q;
int a[maxn], dp[maxn], ind[maxn], qi[maxq];
pi qry[maxq];
int ans[maxn][maxq];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	cin >> q;
	
	for(int i = 0; i < q; i++){
		cin >> qry[i].first;
		qry[i].second = i;
	}
	
	sort(qry, qry + q);
	for(int i = 0; i < q; i++) qi[qry[i].second] = i;
	for(int i = 0, j = 0; i <= m; i++){
		while(j < q && qry[j].first == i - 1) j++;
		ind[i] = j;
	}
	
	for(int j = 1; j < n; j++){
		for(int i = 0; i + j < n; i++){
			dp[i] = (a[i] != a[i + j]) + (i ? dp[i - 1] : 0);
			if(i >= m - 1){
				int k = ind[dp[i] - (i >= m ? dp[i - m] : 0)];
				ans[i - m + 1][k]++;
				ans[i + j - m + 1][k]++;
			}
		}
	}
	
	for(int i = 0; i < n - m + 1; i++){
		for(int j = 1; j < q; j++) ans[i][j] += ans[i][j - 1];
	}
	
	for(int i = 0; i < q; i++){
		cout << ans[0][qi[i]];
		for(int j = 1; j < n - m + 1; j++) cout << " " << ans[j][qi[i]];
		cout << endl;
	}

	return 0;
}
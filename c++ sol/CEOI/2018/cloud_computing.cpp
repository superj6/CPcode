#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 4000, k = 100001;
int n, m;
long long dp[k];
vector<int> a[maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		a[i].resize(3);
		cin >> a[i][1] >> a[i][0] >> a[i][2];
		a[i][2] *= -1;
	}
	
	cin >> m;
	
	for(int i = n; i < n + m; i++){
		a[i].resize(3);
		cin >> a[i][1] >> a[i][0] >> a[i][2];
		a[i][1] *= -1;
	}
	
	sort(a, a + n + m);
	
	for(int i = 0; i < n + m; i++){
		for(int j = (a[i][1] < 0 ? k - 1 : 0); j >= -a[i][1] && j < k - a[i][1]; j += (a[i][1] < 0 ? -1 : 1)){
			dp[j] = max(dp[j], dp[j + a[i][1]] + a[i][2]);
		}
	}
	
	cout << dp[0] << endl;

	return 0;
}

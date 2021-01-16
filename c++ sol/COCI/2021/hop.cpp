#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 1000, k = 3;
int n;
ll a[mxn], dp[mxn][k];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		for(int j = 0; j < i; j++){
			int x = min_element(dp[j], dp[j] + k) - dp[j];
			if(!(a[i] % a[j])) dp[i][x] = max(dp[i][x], dp[j][x] + 1);
			cout << (x + 1) << (j == i - 1 ? endl : ' ');
		}
	}
	
	return 0;
}
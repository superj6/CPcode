#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <vector>
#include <tuple>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<pi, pi>
#define f first
#define s second

const int mxn = 300002;
int n, m, k;
int a[mxn], f[mxn];
int b[mxn][3], dp[mxn][3], p[mxn][3], pp[mxn][3];
vector<int> v;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> m >> k >> n;
	
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		f[i] = a[i];
	}
	
	sort(a + 1, a + n + 1);
	a[n + 1] = m;
	
	for(int i = 1, j = 1, mn = 0x3f3f3f3f, mnp = -1, mnpp = -1; i <= n; i++){
		while(a[i] - a[j] >= k) j++;
		b[i][0] = max(k, a[i]), b[i][1] = min(a[i + 1], a[j] + k - 1), b[i][2] = min(a[i + 1], a[i] + k - 1);
		for(int l = 0; l < 3; l++){
			dp[i][l] = mn + b[i][l], p[i][l] = mnp, pp[i][l] = mnpp;
			for(int r = 0; r < 3; r++){
				int x = (l < 2 ? j : i) - 1;
				if(dp[x][r] + k < dp[i][l]){
					dp[i][l] = dp[x][r] + k, p[i][l] = x, pp[i][l] = r;
				}
			}
			if(dp[i][l] - b[i][l] <= mn){
				mn = dp[i][l] - b[i][l], mnp = i, mnpp = l;
			}
		}
	}

	int ret = min_element(dp[n], dp[n] + 3) - dp[n];
	for(int i = n, j = ret; i; tie(i, j) = make_tuple(p[i][j], pp[i][j])){
		v.push_back(b[i][j]);
	} 
	
	reverse(v.begin(), v.end());
	
	cout << dp[n][ret] << endl;
	for(int i = 1; i <= n; i++){
		int x = *lower_bound(v.begin(), v.end(), f[i]);
		cout << (x - k + 1) << " " << x << endl;
	}

	return 0;
}
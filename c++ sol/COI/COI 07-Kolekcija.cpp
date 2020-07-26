/*
	Trying to do dp by having states that assume each interval begins on an input point, and hold best transition plus
using two pointers. However, I am only getting 40/100 points.
*/

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

int c1[mxn], c2[mxn], c3[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> m >> k >> n;
	
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		f[i] = a[i];
		c1[a[i]] = 1;
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
				if(dp[x][r] + k <= dp[i][l]){
					dp[i][l] = dp[x][r] + k, p[i][l] = x, pp[i][l] = r;
				}
			}
			if(b[i][l] >= k && b[i][l] <= a[i + 1] && dp[i][l] - b[i][l] <= mn){
				mn = dp[i][l] - b[i][l], mnp = i, mnpp = l;
			}
		}
		/*
		cout << a[i] << endl;
		cout << b[i][0] << " " << b[i][1] << " " << b[i][2] << endl;
		cout << dp[i][0] << " " << dp[i][1] << " " << dp[i][2] << endl;
		cout << pp[i][0] << " " << pp[i][1] << " " << pp[i][2] << endl;
		cout << endl;
		*/
	}
	//cout << "<---------------------------------------------->" << endl;
	int ret = min_element(dp[n], dp[n] + 3) - dp[n];
	for(int i = n, j = ret; i; tie(i, j) = make_tuple(p[i][j], pp[i][j])){
		//cout << i << " " << j << endl;
		//cout << b[i][j] << endl;
		v.push_back(b[i][j]);
	} 
	
	reverse(v.begin(), v.end());
	
	//cout << "<---------------------------------------------->" << endl;
	int ret2;
//	cin >> ret2;
	//cout << ret2 << " ";
	cout << dp[n][ret] << endl;
	for(int i = 1; i <= n; i++){
		int x = *lower_bound(v.begin(), v.end(), f[i]);
		cout << (x - k + 1) << " " << x << endl;
		
		c1[f[i]] = 1;
		int l, r;
		//cin >> l >> r;
		//for(int j = l; j <= r; j++) c2[j] = 1;
		for(int j = x - k + 1; j <= x; j++) c3[j] = 1;
	}
	
	for(int i = 1; i <= m; i++){
		//cout << i << ": " << c1[i] << " " << c2[i] << " " << c3[i] << endl;
	}

	return 0;
}

/*
  Realize that it is always optimal to have rectangles bounded by points on the left and right edges. If you place a rectangle between
two points, realize you then have to solve seperately for all points on both sides of the rectangle along with the points above the height
of the rectangle. This should lead to a range dp, where for each range you try splitting the range and taking the dp value from both sides,
or use a rectangle across the whole range and then do dp with the points in the range only higher than the rectangle. This means you can
also hold a dp state that is minimum height a point has to be where it will count towards the dp, and do the dp on each of the different
heights.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int inf = 0x3f3f3f3f;
const int mxn = 101;
int n, m;
pi a[mxn];
int dp[mxn][mxn][mxn];
vector<int> v;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		cin >> a[i].f >> a[i].s;
		v.push_back(a[i].s);
	}
	
	sort(a, a + n);
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	
	for(int i = v.size() - 1; ~i; i--)
	for(int l = n - 1; ~l; l--)
	for(int r = l; r < n; r++){
		int &dpc = dp[i][l][r] = (l < r || a[l].s >= v[i]) * inf;
		ll x = max(1, a[r].f - a[l].f);
		if(x * v[i] <= m){
			dpc = min(dpc, 1 + dp[upper_bound(v.begin(), v.end(), m / x) - v.begin()][l][r]);
		}
		for(int j = l; j < r; j++){
			dpc = min(dpc, dp[i][l][j] + dp[i][j + 1][r]);
		}
	}
	
	cout << dp[0][0][n - 1] << endl;

	return 0;
}

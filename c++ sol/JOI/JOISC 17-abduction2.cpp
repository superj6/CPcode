/*
	Realize for n = 2000 you can just do basic recursion with memoization. To speed this up, you can use sparse
table to find nearest intersection greater and then hold dp states only at intersections such that you turn. Because
q is small, you will not hit every state, and because you only look at intersection in which one is strictly greater
than the other, you only look at most n * (n - 1) / 2 ~ 1e9. The tests give 5 seconds so you just have to hope states
are sparse enough to cut out total amount of intersections by factor of 10 so O(n^2lgn) with good constant factor
passes.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <array>
#include <unordered_map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
typedef array<int, 2> T;
T operator+(T x, T y){ return {x[0] + y[0], x[1] + y[1]};}
T operator*(int x, T y){ return {x * y[0], x * y[1]};}
 
const int mxn = 50000, m = __lg(mxn - 1) + 1, k = 4;
const T d[k] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n[2], q;
int a[2][m][mxn];
unordered_map<int, ll> dp[k][mxn];
 
ll sol(T x, int y){
	ll ret = 0, s = 0;
	for(int i = m - 1; ~i; i--){
		T p = x + (1 << i) * d[y];
		if(p[y & 1] >= -1 && p[y & 1] <= n[y & 1] && a[!(y & 1)][0][p[!(y & 1)]] > 
		a[y & 1][i][y & 2 ? p[y & 1] + 1 : x[y & 1]]){
			x = p, s += (1 << i);
		}
	}
	if(!~x[y & 1] || x[y & 1] == n[y & 1]) return s;
	if(dp[y][x[0]].count(x[1])) return dp[y][x[0]][x[1]] + s;
	for(int i = 0; i < 2; i++){
		int z = (y + 2 * i + 1) % k;
		ret = max(ret, sol(x + d[z], z));
	}
	dp[y][x[0]][x[1]] = ++ret;
	return ret + s;
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n[0] >> n[1] >> q;
	
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < n[i]; j++){
			cin >> a[i][0][j];
		}
		for(int j = 1; j < m; j++)
		for(int l = 0; l + (1 << j) <= n[i]; l++){
			a[i][j][l] = max(a[i][j - 1][l], a[i][j - 1][l + (1 << (j - 1))]);
		}
	}
	
	while(q--){
		T x;
		for(int i = 0; i < 2; i++) cin >> x[i], x[i]--;
		ll ret = 0;
		for(int i = 0; i < k; i++) ret = max(ret, sol(x + d[i], i));
		cout << ret << endl;
	}
 
	return 0;
}
/*
  Use knapsack with all elements to see what sums are possible, then try subtracting each one and seeing after subtracting which
element keeps the maximum amount of sums still possible. This is your p value. Now you can always double the size of the new set
with p subtracted, so you need to find the smallest number that is not a subtraction between two numbers in your set, and because
they are all created with the numbers besides p, you can just use your same set and add the negative values with knapsack and find
the smallest number not in the new set, and that is q. Make sure you hold number of sums with modulo.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
const int mod = 1000696969;
const int mxn = 100, m = 700001;
int n;
int a[mxn];
int dp[m];
 
void f(int x, int y){
	int z = 2 * (x * y > 0) - 1;
	for(int i = ~z ? m - 1 : 0; 0 <= i && i < m; i -= z){
		if(0 <= i - x && i - x < m) (dp[i] += y * dp[i - x]) %= mod;
	}
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	dp[0] = 1;
	for(int i = 0; i < n; i++){
		cin >> a[i];
		f(a[i], 1);
	}
	
	int ret = 0, p = m, q = 0;
	for(int i = 0; i < n; i++){
		f(a[i], -1);
		int x = m - count(dp, dp + m, 0);
		if(x > ret || x == ret && a[i] < a[p]) ret = x, p = i;
		f(a[i], 1);
	}
	
	f(a[p], -1);
	
	for(int i = 0; i < n; i++) if(p != i) f(-a[i], 1);
	
	while(dp[q]) q++;
	
	cout << a[p] << " " << q << endl;
 
	return 0;
}

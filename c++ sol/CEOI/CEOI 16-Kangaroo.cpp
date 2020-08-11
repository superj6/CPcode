/*
  The problem is equivalent to find the number of permutations such that the differences between consectutive elements alternate
between being negative and positive, and the permutation starts with cf and ends with cs. We can do this by inserting elements
from 1 to n in slots of the permutation and maintain how many connected substrings of the permutation there are such that the
endpoints of the substrings must be low points except the endpoints of the permutation. When we insert an element that's not cf
or cs, we can either create a new substring component between any of the current ones or to the left or right of all of them
as long as it is not before cf or after cs, or merge two adjacent ones together since we are inserting elements in increasing 
order so it will be larger than both the merging components' endpoints. When we insert cf or cs, we can either merge it with the
component that's currently the endpoint on the same side, or we can make it a new component. To calculate the number of ways these
actions can be done, we use a dp state dp[number of elements inserted][number of components], and can output dp[n][1] at the end.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007;
const int mxn = 2001;
int n, x, y;
int dp[2][mxn];
int r;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> x >> y;
	
	dp[r++][0] = 1;
	for(int i = 1, l = 0; i <= n; i++, r ^= 1){
		int t = i == x || i == y;
		dp[r][0] = 0;
		for(int j = 1; j <= n; j++){
			if(t){
				dp[r][j] = (dp[!r][j] + dp[!r][j - 1]) % mod;
			}else{
				dp[r][j] = ((ll)max(0, j - l) * dp[!r][j - 1] + (ll)j * dp[!r][j + 1]) % mod;
			}
		}
		l += t;
	}
	r ^= 1;
	
	cout << dp[r][1] << endl;

	return 0;
}

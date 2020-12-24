/*
	Preprocess counting all paths between two vertices such that path only uses buttons < i. Let dp[i][j][l] be
number of paths from j to l with using buttons < i for all nodes between j and l, and let the button pressed on node
j and l be undecided yet. First you can add dp[i - 1][j][l] because that paths using only buttons < i - 1 also are 
also paths < i, and then add all values dp[i - 1][j][p] * dp[i - 1][p][l], as this means you are using buttons 
< i - 1 between j and p and betweeen p and l, but you chose to use button i - 1 on node p. This works because you
have no constraints for using valid paths with buttons < i - 1 from j to p, then when you hit button i - 1 on node
p you reset all lower points so you can once again use all buttons < i - 1 from p to l.
	Now to answer queries, we will calculate f1[i][j] which is number of paths using only buttons < i such that
ends on node j, and all buttons have been chosen except node j, but the first button and node chosen is x and a. You
also similarly compute f2[i][j] which is nearly the same definition except going backwards ending on node j and the
end of the path, ie the start of the dp, is button y and node b. This is calculated similar to precomputed dp as 
you can transition choosing and button for the endpoing to be then multiplying it by a dp value from the precomputed
array to end at a new location.
	Finally to get the answer of the query, we combine the forwards and backwards path at each nodes such that
we multiply f1[i][j] * f2[i][j], as we assume we are using nodes < i go forwards and backwards and the common middle
point is node j, similar to the previous calculations. However we must also add f1[y][b] and f2[x][a] as at most
one of these will be non-zero and this account for the greatest node being at an endpoint of the path. And finally,
if x == y and a == b, you only press one button without travelling any edges, and this hasn't been accounted for so
far, so you add 1 if that's the case as well. Finally you can output the sum of all those cases. The total complexity
is O(k * (n^3 + q * n^2)) for precomputing and processing queries respectively, and since mxn = mxk = mxq, you can
think of it as O(n^4), which passes nicely.	
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
const int mxn = 60;
int n, k, q;
ll dp[mxn][mxn][mxn];
ll f1[mxn][mxn], f2[mxn][mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> q;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		char c;
		cin >> c;
		dp[0][i][j] = c & 1;
	}
	
	for(int i = 1; i < k; i++)
	for(int j = 0; j < n; j++)
	for(int l = 0; l < n; l++){
		dp[i][j][l] = dp[i - 1][j][l];
		for(int p = 0; p < n; p++){
			(dp[i][j][l] += dp[i - 1][j][p] * dp[i - 1][p][l]) %= mod;
		}
	}
	
	while(q--){
		int x, a, y, b;
		cin >> x >> a >> y >> b;
		x--, a--, y--, b--;
		
		memset(f1, 0, sizeof(f1));
		memset(f2, 0, sizeof(f2));
		for(int i = 0; i < n; i++){
			if(x + 1 < k) f1[x + 1][i] = dp[x][a][i];
			if(y + 1 < k) f2[y + 1][i] = dp[y][i][b];
		}
		
		ll ret = x == y && a == b;
		for(int i = 1; i < k; i++)
		for(int j = 0; j < n; j++){
			f1[i][j] += f1[i - 1][j];
			f2[i][j] += f2[i - 1][j];
			for(int l = 0; l < n; l++){
				(f1[i][j] += f1[i - 1][l] * dp[i - 1][l][j]) %= mod;
				(f2[i][j] += f2[i - 1][l] * dp[i - 1][j][l]) %= mod;
			}
			(ret += f1[i][j] * f2[i][j]) %= mod;
		}
		(ret += f1[y][b] + f2[x][a]) %= mod;
		
		cout << ret << endl;
	}

	return 0;
}

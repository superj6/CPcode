/*
	The matrix can be thought of a set of boolean values denoting whether there is an edge between two vertices
on a bipartite graph, where rows represent left vertices and columns represent right vertices. Because each vertex
has degree 2 and the graph is bipartite, the graph must be partitioned into even length cycles. However, four 1s
making a rectangle in the matrix is equivalent to the bipartite graph having a cycle of length 4. This means you can
just calculate the number of even length cycle partitions in bipartite graphs with n nodes on each side such that
all cycles are > length 4. 
	To do this in O(n^2), realize the number of cycles of length 2 * n in a bipartite graph with n nodes on each
side is (n!)^2 / (2 * n). You can realize this by choosing a starting node and analyzing how many nodes there are
left on each side to pick at each step, as each node must be distinct. A naive O(n^2) dp is:

	dp[i] = sum of iCj * (i - 1)C(j - 1) * (j!)^2 / (2 * j) * dp[i - j] for j > 2

where dp[i] is number of partitions in bipartite graph with i nodes on each side, as you are choosing cycles of 
length 2 * j that takes the first node on one side and chooses j - 1 more and chooses j from the other side, 
multiplies that by how many cycles of length 2 * j there are, then multiplies that by the number of ways to 
partition the other i - j nodes.
	To speed this up, using some math to clean up the above formula you get:

	dp[i] = (i!)^2 / (i * 2) * sum of dp[i - j] / ((i - j)!)^2 for j > 2

Because all the coefficient of all the terms summing only depend on the terms index and not i, you can instead let
dp[i] be the sum of val(j) / (j!)^2 for all j <= i where val(j) is the previous definition of dp[j]. Now it is easy
to get the next prefix sum, as now dp[i] = dp[i - 1] + dp[i - 3] / (i * 2), since to calculate val(i) you needed to
multiply dp[i - 3] / (i * 2) by (i!)^2, so to divide by it just take the term out. Finally, to get your answer, just
just take (dp[n] - dp[n - 1]) * (i!)^2, since dp[i] is a prefix sum so dp[i] - dp[i - 1] = val(i). The time
complexity ends up being just O(n). 
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

const int mod = 200003;
const int mxn = 1000001;
int n;
ll f[mxn], iv[mxn], dp[mxn];

int main(){
	freopen("matcnt.in", "r", stdin);
	freopen("matcnt.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < 2; i++) f[i] = iv[i] = dp[i] = 1;
	for(int i = 2; i <= n; i++){
		f[i] = i * f[i - 1] % mod;
		iv[i] = mod - mod / i * iv[mod % i] % mod;
		dp[i] = (dp[i - 1] + (i >= 3 ? iv[i] * iv[2] % mod * dp[i - 3] : 0)) % mod;
	}
	
	ll ret = (mod + dp[n] - dp[n - 1]) * f[n] % mod * f[n] % mod;
	
	cout << ret << endl;

	return 0;
}
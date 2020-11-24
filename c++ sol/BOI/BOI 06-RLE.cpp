/*
  First decode into blocks of consecutive equal characters. Realize that a block of letters will always be optimally encoded if
e != block letter. This means we can hold dp[i] = minimum difference between optimal encoding up to i blocks and encoding all
blocks independently assuming e != block letter. Also for every letter, hold prefix sum[x] of cost(e == block letter x) - cost(e != block letter x).
Now, to transition for each dp[i] value, realize you want the smallest letter cost(x) which is (dp[j] - prefix block sum[x][j]) + prefix block sum[x][i].
The only letter for which the smallest cost(x) changes is for the current block's letter value, so just update cost(x) based on the
current prefix sum, calculate the best dp from all cost values, then update cost(x) based on the new dp value. Now you can just hold
cost(x) for all x in a set to get the minimal value for each dp transition. Finally, while holding dp transitions also hold what
color the interval was for the transition interval then backtrack backwards from the final dp value using parent pointers to reconstruct
when each of the letter transitions should occur, then just encode through all the blocks always change colors in the marked places.
The final complexity is O(n + mlgn) due to needed the set to maintain total minimum cost for transitions.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second
#define pb push_back

const int mxn = 2000001;
int n, m, k;
ll a[mxn], b[mxn], c[mxn], g[mxn];
ll f[mxn], fp[mxn], dp[mxn], p[mxn], ff[mxn];
set<pi> s;
vector<int> v;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	a[0] = g[0] = -1;
	for(int i = 0, j = 0; i < m; i++){
		int x, y = 1;
		cin >> x;
		if(x == j){
			cin >> x >> y;
			if(x != j && !y) j = x;
			else y += 1 + 2 * (x != j);
			i += 2;
		}
		if(a[k] == x) b[k] += y;
		else if(y) k++, a[k] = x, b[k] = y, g[k] = -1;
	}
	
	f[0] = -3;
	for(int i = 0; i < n; i++) s.insert({f[i], i});

	for(int i = 1; i <= k; i++){
		s.erase({f[a[i]] + c[a[i]], a[i]});
		c[a[i]] += 3 * (b[i] / n + !!(b[i] % n) - b[i] / (n + 2)) - min(3ll, b[i] % (n + 2));
		s.insert({f[a[i]] + c[a[i]], a[i]});
		dp[i] = s.begin()->f + 3, p[i] = fp[ff[i] = s.begin()->s];
		if(f[a[i]] > dp[i] - c[a[i]]){
			s.erase({f[a[i]] + c[a[i]], a[i]});
			f[a[i]] = dp[i] - c[a[i]], fp[a[i]] = i;
			s.insert({f[a[i]] + c[a[i]], a[i]});
		} 
	}
	
	for(int i = k; p[i] || ff[i]; i = p[i]) g[p[i]] = ff[i];
	
	for(int i = 0, j = 0; i <= k; i++){
		for(int x = n + 2 * (j != a[i]); b[i] >= x; b[i] -= x){
			v.pb(j), v.pb(a[i]), v.pb(x - 3);
		}
		if(j != a[i] && b[i] <= 3) while(b[i]--) v.pb(a[i]);
		else if(b[i]) v.pb(j), v.pb(a[i]), v.pb(b[i] - 1 - 2 * (j != a[i]));
		if(~g[i]) v.pb(j), v.pb(j = g[i]), v.pb(0);
	}
	
	cout << v.size() << endl;
	cout << v[0];
	for(int i = 1; i < v.size(); i++) cout << " " << v[i];
	cout << endl;

	return 0;
}

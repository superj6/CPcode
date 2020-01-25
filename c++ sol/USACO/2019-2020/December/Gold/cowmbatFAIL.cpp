#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const long long inf = 1000000007;

struct segTree{
	int l, r;
	segTree *left, *right;
	long long val = 0, lazy = 0;
	
	segTree(int a, int b){
		l = a;
		r = b;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	long long amt(){
		return val + lazy;
	}
	
	void push(){
		left->lazy += lazy;
		right->lazy += lazy;
		lazy = 0;
	}
	
	void pull(){
		val = min(left->amt(), right->amt());
	}
	
	void add(int a, int b, long long v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			lazy += v;
			return;
		}
		
		push();
		
		left->add(a, b, v);
		right->add(a, b, v);
		pull();
	}
	
	long long qry(int a, int b){
		if(r < a || b < l) return inf;
		if(a <= l && r <= b) return amt();
		
		push();
		pull();
		
		return min(left->qry(a, b), right->qry(a, b));
	}
};

const int maxn = 100000, maxm = 26;
int n, m, k;
string s;
long long sum[26];
long long dp[maxn];
long long g[maxm][maxm];
segTree *tre[26];

int main(){
	freopen("cowmbat.in", "r", stdin);
	freopen("cowmbat.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k >> s;
	
	for(int i = 0; i < m; i++)
	for(int j = 0; j < m; j++) cin >> g[i][j];
	
	for(int l = 0; l < m; l++)
	for(int i = 0; i < m; i++)
	for(int j = 0; j < m; j++){
		g[i][j] = min(g[i][j], g[i][l] + g[l][j]);
	}
	
	for(int i = 0; i < m; i++) tre[i] = new segTree(0, n - 1);
	
	for(int i = 0; i < n; i++){
		int c = s[i] - 'a';
		dp[i] = inf;
		for(int j = 0; j < m; j++){
			sum[j] += g[c][j];
			tre[j]->add(0, i - 1, g[c][j]);
			dp[i] = min(dp[i], tre[j]->qry(0, i - k));
			if(i >= k - 1) dp[i] = min(dp[i], sum[j]);
		}
		for(int j = 0; j < m; j++){
			tre[j]->add(i, i, dp[i]);
		}
	}
	
	cout << dp[n - 1] << endl;

	return 0;
}
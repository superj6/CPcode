#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int inf = 0x3f3f3f3f;
const int mxn = 301;
int n, m, k;
set<int, greater<int>> dp[mxn * mxn];
int s;

void die(){
	cout << "Impossible" << endl;
	exit(0);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		if(x < k) die();
		s += x;
	}
	s -= n * k;
	
	dp[0].insert(0);
	for(int i = 0; i < m; i++){
		int x, y;
		cin >> x;
		y = x - min(x, n), x -= y;
		for(int it = n * min(k, i); ~it; it--)
		for(int jt : dp[it]){
			int l = min(n * k, it + x);
			dp[l].insert(it + jt + x + y - l);
		}
	}
	
	int ret = inf;
	for(auto it : dp[n * k]){
		if(it >= s) ret = min(ret, it - s);
	}
	
	if(ret == inf) die();
	cout << ret << endl;

	return 0;
}
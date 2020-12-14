#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 401;

struct BIT{
	int bit[mxn];
	
	BIT(){
		memset(bit, 0, sizeof(bit));
	}
	
	void add(int x, int v){
		for(x++; x < mxn; x += x & -x) bit[x] += v;
	}
	
	int qry(int x){
		int ret = 0;
		for(x++; x; x -= x & -x) ret += bit[x];
		return ret;
	}
};

int n;
pi a[mxn];
int dp[mxn][mxn];
vector<int> id;
map<int, int, greater<int>> mp1[mxn], mp2[mxn];
BIT bit;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 1; i <= n; i++){
		cin >> a[i].s >> a[i].f;
		a[i].f += a[i].s;
		mp1[i][-1] = mp2[i][-1] = -1;
		id.push_back(a[i].f), id.push_back(a[i].s);
	}
	a[0] = {-1, -1};
	
	sort(a + 1, a + n + 1);
	sort(id.begin(), id.end());
	id.erase(unique(id.begin(), id.end()), id.end());
	
	mp1[0][-1] = mp2[0][-1] = 0;
	for(int i = 1; i <= n; i++){
		int x = lower_bound(id.begin(), id.end(), a[i].s) - id.begin();
		int b = i - bit.qry(x - 1);
		bit.add(x, 1);
		
		for(int j = i - 1; ~j; j--){
			x = mp1[j].upper_bound(a[i].s)->s;
			if(x >= 0) dp[i][j + b] = max(dp[i][j + b], x);
			x = mp2[j].lower_bound(a[i].s)->s;
			if(x >= 0) dp[i][x + b] = max(dp[i][x + b], j);
		}
		
		//cout << i << endl;
		for(int j = 0; j <= i; j++){
			if(dp[i][j] >= mp1[j].lower_bound(a[i].s)->s){
				auto it = mp1[j].insert({a[i].s, dp[i][j]}).f;
				while(it != mp1[j].begin() && (--it)->s <= dp[i][j]) it = mp1[j].erase(it);
			}
			if(dp[i][j] > mp2[j].begin()->s) mp2[j][a[i].f] = dp[i][j];
			//cout << j << " " << dp[i][j] << endl;
		}
		//cout << endl;
		
	}
	
	int ret = 0;
	for(int i = 0; i <= n; i++) ret = max(ret, min(i, mp2[i].begin()->s));
	
	cout << ret << endl;
	cout << n << endl;
	for(int i = 1; i < n; i++) cout << ret << endl;

	return 0;
}
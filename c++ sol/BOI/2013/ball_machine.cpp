#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100001, k = __lg(mxn) + 1;

struct BIT{
	int bit[mxn];
	
	BIT(){
		memset(bit, 0, sizeof(bit));
	}
	
	void add(int x, int v){
		for(x++; x < mxn; x += x & -x) bit[x] += v;
	}
	
	int qry(){
		int ret = 0, s = 0;
		for(int i = k - 1; ~i; i--){
			ret |= 1 << i;
			if(ret >= mxn || bit[ret] + s < ret) ret ^= 1 << i;
			else s += bit[ret];
		}
		return ret;
	}
};

int n, q;
int mn[mxn], id[mxn], rid[mxn], vis[mxn];
int p[k][mxn];
vector<int> g[mxn];
BIT bit;
int rt, tt;

int dfs(int c){
	mn[c] = c;
	for(int i = 1; i < k; i++) p[i][c] = ~p[i - 1][c] ? p[i - 1][p[i - 1][c]] : -1;
	for(int i : g[c]) mn[c] = min(mn[c], dfs(i));
	return mn[c];
}

void dfs2(int c){
	sort(g[c].begin(), g[c].end(), [&](int x, int y){
		return mn[x] < mn[y];	
	});
	for(int i : g[c]) dfs2(i);
	rid[id[c] = tt++] = c;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	
	for(int i = 0; i < n; i++){
		cin >> p[0][i];
		g[--p[0][i]].push_back(i);
		if(!~p[0][i]) rt = i;
	}
	
	dfs(rt);
	dfs2(rt);
	
	while(q--){
		int t, x;
		cin >> t >> x;
		if(!~-t){
			int c = -1;
			while(x--){
				c = bit.qry();
				vis[rid[c]] = 1;
				bit.add(c, 1);
			}
			cout << rid[c] + 1 << endl;
		}else{
			x--;
			int ret = 0;
			for(int i = k - 1; ~i; i--){
				if(~p[i][x] && vis[p[i][x]]){
					ret |= 1 << i;
					x = p[i][x];
				}
			}
			vis[x] = 0;
			bit.add(id[x], -1);
			cout << ret << endl;
		}
	}

	return 0;
}
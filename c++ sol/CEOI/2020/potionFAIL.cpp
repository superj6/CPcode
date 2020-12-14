#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
//#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

vector<vector<int>> v;
struct segTree{
	int l, r;
	segTree *left = 0, *right = 0;
	int val = -1, chg = 0;
	
	segTree(int a, int b) : l(a), r(b) {}
	
	segTree(segTree *cpy){
		l = cpy->l, r = cpy->r;
		left = cpy->left, right = cpy->right;
		val = cpy->val;
		if(l != r){
			if(left) cpy->left->chg = 1;
			if(right) cpy->right->chg = 1;
		}
	}
	
	void add(int x, int v){
		if(l == r){
			val = v;
			return;
		}
		int mid = (l + r) / 2;
		if(x <= mid){
			if(!left) left = new segTree(l, mid);
			if(left->chg) left = new segTree(left);
			left->add(x, v);
		}else{
			if(!right) right = new segTree(mid + 1, r);
			if(right->chg) right = new segTree(right);
			right->add(x, v);
		}
	}
	
	void qry(){
		if(l == r){
			if(~val) v.back().push_back(val);
			return;
		}
		if(left) left->qry();
		if(right) right->qry();
	}
};

const int mxn = 100000, mxk = 500;
int n, m, k, q;
int a[mxn];
int s[mxn][mxk];
vector<int> b[mxn];
vector<segTree*> tre[mxn];

void cpy(int x, int y){
	b[x].push_back(y);
	tre[x].push_back(new segTree(tre[x].back()));
}

int id(int x, int y){
	int it = find(s[x], s[x] + k, y) - s[x];
	return it < k ? it : -1;
}

void edg(int x, int y){
	int z = 0;
	while(~s[x][z]) z++;
	s[x][z] = y;
	tre[x].back()->add(z, a[y]);
}

void redg(int x, int y){
	int z = id(x, y);
	s[x][z] = -1;
	tre[x].back()->add(z, -1);
}

void qry(int x, int y){
	v.push_back(vector<int>());
	tre[x][upper_bound(b[x].begin(), b[x].end(), y) - b[x].begin() - 1]->qry();
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k >> m >> q;
	
	memset(s, -1, sizeof(s));
	for(int i = 0; i < n; i++){
		cin >> a[i];
		b[i].push_back(0);
		tre[i].push_back(new segTree(0, k - 1));
	}
	
	for(int i = 1; i <= m; i++){
		int u, v;
		cin >> u >> v;
		cpy(u, i), cpy(v, i);
		int x = id(u, v);
		if(!~x) edg(u, v), edg(v, u);
		else redg(u, v), redg(v, u);
	}
	
	for(int i = 0; i < n; i++) b[i].push_back(m + 1);
	
	while(q--){
		int x, y, z;
		cin >> x >> y >> z;
		
		v.clear();
		qry(x, z), qry(y, z);
		for(int i = 0; i < 2; i++) sort(v[i].begin(), v[i].end());
		
		int ret = 1e9;
		for(int i = 0, j = 0; i < v[0].size() && j < v[1].size(); i++){
			while(j < v[1].size() - 1 && v[1][j + 1] < v[0][i]) j++;
			ret = min(ret, abs(v[0][i] - v[1][j]));
			if(j < v[1].size() - 1) ret = min(ret, abs(v[1][j + 1] - v[0][i]));
		}
		
		cout << ret << endl;
	}

	return 0;
}
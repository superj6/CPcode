#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 200001;
int n, q;
int a[mxn], ql[mxn], qr[mxn], f[mxn];
int b[mxn], l[mxn], r[mxn], par[mxn], rnk[mxn];
vector<int> v[mxn];
set<int> s[mxn], ss;

int fnd(int x){ return x == par[x] ? x : par[x] = fnd(par[x]);}

void unf(int x){
	int y = fnd(r[x = fnd(x)] + 1);
	if(rnk[x] < rnk[y]) swap(x, y);
	rnk[x] += rnk[x] == rnk[y];
	par[y] = x, l[x] = min(l[x], l[y]), r[x] = max(r[x], r[y]);
}

void add(int x, int y){
	for(; x <= n; x += x & -x) b[x] += y;
}

int qry(int x){
	int ret = 0;
	for(; x; x -= x & -x) ret += b[x];
	return ret;
}

void upd(int x, int y){
	x = fnd(x);
	if(ss.size() < s[x].size()) swap(ss, s[x]);
	for(int i : s[x]){
		if(ss.count(i)){
			f[i] = qry(qr[i]) - qry(ql[i]) + 1 + (a[ql[i]] != y);
			ss.erase(i);
		}else{
			ss.insert(i);
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		l[i] = r[i] = par[i] = i;
		v[a[i]].push_back(i);
	} 
	
	for(int i = 1; i <= q; i++){
		cin >> ql[i] >> qr[i];
		if(ql[i] > qr[i]) swap(ql[i], qr[i]);
		if(ql[i] == qr[i]) f[i] = 1;
		else s[ql[i]].insert(i), s[qr[i]].insert(i);
	}
	
	for(int i = n; i; i--)
	for(int j = 0, k; j < v[i].size();){
		//update answer
		upd(v[i][j], i);
		if(a[v[i][j] - 1] > i) upd(v[i][j] - 1, i);
		
		for(k = j + 1; k < v[i].size() && a[v[i][k] - 1] >= i && 
		(a[v[i][k] - 1] == i || a[l[fnd(v[i][k] - 1)] - 1] == i); k++){
			if(a[v[i][k] - 1] != i) upd(v[i][k - 1], i);
			upd(v[i][k] - 1, i), upd(v[i][k], i);
		}
		
		if(a[v[i][k - 1] + 1] > i) upd(v[i][k - 1] + 1, i);
		
		//combine intervals
		add(v[i][j], 1);
		swap(ss, s[fnd(v[i][j])]);
		if(a[v[i][j] - 1] > i) unf(v[i][j] - 1);
		
		for(j++; j < k; j++){
			if(a[v[i][j] - 1] != i) unf(v[i][j - 1]);
			unf(v[i][j] - 1);
		}
		
		if(a[v[i][j - 1] + 1] > i) unf(v[i][j - 1]);
	}
	
	for(int i = 1; i <= q; i++) cout << f[i] << endl;
	
	return 0;
}
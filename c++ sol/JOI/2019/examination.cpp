#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define pii pair<pi, pi>

struct segTree{
	int l, r;
	segTree *left = 0, *right = 0;
	long val = 0;
	
	segTree(int a, int b){
		l = a;
		r = b;
	}
	
	void add(int x, int v){
		if(l == r){
			val += v;
			return;
		}
		
		int mid = (l + r) / 2;
		if(x <= mid){
			if(!left) left = new segTree(l, mid);
			left->add(x, v);
		}else{
			if(!right) right = new segTree(mid + 1, r);
			right->add(x, v);
		}
		
		val = (left ? left->val : 0) + (right ? right->val : 0);
	}
	
	long qry(int a, int b){
		if(r < a || b < l) return 0;
		if(a <= l && r <= b) return val;
		
		return (left ? left->qry(a, b) : 0) + (right ? right->qry(a, b) : 0);
	}
};

const int maxn = 300001;

struct BIT{
	segTree *bit[maxn];
	
	BIT(){
		memset(bit, 0, sizeof(bit));
	}
	
	void add(int x, int y, int v){
		for(x++; x < maxn; x += x & -x){
			if(!bit[x]) bit[x] = new segTree(0, maxn);
			bit[x]->add(y, v);
		}
	}
	
	int qry(int x, int y, int Y){
		int ret = 0;
		for(x++; x; x -= x & -x) if(bit[x]) ret += bit[x]->qry(y, Y);
		return ret;
	}
	
	int qry(int x, int X, int y, int Y){
		return qry(X, y, Y) - qry(x - 1, y, Y);
	}
};

int n, q;
pi a[maxn];
pii qry[maxn];
vector<int> v;
BIT bit;
int ans[maxn];

int id(int x){
	return lower_bound(v.begin(), v.end(), x, greater<int>()) - v.begin();
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	
	for(int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
	for(int i = 0; i < q; i++){
		cin >> qry[i].first.first >> qry[i].second.first >> qry[i].second.second;
		qry[i].first.second = i;
		v.push_back(qry[i].first.first);
		v.push_back(qry[i].second.first);
		v.push_back(qry[i].second.second);
	} 
	
	sort(a, a + n, greater<pi>());
	sort(qry, qry + q, greater<pii>());
	sort(v.begin(), v.end(), greater<int>());
	v.erase(unique(v.begin(), v.end()), v.end());
	
	for(int i = 0, j = 0; i < q; i++){
		for(; j < n && a[j].first >= qry[i].first.first; j++) bit.add(id(a[j].second), id(a[j].first + a[j].second), 1);
		ans[qry[i].first.second] = bit.qry(id(qry[i].second.first), 0, id(qry[i].second.second));
	}
	
	for(int i = 0; i < q; i++) cout << ans[i] << endl;

	return 0;
}
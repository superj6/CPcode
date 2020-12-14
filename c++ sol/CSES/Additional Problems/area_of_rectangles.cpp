#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

struct segTree{
	int l, r;
	segTree *left, *right;
	int val = 0, val2 = 0;
 
	segTree(int a, int b){
		l = a;
		r = b;
 
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
 
	void add(int a, int b, int v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			val2 += v;
			val = val2 ? r - l + 1 : l != r ? left->val + right->val : 0;
			return;
		}
 
		left->add(a, b, v);
		right->add(a, b, v);
		val = val2 ? r - l + 1 : left->val + right->val;
	}
 
	int qry(int a, int b){
		if(r < a || b < l) return 0;
		if(val2) return min(r, b) - max(l, a) + 1;
		if(a <= l && r <= b) return val;
		
		return left->qry(a, b) + right->qry(a, b);
	}
};

const int maxn = 2000001;
int n;
vector<pi> a[maxn];
segTree tre(0, maxn);

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		int x, y, X, Y;
		cin >> x >> y >> X >> Y;
		x += maxn / 2, y += maxn / 2 + 1, X += maxn / 2, Y += maxn / 2;
		a[x].push_back({y, Y}), a[X].push_back({-y, -Y});
	}
	
	long long ret = 0;
	for(int i = 0, s = 0; i < maxn; i++){
		for(pi p : a[i]) tre.add(abs(p.f), abs(p.s), p.f / abs(p.f));
		if(!a[i].empty()) s = tre.qry(0, maxn);
		ret += s;
	}
	
	cout << ret << endl;

	return 0;
}
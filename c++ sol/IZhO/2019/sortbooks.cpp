#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
 
struct segTree{
	int l, r;
	segTree *left, *right;
	int val = 0;
	
	segTree(int a, int b){
		l = a;
		r = b;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	void add(int x, int v){
		if(x < l || r < x) return;
		if(l == r){
			val = max(val, v);
			return;
		}
		
		left->add(x, v);
		right->add(x, v);
		val = max(left->val, right->val);
	}
	
	int qry(int a, int b){
		if(r < a || b < l) return 0;
		if(a <= l && r <= b) return val;
		
		return max(left->qry(a, b), right->qry(a, b));
	}
};
 
const int maxn = 1000000;
int n, q;
int a[maxn], l[maxn], r[maxn], s[maxn];
vector<int> p[maxn], qry[maxn];
stack<int> stk;
int ans[maxn];
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		while(!stk.empty() && a[stk.top()] <= a[i]) stk.pop();
		if(!stk.empty()) p[stk.top()].push_back(i);
		stk.push(i);
	}
	
	for(int i = 0; i < q; i++){
		cin >> l[i] >> r[i] >> s[i];
		l[i]--, r[i]--;
		qry[l[i]].push_back(i);
	}
	
	segTree tre(0, n);
	for(int i = n - 1; i >= 0; i--){
		for(int j : p[i]) tre.add(j, a[i] + a[j]);
		for(int j : qry[i]) ans[j] = tre.qry(i, r[j]) <= s[j];
	}
	
	for(int i = 0; i < q; i++) cout << ans[i] << endl;
 
	return 0;
}
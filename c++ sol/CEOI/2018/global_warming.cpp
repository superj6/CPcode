#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

struct segTree{
	int l, r;
	segTree *left, *right;
	int val;
	
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
			val = v;
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

const int maxn = 200000;
int n, x;
int a[maxn], b[maxn], dp[maxn];
vector<int> p, v;
multiset<int, greater<int>> val[maxn];
segTree tre(0, maxn);

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> x;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		b[i] = a[i];
		int j = lower_bound(p.begin(), p.end(), a[i]) - p.begin();
		if(j < p.size()) p[j] = a[i];
		else p.push_back(a[i]);
		dp[i] = j + 1;
		val[i].insert(0);
	}
	
	sort(b, b + n);
	for(int i = 0; i < n; i++) if(i == n - 1 || b[i] != b[i + 1]) v.push_back(b[i]);
	
	for(int i = 0; i < n; i++){
		int j = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
		val[j].insert(dp[i]);
		tre.add(j, *val[j].begin());
	}
	
	p.clear();
	int ret = 0;
	for(int i = n - 1; i >= 0; i--){
		int j = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
		val[j].erase(val[j].find(dp[i]));
		tre.add(j, *val[j].begin());
		
		j = lower_bound(p.begin(), p.end(), -a[i]) - p.begin();
		if(j < p.size()) p[j] = -a[i];
		else p.push_back(-a[i]);
		
		ret = max(ret, j + 1 + tre.qry(0, lower_bound(v.begin(), v.end(), a[i] + x) - v.begin() - 1));
	}
	
	cout << ret << endl;

	return 0;
}
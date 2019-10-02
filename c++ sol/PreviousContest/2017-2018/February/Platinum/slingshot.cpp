/*
This is code of SuperJ6 for Codeforces.
Don't copy my code during f*kin' contests.

2.71828182845904523536
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <math.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const long long inf = 100000000000007;
struct segTree{
	int l, r;
	segTree *left, *right;
	long long val1 = inf, val2 = inf;
	
	segTree(int a, int b){
		l = a;
		r = b;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	void add(int x, long long v1, long long v2){
		if(x < l || r < x) return;
		if(l == r){
			val1 = min(val1, v1);
			val2 = min(val2, v2);
			return;
		}
		
		left->add(x, v1, v2);
		right->add(x, v1, v2);
		val1 = min(left->val1, right->val1);
		val2 = min(left->val2, right->val2);
	}
	
	long long qry1(int a, int b){
		if(r < a || b < l) return inf;
		if(a <= l && r <= b) return val1;
		
		return min(left->qry1(a, b), right->qry1(a, b));
	}
	
	long long qry2(int a, int b){
		if(r < a || b < l) return inf;
		if(a <= l && r <= b) return val2;
		
		return min(left->qry2(a, b), right->qry2(a, b));
	}
};

struct rng{
	long long x, y, t;
	
	friend bool operator <(rng a, rng b){
		return	a.x < b.x;
	}
};

const int maxn = 200000;
int n, m;
rng r[maxn];
long long ans[maxn];
set<long long> st;
vector<long long> p;

int main(){
	freopen("slingshot.in", "r", stdin);
	freopen("slingshot.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		cin >> r[i].x >> r[i].y >> r[i].t;
		st.insert(r[i].y);
	}
	for(int i = n; i < n + m; i++){
		cin >> r[i].x >> r[i].y;
		r[i].t = n - i - 1;
		ans[i - n] = abs(r[i].x - r[i].y);
		st.insert(r[i].y);
	}
	
	sort(r, r + n + m);
	
	for(auto it = st.begin(); it != st.end(); it++) p.push_back(*it);
	
	
	for(int k = 0; k < 2; k++){
		segTree tre(0, p.size() - 1);
		for(int i = 0; i < n + m; i++){
			int f = lower_bound(p.begin(), p.end(), r[i].y) - p.begin();
			if(r[i].t < 0){
				ans[-r[i].t - 1] = min(ans[-r[i].t - 1], tre.qry1(0, f) + r[i].x + r[i].y);
				ans[-r[i].t - 1] = min(ans[-r[i].t - 1], tre.qry2(f, p.size() - 1) + r[i].x - r[i].y);
			}else{
				tre.add(f, r[i].t - r[i].x - r[i].y, r[i].t + r[i].y - r[i].x);
			}
			r[i].x *= -1;
		}
		reverse(r, r + n + m);
	}
	
	for(int i = 0; i < m; i++) cout << ans[i] << endl;

	return 0;
}
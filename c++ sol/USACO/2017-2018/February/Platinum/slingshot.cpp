/*
	For this problem, it is best to start thinking about different cases of slingshot endpoint orientation relative to the
the current transport endpoints. Call sx and sy the slingshot endpoints, and x and y the transport query endpoints. There are only
for different relative orientations sx and sy can have with x and y: sx < x and sy < y, sx < x and sy > y, sx > x and sy < y,
sx > x and sy > y. Consider the first case, and the other cases will follow similar logic. If you sorted the points by there first
end point and iterated through them, you would make a slingshot available to be used when you passed it in the sweep. For a query,
to find the best slingshot for that case, it would be helpful to be able to find the distance when using an available slingshot
such that the endpoint is before the query endpoint. How you could do this is to keep a segment tree with the right endpoints of
slingshots currently available, and hold there value of t - sx - sy. This is because when sx < x and sy < y, the value of the
best path using a slingshot in that orientation is (x - sx) + (y - sy) + t. which can be rearranged as (x + y) + (t - sx - sy).
This means when considering one orientation by itself, the value of the best slingshot is completely independent of the queries
x and y value, so you can just query the segtree for the lowest value of t - sx - sy where the active endpoint is before the endpoint
you are querying. You can similarly modify the value and use the same technique with the other orientations and do a sweep through
keeping active endpoints in a segment tree. Also to write less code, you can only consider the first two orientations then reverse
the ordering of the points and run the same code. Lastly, make sure to consider the case where you don't use a slingshot. The time
complexity of this is O(nlogn) from the segment tree queries.
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

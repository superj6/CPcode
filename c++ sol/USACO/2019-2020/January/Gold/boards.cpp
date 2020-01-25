#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define pii pair<pi, int>
#define piii pair<pi, pi>
#define x first
#define y second

const int inf = 1000000007;

struct segTree{
	int l, r;
	segTree *left, *right;
	int val = inf;
	
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
			val = min(val, v);
			return;
		}
		
		left->add(x, v);
		right->add(x, v);
		val = min(left->val, right->val);
	}
	
	int qry(int a, int b){
		if(r < a || b < l) return inf;
		if(a <= l && r <= b) return val;
		
		return min(left->qry(a, b), right->qry(a, b));
	}
};

const int maxn = 100001;
int k, n;
piii a[maxn];
vector<int> id;
priority_queue<pii, vector<pii>, greater<pii>> pq;
segTree tre(0, 2 * maxn);

int idx(int x){
	return lower_bound(id.begin(), id.end(), x) - id.begin();
}

int main(){
	freopen("boards.in", "r", stdin);
	freopen("boards.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> k >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i].x.x >> a[i].x.y >> a[i].y.x >> a[i].y.y;
		id.push_back(a[i].x.y);
		id.push_back(a[i].y.y);
	}
	a[n++] = {{k, k}, {k, k}}; 
	id.push_back(0);
	id.push_back(k);
	
	sort(a, a + n);
	sort(id.begin(), id.end());
	id.erase(unique(id.begin(), id.end()), id.end());
	tre.add(0, 0);
	
	for(int i = 0; i < n; i++){
		while(!pq.empty() && pq.top().x.x <= a[i].x.x){
			tre.add(pq.top().x.y, pq.top().y);
			pq.pop();
		} 
		int val = tre.qry(0, idx(a[i].x.y)) + a[i].x.x + a[i].x.y;
		pq.push({{a[i].y.x, idx(a[i].y.y)}, val - a[i].y.x - a[i].y.y});
		if(i == n - 1) cout << val << endl;
	}

	return 0;
}
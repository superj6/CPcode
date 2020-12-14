#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, int>
#define f first
#define s second

const int inf = 2000000011;
const int maxn = 100000;
int n, m;
int id[maxn], w[maxn], x[maxn], y[maxn], z[maxn];
ll d[maxn];
priority_queue<pi, vector<pi>, greater<pi>> pq;

struct segTree{
	int l, r;
	segTree *left, *right;
	int val;
	
	segTree(int a, int b){
		l = a, r = b;
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
			val = min(left->val, right->val);
		}else{
			int it = id[l];
			val = x[it] + w[it];
		}
	}
	
	void qry(int a, int b, ll v){
		int it = id[l];
		if(a < x[it] - w[it] || b < val) return;
		if(l == r){
			if(d[it] == (ll)inf * inf){
				d[it] = v + z[it];
				pq.push({d[it], it});
			}
			val = inf;
			return;
		}
		left->qry(a, b, v);
		right->qry(a, b, v);
		val = min(left->val, right->val);
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> m >> n;
	
	for(int i = 0; i < n; i++){
		cin >> w[i] >> x[i] >> y[i] >> z[i];
		id[i] = i;
		if(x[i] == 1){
			d[i] = z[i];
			pq.push({d[i], i});
		}else{
			d[i] = (ll)inf * inf;
		}
	}
	
	sort(id, id + n, [&](int i, int j){
		return x[i] - w[i] == x[j] - w[j] ? x[i] + w[i] < x[j] + w[j] : x[i] - w[i] < x[j] - w[j];	
	});
	
	segTree tre(0, n - 1);
	while(!pq.empty()){
		int it = pq.top().s;
		pq.pop();
		tre.qry(y[it] - w[it] + 1, y[it] + w[it] + 1, d[it]);
	}
	
	ll ret = (ll)inf * inf;
	for(int i = 0; i < n; i++){
		if(y[i] == m) ret = min(ret, d[i]);
	}
	
	cout << (ret == (ll)inf * inf ? -1 : ret) << endl;

	return 0;
}
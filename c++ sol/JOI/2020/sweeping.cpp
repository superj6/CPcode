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
	int val = -1;
 
	segTree(int a, int b){
		l = a;
		r = b;
 
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
 
	void push(){
		left->val = max(left->val, val);
		right->val = max(right->val, val);
		val = -1;
	}
	
	void set(int x, int v){
		if(l == r){
			val = v;
			return;
		}
 
		push();
 
		if(x <= (l + r) / 2) left->set(x, v);
		else right->set(x, v);
	}
 
	void add(int a, int b, int v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			val = max(val, v);
			return;
		}
 
		push();
 
		left->add(a, b, v);
		right->add(a, b, v);
	}
 
	long qry(int x){
		if(l == r) return val;
 
		push();
 
		return x <= (l + r) / 2 ? left->qry(x) : right->qry(x);
	}
};

const int maxm = 1500000;
int n, m, q;
int qry[maxm][3];
vector<int> a;
vector<pi> id;
segTree tre(0, maxm);

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> q;
	
	for(int i = 0; i < m; i++){
		qry[i][0] = 4;
		cin >> qry[i][2] >> qry[i][1];
		id.push_back({qry[i][1], a.size()});
		a.push_back(-1);
	}
	
	for(int i = m; i < m + q; i++){
		cin >> qry[i][0];
		if(qry[i][0] == 4){
			cin >> qry[i][2] >> qry[i][1];
			id.push_back({qry[i][1], a.size()});
			a.push_back(-1);
		}else{
			cin >> qry[i][1];
			if(qry[i][0] == 1) qry[i][1]--;
		}
	}
	
	sort(id.begin(), id.end());
	for(int i = 0, j = 0; i < id.size(); i++) a[id[i].s] = i;
	
	for(int i = 0, j = 0; i < m + q; i++){
		if(qry[i][0] == 1){
			cout << tre.qry(a[qry[i][1]]) << " " << id[a[qry[i][1]]].f << endl;
		}else if(qry[i][0] == 2){
			int it = lower_bound(id.begin(), id.end(), (pi){qry[i][1] + 1, 0}) - id.begin() - 1;
			tre.add(0, it, n - qry[i][1]);
		}else{
			tre.set(a[j++], qry[i][2]);
		}
	}

	return 0;
}
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int k = 1 << 4;

struct segTree{
	int l, r;
	segTree *left, *right;
	int lzy = 0;
	int dpl[k] = {0}, dpm[k] = {0}, dpr[k] = {0};
 
	segTree(int a, int b){
		l = a, r = b;
		dpl[0] = dpm[0] = dpr[0] = r - l + 1;
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	void upd(int x){
		lzy += x;
		for(int i = (x > 0) * (k - 1); ~i && i < k; i += 1 - 2 * (x > 0)){
			if(i - x < 0 || i - x >= k) dpl[i] = dpm[i] = dpr[i] = 0;
			else dpl[i] = dpl[i - x], dpm[i] = dpm[i - x], dpr[i] = dpr[i - x];
		}
	}
 
	void push(){
		left->upd(lzy), right->upd(lzy);
		lzy = 0;
	}
 
	void pull(){
		int mid = (l + r) / 2;
		for(int i = 0; i < k; i++){
			dpl[i] = left->dpl[i] + (left->dpl[i] == (mid - l + 1)) * right->dpl[i];
			dpr[i] = right->dpr[i] + (right->dpr[i] == (r - mid)) * left->dpr[i];
			dpm[i] = max({left->dpm[i], right->dpm[i], left->dpr[i] + right->dpl[i]});
		}
	}
 
	void add(int a, int b, int v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			upd(v);
			return;
		}
		push();
		left->add(a, b, v), right->add(a, b, v);
		pull();
	}
};

const int maxn = 100000;
int n, q;
segTree tre(0, maxn);

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	tre.add(n + 1, maxn, 15);
	
	for(int i = 0; i < 4; i++){
		int m;
		cin >> m;
		while(m--){
			int x, y;
			cin >> x >> y;
			tre.add(x, y, (1 << i));
		}
	}
	
	cin >> q;
	
	while(q--){
		int id, t, x, y;
		cin >> id >> t >> x >> y;
		id--;
		tre.add(x, y, (1 - 2 * t) * (1 << id));
		cout << tre.dpm[0] << endl;
	}

	return 0;
}
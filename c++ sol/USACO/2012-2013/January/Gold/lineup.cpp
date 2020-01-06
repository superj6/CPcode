#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
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
			val += v;
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

const int maxn = 100000;
int n, k;
int a[maxn];
unordered_map<int, int> mp;
int m;

int main(){
	freopen("lineup.in", "r", stdin);
	freopen("lineup.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		if(mp.find(a[i]) == mp.end()) mp[a[i]] = m++;
		a[i] = mp[a[i]];
	}
	
	int ret = 0;
	segTree tre(0, m);
	for(int i = 0, j = 0, c = 0; i < n; i++){
		if(tre.qry(a[i], a[i]) == 0) c++;
		tre.add(a[i], 1);
		while(c > k + 1){
			if(tre.qry(a[j], a[j]) == 1) c--;
			tre.add(a[j], -1);
			j++;
		}
		ret = max(ret, tre.qry(0, m));
	}
	
	cout << ret << endl;

	return 0;
}
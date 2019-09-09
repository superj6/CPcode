#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

struct segTree{
	int l, r;
	segTree *left, *right;
	int maxv = 0, lazy = 0;
	
	segTree(int a, int b){
		l = a;
		r = b;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}

	int qry(){
		return maxv + lazy;
	}
	
	void add(int a, int b, int x){
		if(l > b || r < a) return;
		if(l >= a && r <= b){
			lazy += x;
			return;
		}
		
		left->lazy += lazy;
		right->lazy += lazy;
		lazy = 0;
		
		left->add(a, b, x);
		right->add(a, b, x);
		maxv = max(left->qry(), right->qry());
	}
};

bool used[2000001];
vector<int> p;

int main(){
	freopen("lazy.in", "r", stdin);
	freopen("lazy.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	pair<int, pair<int, int>> a[2 * n];
	
	for(int i = 0; i < n; i++){
		int g, x, y;
		cin >> g >> x >> y;
		
		x -= y;
		y += x + y;
		
		if(!used[y]){
			p.push_back(y);
			used[y] = 1;
		}
		
		a[i].first = x - k;
		a[i + n].first = x + k + 1;
		
		a[i].second.first = a[i + n].second.first = y;
		
		a[i].second.second = g;
		a[i + n].second.second = -g;
	}
	
	n *= 2;
	sort(a, a + n);
	sort(p.begin(), p.end());
	segTree tre = segTree(1, p.size());
	
	int maxv = 0;
	for(int i = 0; i < n; i++){
		int st = lower_bound(p.begin(), p.end(), a[i].second.first - 2 * k) - p.begin() + 1;
		int en = upper_bound(p.begin(), p.end(), a[i].second.first + 2 * k) - p.begin();
		tre.add(st, en, a[i].second.second);
		
		if(i == n - 1 || a[i].first != a[i + 1].first){
			maxv = max(maxv, tre.qry());
		}
	}
	
	cout << maxv << endl;

	return 0;
}
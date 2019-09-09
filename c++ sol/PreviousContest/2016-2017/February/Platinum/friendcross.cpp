#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

struct segTree{
	int l, r;
	segTree *left = NULL, *right = NULL;
	int sum = 0;
	
	segTree(int a, int b){
		l = a;
		r = b;
	}
	
	void add(int t, int x){
		if(l == r){
			sum += x;
			return;
		}
		
		int mid = l + (r - l) / 2;
		
		if(t <= mid){
			if(!left) left = new segTree(l, mid);
			left->add(t, x);
		}else{
			if(!right) right = new segTree(mid + 1, r);
			right->add(t, x);
		}
		
		sum = (left ? left->sum : 0) + (right ? right->sum : 0);
	}
	
	int qry(int a, int b){
		if(l > b || r < a) return 0;
		if(l >= a && r <= b) return sum;
		
		return (left ? left->qry(a, b) : 0) + (right ? right->qry(a, b) : 0);
	}
};

const int maxn = 100010;
segTree *bit[maxn];

void add(int i, int t, int x){
	i++;
	for(; i < maxn; i += i & (-i)) bit[i]->add(t, x);
}

int qry(int i, int a, int b){
	i++;
	int ret = 0;
	for(; i > 0; i -= i & (-i)) ret += bit[i]->qry(a, b);
	return ret;
}

int main(){
	freopen("friendcross.in", "r", stdin);
	freopen("friendcross.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	int a[n], b[n], p[n];
	for(int i = 1; i <= maxn; i++) bit[i] = new segTree(0, n);
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		x--;
		p[x] = i;
		b[i] = x;
	}
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		x--;
		
		a[p[x]] = i;
		add(i, x, 1);
	}
	
	int tot = 0;
	
	for(int i = 0; i < n; i++){
		tot += qry(a[i], 0, n) - qry(a[i], b[i] - k, b[i] + k);
		add(a[i], b[i], -1);
	}
	
	cout << tot << endl;

	return 0;
}
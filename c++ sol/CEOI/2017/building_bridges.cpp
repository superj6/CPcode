#include <iostream>
#include <cstdio>
#include <algorithm>
#include <complex>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

#define pt complex<long long>
#define x real
#define y imag

const long long inf = 1000000000000007;

struct liTree{
	int l, r;
	liTree *left, *right;
	pt line = {0, inf};
	
	liTree(int a, int b){
		l = a;
		r = b;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new liTree(l, mid);
			right = new liTree(mid + 1, r);
		}
	}
	
	long long dot(pt a, pt b){
		return (conj(a) * b).x();
	}
	
	long long f(pt a, int x){
		return dot(a, {x, 1});
	}
	
	void add(pt nw){
		int m = (l + r) / 2;
		bool lef = f(nw, l) < f(line, l);
		bool mid = f(nw, m) < f(line, m);
		if(mid){
			swap(line, nw);
		}
		if(l == r) return;
		if(lef != mid) left->add(nw);
		else right->add(nw);
	}
	
	void add(long long m, long long b){
		add({m, b});
	}
	
	long long qry(int x){
		if(x < l || r < x) return inf;
		if(l == r) return f(line, x);
		return min(f(line, x), min(left->qry(x), right->qry(x)));
	}
};

const int maxn = 1000000;
int n;
long long h[maxn], w[maxn];
liTree tre(0, maxn);

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> h[i];
	for(int i = 0; i < n; i++){
		cin >> w[i];
		if(i) w[i] += w[i - 1];
	}
	
	long long ret = 0;
	tre.add(-2 * h[0], h[0] * h[0] - w[0]);
	for(int i = 1; i < n; i++){
		ret = tre.qry(h[i]) + h[i] * h[i] + w[i - 1];
		tre.add(-2 * h[i], ret + h[i] * h[i] - w[i]);
	}
	
	cout << ret << endl;

	return 0;
}
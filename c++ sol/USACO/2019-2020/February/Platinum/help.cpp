#include <iostream>
#include <cstdio>
#include <algorithm>
#include <array>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007, maxk = 11;
typedef array<long long, maxk> T;

T operator+(T a, T b){
	for(int i = 0; i < maxk; i++){
		a[i] += b[i];
		a[i] %= mod;
	} 
	return a;
}

T operator*(T a, long long b){
	for(int i = 0; i < maxk; i++){
		a[i] *= b;
		a[i] %= mod;
	}
	return a;
}

struct segTree{
	int l, r;
	segTree *left, *right;
	T val{};
	long long lzy = 1;
	
	segTree(int a, int b){
		l = a;
		r = b;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	T amt(){
		return val * lzy;
	}
	
	void push(){
		left->lzy *= lzy;
		left->lzy %= mod;
		right->lzy *= lzy;
		right->lzy %= mod;
		val = val * lzy;
		lzy = 1;
	}
	
	void pull(){
		val = left->amt() + right->amt();
	}
	
	void add(int x, T v){
		if(x < l || r < x) return;
		if(l == r){
			val = val * lzy;
			lzy = 1;
			val = val + v;
			return;
		}
		
		push();
		left->add(x, v);
		right->add(x, v);
		pull();
	}
	
	void mult(int a, int b, int v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			lzy *= v;
			lzy %= mod;
			return;
		}
		
		push();
		left->mult(a, b, v);
		right->mult(a, b, v);
		pull();
	}
	
	T qry(int a, int b){
		if(b < l || r < a) return T();
		if(a <= l && r <= b) return amt();
		
		push();
		
		return left->qry(a, b) + right->qry(a, b);
	}
};

const int maxn = 100000;
int n, k;
pi a[maxn];
int id[2 * maxn + 1];
long long f[maxk][maxk];
segTree tre(0, maxn);

int main(){
	freopen("help.in", "r", stdin);
	freopen("help.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++){ 
		cin >> a[i].f >> a[i].s;
		id[a[i].s]++;
	}
	for(int i = 1; i <= 2 * n; i++) id[i] += id[i - 1];
	
	sort(a, a + n);
	
	for(int i = 0; i <= k; i++){
		f[i][0] = 1;
		for(int j = 1; j <= i; j++) f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
	}
	T s{};
	s[0] = 1;
	tre.add(0, s);
	
	for(int i = 0; i < n; i++){
		T x = tre.qry(id[a[i].f] + 1, id[a[i].s]);
		T y = tre.qry(0, id[a[i].f]);
		for(int j = 0; j <= k; j++)
		for(int l = 0; l <= j; l++){
			x[j] += f[j][l] * y[l] % mod;
			x[j] %= mod;
		}
		tre.mult(id[a[i].s], n, 2);
		tre.add(id[a[i].s], x);
	}
	
	cout << tre.qry(1, n)[k] << endl;

	return 0;
}
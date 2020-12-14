/*
	To use 2 * n switches, create a full binary tree for the next power of two larger than or equal to n, and have every trigger
lead to the tree and the tree of switches will go to the next trigger. To cut down on switches, when creating the tree, you can cut off
all portions of the tree that the range of leaf node indices is completely outside the range outside of the bounds of n. I don't have
definite proof, but you can think of it like segment tree that it will chop off powers of two resulting in almost no more than lgn extra
switches. Also, when cut off, the switch states will still work out because it will be used a multiple of two times for every time the
ball comes back to a cut off portion of the switch.
*/

//#include "doll.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define vi vector<int>

const int mxn = 1 << 19;
int n, k, t;
bool b[mxn];
vi f, u(mxn), v(mxn);

int bld(int l, int r){
	if(l == r) return 0;
	if(r < k - n) return -1;
	int it = t++, mid = (l + r) / 2;
	u[it] = bld(l, mid), v[it] = bld(mid + 1, r);
	return -it - 1;
}

void add(int x, int y){
	x = -x - 1;
	int &z = b[x] ? v[x] : u[x];
	b[x] ^= 1;
	if(!z) z = y;
	else add(z, y);
}

void answer(vi f, vi u, vi v){
	for(int i = 0; i < f.size(); i++){
		cout << i << ": " << f[i] << endl;
	}
	for(int i = 0; i < u.size(); i++){
		cout << (-i - 1) << ": " << u[i] << " " << v[i] << endl;
	} 
}

void create_circuit(int m, vi a){
	n = a.size(), k = 1 << (__lg(n - 1) + 1);
	bld(0, k - 1);
	
	for(int i = 1; i < n; i++) add(-1, a[i]);
	if(n & 1) add(-1, -1);
	add(-1, 0);
	
	f.assign(m + 1, -1), u.resize(t), v.resize(t);
	f[0] = a[0];
	
	answer(f, u, v);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	vi a(n);
	for(int i = 0; i < n; i++) cin >> a[i];
	
	create_circuit(m, a);

	return 0;
}

/*
	We can go through the array, keeping a stack of min an max elements encountered so far. Now, we need a segment
tree which can perform range updates and query the top node such each position holds three values, and you want to add
or set one of the values on a range, and you keep the sum of products of the three values, as each position in the
segment tree will correspond to the current left endpoint of the array in which we want to add the result.
	To create such a segment tree, we can just hold all subsets of values and their sum of products. Then to
update a range, you mark a lazy value and every subset which includes the current value you are updating you can just
take the subset that includes that value and multiply by the updated one.
	Now we just add all of the current prefix by one to update the length, and update for the other values based
the new end range from the stack for how far the current element will be min or max. It is O(nlgn), and the general
segtree with k values in each position would be O(2^k * nlgn). It was hard for me to get in time limit and memory
however, so I had to code it in the AIcash segtree style, unlike my normal segtree style.
*/

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

const int mod = 1000000000;
const int mxn = 1 << 19, k = 3;
int n, m;
int a[mxn];
int t[mxn << 1][1 << k], lz[mxn][1 << k];
vector<int> s1, s2;

int ad(int x, int y){ return x + y >= mod ? x + y - mod : x + y;}

void upd(int x, int y, int v){
	if(x < (1 << m)) lz[x][y] = ad(!y * lz[x][y], v);
	for(int i = 0; i < (1 << k); i++){
		if((i >> y) & 1) t[x][i] = ad(!y * t[x][i], (ll)v * t[x][i ^ (1 << y)] % mod);
	}
}

void pul(int x){
	for(int i = m; i; i--){
		int y = x >> i;
		for(int j = 0; j < k; j++){
			if(lz[y][j]) upd(y << 1, j, lz[y][j]), upd(y << 1 | 1, j, lz[y][j]);
			lz[y][j] = 0;
		}
	}
	
	for(x >>= 1; x; x >>= 1)
	for(int i = 0; i < (1 << k); i++){
		t[x][i] = ad(t[x << 1][i], t[x << 1 | 1][i]);
	}
}

void add(int l, int r, int x, int v){
	l += (1 << m), r += (1 << m);
	for(int i = l, j = r + 1; i < j; i >>= 1, j >>= 1){
		if(i & 1) upd(i++, x, v);
		if(j & 1) upd(--j, x, v);
	}
	pul(l), pul(r);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	m = __lg(n) + 1;
	
	for(int i = 0; i < (1 << m); i++) t[(1 << m) + i][0] = 1;
	for(int i = (1 << m) - 1; i; i--) t[i][0] = ad(t[i << 1][0], t[i << 1 | 1][0]);
	
	ll ret = 0;
	s1.push_back(0), s2.push_back(0);
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		add(1, i, 0, 1);
		
		while(s1.back() && a[i] >= a[s1.back()]) s1.pop_back();
		add(s1.back() + 1, i, 1, a[i]);
		s1.push_back(i);
		
		while(s2.back() && a[i] <= a[s2.back()]) s2.pop_back();
		add(s2.back() + 1, i, 2, a[i]);
		s2.push_back(i);
		
		ret = ad(ret, t[1][(1 << k) - 1]);
	}
	
	cout << ret << endl;
	
	return 0;
}
/*
	Realize you can reorder elements in any way that are all in same connected component, where edges are valid
swap pairs. This means you can use union find to keep track of added edges, while keeping a hash of the elements 
within the set and a map with counts of how many elements are within components of each hash value. Also, for each
hash you need to subtract the elements in their sorted order. Now, to answer type 3, the answer is yes if and only if
the count of elements in components with hashes of value 0 is equal to n, since being in a hash with value 0 means
every element can be pair with a position in its connected component where it goes in sorted order. To answer type 4,
you just keep track during all operations of the size of a component multiplied the number of elements in components
with the negative hash value, since adding an edge would combine those components making the hash 0.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
using namespace std;
#define endl '\n'
#define ll long long
#define ull unsigned ll
#define pi pair<int, int>
#define f first
#define s second

const ull ha = 1000696969;
const int mxn = 1000001;
ll n, k, q;
int a[mxn], b[mxn], sz[mxn], par[mxn], rnk[mxn];
ull h[mxn], p[mxn];
unordered_map<ull, int> f;

int fnd(int x){ return x == par[x] ? x : par[x] = fnd(par[x]);}

void add(int x, int y){
	if(!~y) k -= !!h[x] * sz[x] * f[-h[x]];
	f[h[x]] += y * sz[x];
	if(~y) k += !!h[x] * sz[x] * f[-h[x]];
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	
	p[0] = 1;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		b[i] = a[i], sz[i] = 1, par[i] = i;
		p[i] = ha * p[i - 1];
	} 
	
	sort(b + 1, b + n+ 1);
	
	for(int i = 1; i <= n; i++) h[i] = p[a[i]] - p[b[i]], add(i, 1);
	
	while(q--){
		int t;
		cin >> t;
		if(!~-t){
			int x, y, xx, yy;
			cin >> x >> y;
			xx = fnd(x), yy = fnd(y);
			add(xx, -1), add(yy, -1);
			h[xx] -= p[a[x]], h[yy] -= p[a[y]];
			swap(a[x], a[y]);
			h[xx] += p[a[x]], h[yy] += p[a[y]];
			add(xx, 1), add(yy, 1);
		}else if(t == 2){
			int x, y;
			cin >> x >> y;
			x = fnd(x), y = fnd(y);
			if(x != y){
				if(rnk[x] < rnk[y]) swap(x, y);
				rnk[x] += rnk[x] == rnk[y];
				add(x, -1), add(y, -1);
				par[y] = x, h[x] += h[y], sz[x] += sz[y];
				add(x, 1);
			}
		}else if(t == 3){
			cout << (f[0] == n ? "DA" : "NE") << endl;
		}else{
			cout << k << endl;
		}
	}
	
	return 0;
}
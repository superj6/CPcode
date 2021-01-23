/*
	Realize if x can win, and y can beat x, than y can win. This means there is a group such that all can beat 
eachother. Similarly, if x can win, and the max position of y is less than the max position of x, that means there
y can definitely beat x therefore it can win. That means the group of winning values is a consecutive group based on
there max position in any court. Finally, realize if the number of values with max position at most x is less than x,
that means there is at least one person that has one of their positions less than x but max position greater than x,
so you still need to extend how far the winning consecutive group's max position go's. This means you can create a 
segment tree that holds the prefix sum of the values at each position which are 1 minus the number of values with this
max position. Than using hall's, the group of winners must be the first consecutive group such that the number of people
with max position at most x is equal to x, so you can just walk in the segment tree to find the first prefix sum equal
to 0. Now when you swap to people's placements, you just recalculate each of their max position and update the segment
tree. And to query, you just see if there max position is within the winning range.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100000, k = 3;
int n, q;
int a[mxn][k], f[mxn];

int ff(int x){
	return *max_element(a[x], a[x] + k);
}

struct segTree{
	int l, r;
	segTree *tl, *tr;
	int vl, ss;
	
	segTree(int l, int r) : l(l), r(r){
		if(l != r){
			int mid = (l + r) / 2;
			tl = new segTree(l, mid);
			tr = new segTree(mid + 1, r);
			pul();
		}else{
			vl = ss = f[l] - 1;
		}
	}
	
	void pul(){
		vl = max(tl->vl, tl->ss + tr->vl);
		ss = tl->ss + tr->ss;
	}
	
	void add(int x, int v){
		if(x < l || r < x) return;
		if(l == r) return (void)(vl += v, ss += v);
		tl->add(x, v), tr->add(x, v);
		pul();
	}
	
	int qry(int x = 0){
		return l == r ? l : !(x + tl->vl) ? tl->qry(x) : tr->qry(x + tl->ss);
	}
};

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	
	for(int j = 0; j < k; j++)
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		a[--x][j] = i;
	}
	
	for(int i = 0; i < n; i++) f[ff(i)]++;
	
	segTree tre(0, n - 1);
	while(q--){
		int t;
		cin >> t;
		if(t & 1){
			int x;
			cin >> x;
			x--;
			cout << (ff(x) <= tre.qry() ? "DA" : "NE") << endl;
		}else{
			int x, y, z;
			cin >> z >> x >> y;
			x--, y--, z--;
			tre.add(ff(x), -1), tre.add(ff(y), -1);
			swap(a[x][z], a[y][z]);
			tre.add(ff(x), 1), tre.add(ff(y), 1);
		}
	}
	
	return 0;
}
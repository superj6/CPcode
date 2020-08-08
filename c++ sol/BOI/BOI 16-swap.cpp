/*
  The sorting conditions are equivalent to having a binary tree where you go down the tree and can choose swap a node with first
the left child, then the right child. This means if you don't swap or only swap with the left child, you can then solve the subtrees
seperately. However, if you swap with the right child, you could've swapped with the left child first so you can choose which of the
other values end up in each subtree, which is what makes the problem difficult. What you do is never actually move elements in the
tree, and instead mark values with -1 if it can be used in any situation, 1 if it has been swapped up or is the furthest element up and
will swap from left to right child, or 0 if it is the furthest element up the tree that can be used and can't swap from left to right 
child. You can then just create the answer 1 by 1 by going up the tree from the current index and see which element will now be at the
current node, and set values depending on if it or one of its children are the smallest. Time complexity O(nlgn).
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
const int mxn = 400001;
int n;
int a[mxn], f[mxn], ans[mxn];
 
void add(int x, int v){
	for(; x; x >>= 1){
		if(a[x] == v){
			f[x] = 0;
			break;
		}
		if(x & 1){
			if(a[x ^ 1] == v){
				f[x] = f[x ^ 1] = 1;
				break;
			}
			f[x ^ 1] = 0;
		}
		f[x] = 1;
	}
}
 
int qry(int x){
	int ret = mxn;
	for(; x; x >>= 1){
		if(~-f[x]) ret = min(ret, a[x]);
		if(!f[x]) break;
		if((x & 1) && f[x ^ 1]){
			ret = min(ret, a[x ^ 1]);
			if(!~-f[x ^ 1]) break;
		}
	}
	return ret;
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	memset(a, 0x3f, sizeof(a));
	memset(f, -1, sizeof(f));
	for(int i = 1; i <= n; i++) cin >> a[i];
	f[1] = 0;
	
	for(int i = 1; i <= n; i++){
		int x = qry(i), l = i << 1, r = i << 1 | 1;
		ans[i] = min({x, a[l], a[r]});
		if(ans[i] == x) f[l] = f[r] = 0, add(i, x);
		if(ans[i] == a[l]) f[l] = 1, f[r] = 0;
		if(ans[i] == a[r]) f[r] = 1;
	}
	
	cout << ans[1];
	for(int i = 2; i <= n; i++) cout << " " << ans[i];
	cout << endl;
 
	return 0;
}

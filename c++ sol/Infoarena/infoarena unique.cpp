/*
  Imagine creating cartesian tree out of array, with larger elements above smaller elements in every subtree. Realize that the
range of indices within an element's subtree are the largest possible range the current element could possibly be a part of, and
it is also always optimal to choose the whole subtree range since it is most likely to contain every element with value below the
current one since it is maximal. This means the problems boils down to finding the number of distinct elements in each of the O(n)
ranges corresponding to the subtrees of different element in the cartesian tree, and testing if the number of distinct elements is
equal to the value of the current element. If it is, you can then update the answer with the range size. You can find the number of
distinct element for offline queries in ranges in O(nlgn) using a BIT, or alternatively, for this problem you could use dsu on trees
to hold ranges of elements contained within each subtree and dfs the cartesian tree. I went with the first option, but had to use
fast IO because the time limit was so tight.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

int rd(){
	char c;
	while(!isdigit(c = getchar()));
	int x = c - '0';
	while(isdigit(c = getchar())) x = 10 * x + c - '0';
	return x;
}

const int mxn = 100001;
int n;
int a[mxn], l[mxn], r[mxn], f[mxn], bit[mxn];
vector<int> v[mxn];
stack<int> stk;

void add(int x, int v){
	for(; x <= n; x += x & -x) bit[x] += v;
}

int qry(int x){
	int ret = 0;
	for(; x; x -= x & -x) ret += bit[x];
	return ret;
}

void answer(){
	n = rd();
	
	while(!stk.empty()) stk.pop();
	a[0] = n, stk.push(0);
	for(int i = 1, x; i <= n; i++){
		a[i] = rd();
		f[i] = bit[i] = 0, v[l[i] = r[i] = i].clear();
		while(a[x = stk.top()] < a[i]) l[i] = l[x], stk.pop();
		v[l[i]].push_back(i), stk.push(r[x] = i);
	}
	
	int ret = 0;
	for(int i = n; i; i--){
		if(f[a[i]]) add(f[a[i]], -1);
		r[i] = r[r[i]], add(f[a[i]] = i, 1);
		for(int j : v[i]) if(qry(r[j]) == a[j]) ret = max(ret, r[j] - i + 1);
	}
	
	cout << ret << endl;
}

int main(){
	freopen("unique.in", "r", stdin);
	freopen("unique.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t = rd();
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}

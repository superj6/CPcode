/*
	You can solve for each element independently on how many elements will be visible to it in different cases
and sum them. Realize there are only three case:

1. Element can see all elements it could in full array.
2. One of elements in between it and next highest element are taken away.
3. The next higher element is taken away so it can see back even farther.

You can find the next highest element using a montonic stack for all elements. After that, the first 2 cases are easy
to handle with some basic math. To handle the third case, run through the montonic stack algorithm again, but for each
position hold all elements that the current element is the next highest. Now, you can pretend that element is not there
and bsearch on the montonic stack to find where it would intersect if that element is taken away. Make sure to handle
special case of no element being higher before current one, and I needed fast io because of tight time limit.
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

int rd(){
	char c;
	while(!isdigit(c = getchar()));
	int x = c - '0';
	while(isdigit(c = getchar())) x = 10 * x + c - '0';
	return x;
}

const int mxn = 1000001;
int n;
int a[mxn];
vector<int> v;
vector<int> g[mxn];

int main(){
	freopen("turnuri.in", "r", stdin);
	freopen("turnuri.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	n = rd();
	
	a[0] = 2e9 + 1;
	v.push_back(0);
	for(int i = 1; i <= n; i++){
		a[i] = rd();
		while(a[v.back()] <= a[i]) v.pop_back();
		g[v.back()].push_back(i), v.push_back(i);
	}
	
	ll ret = 0;
	v.assign(1, 0);
	for(int i : g[0]) ret += (ll)(i - 1) * (n - i) + (ll)(i - 2) * (i - 1);
	for(int i = 1; i <= n; i++){
		for(int j : g[i]){
			ret += (ll)(j - i) * (n - (j - i) - 1) + (ll)(j - i - 1) * (j - i - 1);
			int x = *prev(upper_bound(v.begin(), v.end(), j, [&](int x, int y){
				return a[x] > a[y];
			}));
			ret += j - x - !x - 1;
		}
		while(a[v.back()] <= a[i]) v.pop_back();
		v.push_back(i);
	}
	
	cout << ret << endl;

	return 0;
}
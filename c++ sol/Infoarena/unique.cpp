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
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100002;
int n, m;
int a[mxn];
stack<int> stk;

void answer(){
	cin >> n >> m;
	
	memset(a, 0, (n + 1) * sizeof(int));
	for(int i = 0; i < m; i++){
		int x, y;
		cin >> x >> y;
		a[x]++, a[y + 1]--;
	}
	
	while(!stk.empty()) stk.pop();
	
	ll ret = 0;
	stk.push(0);
	for(int i = 1, x; i <= n; i++){
		a[i] += a[i - 1];
		if(a[i] > stk.top()) ret += a[i] - stk.top();
		while(a[i] < stk.top()) x = stk.top(), stk.pop();
		if(a[i] != stk.top()) stk.push(a[i]);
	}

	cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}
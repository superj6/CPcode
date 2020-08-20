/*
  Realize in the problem since the inorder traversal has to be equal to the indices in increasing order, and each node is divisor
of all its subtree's nodes, the problem has similar constraints to a cartesian tree. In fact, you can just run the linear cartesian
tree algorithm using a stack except compare elements by seeing if one is a divisor of another by querying if the element is equal
to the gcd of the range between the two elements you are querying, since all elements in between have already been determined to be
a child of one of the two elements you are currently comparing.
*/

//#include "popa.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 1000;
int n;
int a[mxn];

int query(int x, int y, int X, int Y){
	int g = a[x], G = a[X];
	for(int i = x; i <= y; i++) g = __gcd(g, a[i]);
	for(int i = X; i <= Y; i++) G = __gcd(G, a[i]);
	return g == G;
}

//sol
int qry(int x, int y){
	return query(x, x, min(x, y), max(x, y));
}

int solve(int n, int l[], int r[]){
	stack<int> stk;
	for(int i = 0; i < n; i++){
		int x;
		l[i] = r[i] = -1;
		while(!stk.empty() && qry(i, x = stk.top())){
			l[i] = x;
			stk.pop();
		}
		if(!stk.empty()){
			//if(!qry(x, i)) return -1;
			r[x] = i;
		}
		stk.push(i);
	}
	while(stk.size() > 1) stk.pop();
	return stk.top();
}
//end sol

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	int l[n], r[n];
	int x = solve(n, l, r);
	
	cout << x << endl;
	if(~x){
		cout << l[0];
		for(int i = 1; i < n; i++) cout << " " << l[i];
		cout << endl;
		cout << r[0];
		for(int i = 1; i < n; i++) cout << " " << r[i];
		cout << endl;
	}

	return 0;
}

//#include "assistant.h"
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

const int mxn = 100000;
int f[mxn];
stack<int> v;

int GetRequest(){
	int x;
	cin >> x;
	return x;
}

void PutBack(int x){ cout << x << " ";}

void Assist(unsigned char *a, int n, int k, int m){
	for(int i = 0; i < k; i++){
		f[i] = 1;
		if(!a[i]) v.push(i);
	} 
	for(int i = 0; i < n; i++){
		int x = GetRequest();
		if(!f[x]) f[v.top()] = 0, PutBack(v.top()), v.pop();
		if(!a[k + i]) v.push(x);
		f[x] = 1;
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
 
	int n, m, k;
	cin >> n >> k >> m;
 
	unsigned char a[m];
	for(int i = 0, x; i < m; i++) cin >> x, a[i] = x;
 
	Assist(a, n, k, m);
	
	cout << endl;
 
	return 0;
}
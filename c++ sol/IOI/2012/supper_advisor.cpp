//#include "advisor.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 200000;
int b[mxn], f[mxn], p[mxn], ans[mxn];
priority_queue<pi> pq;

void WriteAdvice(int x){ cout << x << " ";}

void ComputeAdvice(int *a, int n, int k, int m){
	memset(b, -1, sizeof(b));
	memset(p, 0x3f, sizeof(p));
	for(int i = n - 1; ~i; i--) f[i] = p[a[i]], p[a[i]] = i;
	for(int i = 0; i < k; i++) pq.push({p[i], b[i] = i});
	for(int i = 0; i < n; i++){
		if(~b[a[i]]) ans[b[a[i]]] = 1;
		else b[pq.top().s] = -1, pq.pop();
		b[a[i]] = i + k, pq.push({f[i], a[i]});
	}
	for(int i = 0; i < n + k; i++) WriteAdvice(ans[i]);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, k;
	cin >> n >> k >> m;
	
	int a[n];
	for(int i = 0; i < n; i++) cin >> a[i];
	
	ComputeAdvice(a, n, k, m);
	
	cout << endl;
	
	return 0;
}
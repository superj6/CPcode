//#include "friend.h"
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

int findSample(int n, int a[], int p[], int b[]){
	int ret = 0;
	for(int i = n - 1; i; i--){
		switch(b[i]){
			case 0:
				ret += a[i];
				a[p[i]] = max(a[p[i]] - a[i], 0);
				break;
			case 1:
				a[p[i]] += a[i];
				break;
			case 2:
				a[p[i]] = max(a[p[i]], a[i]);
				break;
		}
	}
	
	return ret + a[0];
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	int a[n], p[n], b[n];
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < n; i++) cin >> p[i];
	for(int i = 0; i < n; i++) cin >> b[i];
	
	cout << findSample(n, a, p, b) << endl;
	

	return 0;
}
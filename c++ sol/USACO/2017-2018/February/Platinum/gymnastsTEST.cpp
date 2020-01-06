/*
	This was some different brute force tests I did to attempt to find a pattern and solve the problem. It is a good strategy
to make brute force programs when you are stuck.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <math.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

void solve(int n, int p){
	int cnt = 0;
	for(int i = 0; i < pow(n, n); i++){
		int a[n], ret[n];
		memset(ret, 0, sizeof(ret));
		for(int j = 0, k = i; j < n; j++, k /= n){
			a[j] = k % n + 1;
			for(int l = 0; l < a[j]; l++){
				ret[(j + l) % n]++;
			}
		}
		
		bool works = 1;
		for(int j = 0; j < n; j++){
			if(a[j] != ret[j]){
				works = 0;
				break;
			}
		}
		
		if(works){
			cnt++;
			if(p){
				for(int j = 0; j < n; j++){
					cout << ret[j] << " ";
				}
				cout << endl;
			}
		}
	}
	
	cout << cnt << endl;
}

void solve2(int n, int p){
	int cnt = 0;
	for(int i = 0; i < n; i++){
		for(int j = 1; j < (1 << n); j++){
			int a[n], ret[n];
			memset(ret, 0, sizeof(ret));
			for(int k = 0; k < n; k++){
				a[k] = i + ((j >> k) & 1);
				for(int l = 0; l < a[k]; l++){
					ret[(k + l) % n]++;
				}
			}
			
			bool works = 1;
		for(int k = 0; k < n; k++){
			if(!a[k] || a[k] != ret[k]){
				works = 0;
				break;
			}
		}
		
		if(works){
			cnt++;
			if(p){
				for(int k = 0; k < n; k++){
					cout << ret[k] << " ";
				}
				cout << endl;
			}
		}
		}
	}
	
	cout << cnt << endl;
}

void solve3(int n, int p){
	int cnt = 0;
	for(int i = 1; i < n; i++){
		for(int j = 1; j < (1 << n) - 1; j++){
			int a[n], ret[n];
			memset(ret, 0, sizeof(ret));
			for(int k = 0; k < n; k++){
				a[k] = i * ((j >> k) & 1);
				for(int l = 0; l < a[k]; l++){
					ret[(k + l) % n]++;
				}
			}
			
			bool works = 1;
		for(int k = 1; k < n; k++){
			if(ret[k] != ret[k - 1]){
				works = 0;
				break;
			}
		}
		
		if(works){
			cnt++;
			if(p){
				for(int k = 0; k < n; k++){
					cout << a[k] << " ";
				}
				cout << endl;
			}
		}
		}
	}
	
	cout << cnt + n << endl;
}

int main(){
	//freopen("gymnasts.in", "r", stdin);
	//freopen("gymnasts.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t, n, m, p;
	cin >> t >> n >> m >> p;
	
	if(m){
		for(int i = 1; i <= n; i++){
			if(t == 2) solve3(i, p);
			else if(t) solve2(i, p);
			else solve(i, p);
			cout << endl;
		}
	}else{
		if(t == 2) solve3(n, p);
		else if(t) solve2(n, p);
		else solve(n, p);
	}

	return 0;
}

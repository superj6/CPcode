/*
This is code of SuperJ6 for Codeforces.
Don't copy my code during f*kin' contests.

2.71828182845904523536
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 2000000;
int n;
int par[maxn], rnk[maxn], sz[maxn];
bool used[maxn];

int find(int x){
	return x == par[x] ? x : par[x] = find(par[x]);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < 2 * n; i++) par[i] = i;
	
	for(int i = 0; i < n; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		b += n;
		
		a = find(a), b = find(b);
		if(a != b){
			if(rnk[a] < rnk[b]) swap(a, b);
			if(rnk[a] == rnk[b]) rnk[a]++;
			par[b] = a;
			sz[a] += sz[b];
		}
		sz[a]++;
	}
	
	int ret = 0;
	for(int i = 0; i < n; i++){
		int x = find(i);
		if(!used[x]){
			ret += sz[x] / 2;
			used[x] = 1;
		}
	}
	
	cout << ret << endl;

	return 0;
}
/*
	Realize two points are within distance k of eachother if both diagonal distances are within k diagonals of
each other. This means we can precompute the or and xor of each diagonal, then we'll test if diagonals are within
distance k but not with distance k - 1. For distance k, we can see if for at least one range of k + 1 consecutive
diagonals the xor of all points in that diagonal is 0 and the or of those diagonals is 1. This needs to be true for
both diagonal directions of distance k. This is because the xor shows that there are 0 or 2 points and the or ensures
there are exactly 2 points. The test for k - 1 is obviously synonymous.
*/

//#include "vision.h"
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
#define vi vector<int>

vi a;

int add_not(int x){
	a.push_back(!a[x]);
	return a.size() - 1;
}

int add_and(vi v){
	a.push_back(1);
	for(int i : v) a.back() &= a[i];
	return a.size() - 1;
}

int add_or(vi v){
	a.push_back(0);
	if(*max_element(v.begin(), v.end()) > a.size()) exit(0);
	for(int i : v) a.back() |= a[i];
	return a.size() - 1;
}

int add_xor(vi v){
	a.push_back(0);
	for(int i : v) a.back() ^= a[i];
	return a.size() - 1;
}

void construct_network(int n, int m, int k){
	vi v, vv, w;
	int d = n + m - 1, f[2], ff[2];
	for(int t = 0; t < 2; t++)
	for(int i = 0; i < d; i++){
		v.clear();
		for(int j = max(0, i + 1 - m); j < n && j <= i; j++){ 
			v.push_back(j * m + (t ? m + j - i - 1 : i - j));
		} 
		add_or(v), add_xor(v);
	}
	
	for(int t = 0; t < 2; t++){
		for(int i = 0; i < 2; i++){
			w.clear();
			for(int j = 0; j < d + t - k; j++){
				v.clear(), vv.clear();
				for(int l = 0; l <= k - t; l++){
					int x = n * m + 2 * (d * i + j + l);
					v.push_back(x), vv.push_back(x + 1);
				} 
				w.push_back(add_and({add_or(v), add_not(add_xor(vv))}));
			}
			ff[i] = add_or(w);
		}
		f[t] = add_and({ff[0], ff[1]});
	}
	
	add_and({f[0], add_not(f[1])});
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	a.resize(n * m);
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		cin >> a[i * m + j];
	}

	construct_network(n, m, k);
	
	cout << a.back() << endl;
	
	return 0;
}
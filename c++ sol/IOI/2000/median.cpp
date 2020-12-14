#include "device.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define vi vector<int>

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int x, int y){
	return uniform_int_distribution<int>(x, y)(rng);
}

int f1, f2;
vi a;

int qry(int x, int y, int z){
	return Med3(++x, ++y, ++z) - 1;
}

int cmp(int x, int y){
	return x == qry(f1, x, y);
}

int sol(vi v, int x){
	int n = v.size();
	
	vi w, z;
	int y = v[rnd(0, n - 1)];

	for(int i : v) if(i != y) (cmp(i, y) ? w : z).push_back(i);
	
	return x < w.size() ? sol(w, x) : x == w.size() ? y : sol(z, x - w.size() - 1);
}

int Median(int n){
	if(!~-n) return 1;
	a.resize(n);
	a[0] = f1 = 0, a[1] = f2 = 1;
	for(int i = 2; i < n; i++){
		int x = qry(f1, f2, i);
		if(x == f1) f2 = x, f1 = i;
		else if(x == i) f2 = i;
		a[i] = i;
	}
	
	swap(a.back(), a[f1]);
	a.pop_back();
	
	return sol(a, n / 2 - 1) + 1;
}
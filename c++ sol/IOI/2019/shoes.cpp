#include "shoes.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 200001;

struct BIT{
	int bit[maxn];
	
	void add(int x, int v){
		for(x++; x < maxn; x += x & -x) bit[x] += v;
	}
	
	int qry(int x){
		int ret = 0;
		for(x++; x; x -= x & -x) ret += bit[x];
		return ret;
	}
};

int n;
int a[maxn];
bool used[maxn];
vector<int> p[2][maxn];
BIT bit;

long long count_swaps(vector<int> s){
	n = s.size();
	
	for(int i = n - 1; i >= 0; i--){
		a[i] = s[i];
		p[a[i] > 0][abs(a[i])].push_back(i);
	}
	
	long long ret = 0;
	for(int i = 0; i < n; i++){
		if(used[i]){
			bit.add(i, -1);
		}else{
			int x = a[i] > 0, y = abs(a[i]);
			int it = p[!x][y].back();
			
			bit.add(it, 1);
			ret += it - i - bit.qry(it) + x;
			
			used[i] = 1;
			used[it] = 1;
			p[x][y].pop_back();
			p[!x][y].pop_back();
		}
	}
	
	return ret;
}

/*
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	vector<int> a(n);
	for(int i = 0; i < n; i++) cin >> a[i];
	
	cout << count_swaps(a) << endl;

	return 0;
}
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 1000001;
struct BIT{
	int bit[maxn];
	
	BIT(){
		memset(bit, 0, sizeof(bit));
	}
	
	void add(int x, int v){
		for(x++; x < maxn; x += x & -x) bit[x] += v;
	}
	
	void add(int a, int b, int v){
		if(a > b) swap(a, b);
		add(a, v);
		add(b + 1, -v);
	}
	
	int qry(int x){
		int ret = 0;
		for(x++; x; x -= x & -x) ret += bit[x];
		return ret;
	}
};

int n, m;
int a[maxn];
BIT bit;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i]--;
		if(i) bit.add(a[i - 1], a[i], 1);
	}
	
	for(int i = 0; i < m; i++){
		int t, x;
		cin >> t >> x;
		t--, x--;
		if(t){
			cout << bit.qry(x) << endl;
		}else{
			if(x) bit.add(a[x - 1], a[x], -1);
			if(x < n - 1) bit.add(a[x], a[x + 1], -1);
			cin >> a[x];
			if(x) bit.add(a[x - 1], a[x], 1);
			if(x < n - 1) bit.add(a[x], a[x + 1], 1);
		}
	}

	return 0;
}
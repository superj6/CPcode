#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 15;
int n, m;
pi a[maxn];

bool works(int x){
	bool l[maxn], r[maxn];
	memset(l, 0, sizeof(l));
	memset(r, 0, sizeof(r));
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j <= (a[i].second - a[i].first + n) % n; j++){
			if(x & (1 << i)) l[(j + a[i].first) % n] = 1;
			else r[(j + a[i].first) % n] = 1;
		}
	}
	
	for(int i = 0; i < n; i++) if(!l[i] || !r[i]) return 0;
	return 1;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++) cin >> a[i].first >> a[i].second;
	
	for(int i = 0; i < (1 << m); i++){
		if(works(i)){
			for(int j = 0; j < m; j++) cout << ((i >> j) & 1);
			cout << endl;
			return 0;
		}
	}
	
	cout << "impossible" << endl;

	return 0;
}
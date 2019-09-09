#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const int maxn = 100000;
int n;
int a[maxn];

bool works(int x){
	int b[x];
	for(int i = 0; i < x; i++) b[i] = a[i];
	sort(b, b + x);
	
	
	for(int i = 0; i < x; i++){
		if(b[i] <= i) return 1;
	}
	
	return 0;
}

int main(){
	freopen("greedy.in", "r", stdin);
	freopen("greedy.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i] = n - a[i] - 1;
	}
	
	int l = 0, r = n;
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(works(mid)) r = mid;
		else l = mid;
	}
	
	cout << n - r << endl;

	return 0;
}
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 200000;
int n;
int a[maxn], deg[maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n - 2; i++){
		cin >> a[i];
		a[i]--;
		deg[a[i]]++;
	}
	a[n - 2] = a[n - 3];
	
	for(int i = 0, j = 0, k = 0; i < n - 1; i++){
		while(deg[j] || a[i] == j) j++;
		if(deg[k] || a[i] == k) k = j;
		cout << a[i] + 1 << " " << k + 1 << endl;
		deg[k]--, deg[a[i]]--;
		if(!deg[a[i]] && a[i] < j) k = a[i];
	}

	return 0;
}
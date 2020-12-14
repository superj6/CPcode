#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 200001;
int n, q;
ll a[maxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		a[i + n] = a[i];
	}
	
	for(int i = 1; i <= 2 * n; i++){
		a[i] += a[i - 1];
	}
	
	while(q--){
		int x, y;
		cin >> x >> y;
		if(x > y) swap(x, y);
		x--, y--;
		
		cout << min(a[y] - a[x], a[x + n] - a[y]) << endl;
	}

	return 0;
}
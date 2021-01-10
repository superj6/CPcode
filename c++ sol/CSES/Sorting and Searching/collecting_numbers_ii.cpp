#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 200002;
int n, q;
int a[mxn], b[mxn];

int f(int x){
	return (b[x] < b[x - 1]) + (b[x + 1] < b[x]);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> q;
	
	int ret = n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		ret -= !!b[a[i] - 1], b[a[i]] = i;
	}
	
	while(q--){
		int x, y;
		cin >> x >> y;
		x = a[x], y = a[y];
		if(x > y) swap(x, y);
		
		ret -= f(x) + f(y) - (x + 1 == y && b[y] < b[x]);
		swap(a[b[x]], a[b[y]]), swap(b[x], b[y]);
		ret += f(x) + f(y) - (x + 1 == y && b[y] < b[x]);
		
		cout << ret << endl;
	}

	return 0;
}
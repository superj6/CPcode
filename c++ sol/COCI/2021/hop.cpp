#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 1000, k = 4;
int n;
ll a[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i] = __lg(a[i]);
		for(int j = 0; j < i; j++){
			int x = 1, y = a[i], z = a[j];
			while(y / k != z / k) x++, y /= k, z /= k;
			cout << x << (j == i - 1 ? endl : ' ');
		}
	}
	
	return 0;
}
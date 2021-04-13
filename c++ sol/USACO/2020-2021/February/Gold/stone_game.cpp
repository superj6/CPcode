#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int m = 1000001;
int n;
int a[m];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0, x; i < n; i++) cin >> x, a[x]++;
	
	for(int i = 1; i < m; i++) a[i] += a[i - 1];
	
	int ret = 0;
	for(int i = 1; i < m; i++){
		int x = a[min(m, 2 * i) - 1] - a[i - 1], t = 0;
		for(int j = (m - 1) / i, l = 0; ~-j; j--){
			t |= (a[min(m, (j + 1) * i) - 1] - a[j * i - 1]) & 1;
		}
		ret += x * ((x & 1) && !t);
	}
	
	cout << ret << endl;
	
	return 0;
}
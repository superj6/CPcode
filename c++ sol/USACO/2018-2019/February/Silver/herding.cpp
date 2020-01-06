#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n;
int a[maxn];

int solve(){
	if(a[n - 2] - a[0] == n - 2 && a[n - 1] - a[n - 2] > 2) return 2;
	if(a[n - 1] - a[1] == n - 2 && a[1] - a[0] > 2) return 2;
	int ret = 0;
	for(int i = 0, j = 0; i < n; i++){
		while(a[i] - a[j] > n - 1) j++;
		ret = max(ret, i - j + 1);
	}
	return n - ret;
}

int main(){
	freopen("herding.in", "r", stdin);
	freopen("herding.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	sort(a, a + n);
	
	int minv = solve();
	int maxv = max(a[n - 2] - a[0], a[n - 1] - a[1]) - n + 2;
	
	cout << minv << endl;
	cout << maxv << endl;

	return 0;
}
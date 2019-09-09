#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	pair<int, int> a[n];
	for(int i = 0; i < n; i++){
		cin >> a[i].first;
		a[i].second = i;
	}
	
	sort(a, a + n);
	
	int ans = 0;
	for(int i = 0; i < n; i++){
		ans = max(ans, a[i].second - i + 1);
	}
	
	cout << ans << endl;

	return 0;
}
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'

int main(){
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
	
	int ans[n];
	set<int> used;
	used.insert(0);
	
	for(int i = 0; i < n; i++){
		ans[a[i].second] = -(*used.upper_bound(-a[i].second - 1));
		used.insert(-a[i].second - 1);
	}
	
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}